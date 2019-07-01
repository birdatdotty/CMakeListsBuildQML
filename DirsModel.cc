#include "DirsModel.h"
#include "Node.h"
#include "TreeItem.h"

#include <QFileDialog>
#include <QDebug>

DirsModel::DirsModel()
{
}

QHash<int, QByteArray> DirsModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[dir] = "dir";

  return roles;
}

int DirsModel::rowCount(const QModelIndex &/*parent*/) const
{
  return dirs.size();
}

QVariant DirsModel::data(const QModelIndex &index, int role) const
{
  if (role == dir || Qt::DisplayRole)
    return dirs.at(index.row());

  return QVariant();
}

void DirsModel::addDir(QString curDir)
{

  QFileDialog dialog;
  dialog.setFileMode(QFileDialog::DirectoryOnly);
  dialog.setOption(QFileDialog::ShowDirsOnly, false);
  dialog.setDirectory(curDir);
  dialog.exec();
  qInfo() << "void DirsModel::addDir(QString curDir)"
          << dialog.directory().path();
}

QString DirsModel::getPath()
{
  return path;
}

void DirsModel::resetInherits(QModelIndex currentIndex)
{
  QJsonObject obj = qvariant_cast<QJsonObject>(currentIndex.data(Node::getObjRole));
//  path = const_cast<TreeItem*>(currentIndex.internalPointer())->getPath();;
  TreeItem* treeItem = static_cast<TreeItem*>(currentIndex.internalPointer());
  path = treeItem->getPath();

  QJsonArray dirsArr = obj["dirs"].toArray();

  beginResetModel();
  dirs.clear();
  for(int i = 0; i < dirsArr.size(); i++)
    dirs.append(dirsArr[i].toString());
  endResetModel();

}
