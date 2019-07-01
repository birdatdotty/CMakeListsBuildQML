#include "TreeModel.h"

TreeModel::TreeModel(const TreeItem* root, QObject *parent)
  : QAbstractItemModel(parent)
{
  subProjectName = "Подпроект не выбран";
//  enum {getObjRole = Qt::UserRole + 7};
  rootItem = root;
  activeItem = Q_NULLPTR;
  existRow = false;
//  roles[Qt::DisplayRole] = "name";
//  roles[Node::getObjRole] = "getObj";

//  setRoleNames(roles);
}

TreeModel::~TreeModel()
{

}

QHash<int, QByteArray> TreeModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[Qt::DisplayRole] = "name";
  roles[Node::getObjRole] = "getObj";

  return roles;
}

const QString TreeModel::getSubProjectName()
{
  return subProjectName;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  TreeItem *item;
  item = static_cast<TreeItem*>(index.internalPointer());

  return item->data(role);
}
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  return QAbstractItemModel::flags(index);
}
QVariant TreeModel::headerData(int /*section*/,
                          Qt::Orientation /*orientation*/,
                          int role) const
{
  if (role == Qt::DisplayRole)
    return QVariant("VVVVV");

  return QVariant();
}
#include <QDebug>
QModelIndex TreeModel::index(int row, int column,
                  const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
      return QModelIndex();

  const TreeItem *parentItem;

  if (!parent.isValid())
      parentItem = rootItem;
  else
      parentItem = static_cast<TreeItem*>(parent.internalPointer());

  TreeItem *item = parentItem->child(row);

  if (item)
      return createIndex(row, column, item);
  else
      return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
      return QModelIndex();

  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = item->parentItem();
  if (parentItem == nullptr)
      return QModelIndex();

  if (item == rootItem)
      return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}
int TreeModel::rowCount(const QModelIndex &parent) const
{
  const TreeItem *parentItem;
  if (parent.column() > 0)
      return 0;

  if (!parent.isValid())
      parentItem = rootItem;
  else
      parentItem = static_cast<TreeItem*>(parent.internalPointer());

  return parentItem->childCount();
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
      return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  else
    return rootItem->columnCount();
}

void TreeModel::setActiveIndex(QModelIndex index)
{
  subProjectName = index.data().toString();
  updateSubProjectName();
  existRow = true;
  activeItem = &index;

  activeIdex(index);
  QJsonObject obj = qvariant_cast<QJsonObject>(index.data(Node::getObjRole));

  TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
  QString path = item->getPath();
  activeData(path, obj);
}

void TreeModel::setDataActiveItem(QJsonObject obj)
{
  /*
   * { section, data }
   */
  if (activeItem != nullptr)
    {
      TreeItem* item = static_cast<TreeItem*>(activeItem->internalPointer());
      item->updateObj(obj);
    }
}

bool TreeModel::testRow()
{
  return existRow;
}
