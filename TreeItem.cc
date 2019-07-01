#include "TreeItem.h"

#include <QDebug>
TreeItem::TreeItem(QString path)
  : Node()
{
  subdirs.append(path);
  status = true;

  populate();
}

TreeItem::TreeItem(QString path, TreeItem *parent)
  : Node(path),
    m_parentItem(parent)
{
  parent->m_childItems.append(this);
  subdirs = getDirs();
  populate();
}

TreeItem::~TreeItem()
{
///////////////////////////////////////////////////////////////////////////
}

void TreeItem::appendChild(TreeItem *item)
{
  m_childItems.append(item);
}

TreeItem *TreeItem::child(int row) const
{
  return m_childItems[row];
}

int TreeItem::childCount() const
{
  return m_childItems.size();
}

int TreeItem::columnCount() const
{
  return 1;
}

QVariant TreeItem::data(int role) const
{
  if (role == Qt::DisplayRole)
    {
      return QVariant(getName());
    }

  if (role == getObjRole)
    {
      return QVariant(getObj());
    }

  return QVariant();
}

int TreeItem::row() const
{
  if (m_parentItem)
      return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

  return 0;
}
TreeItem *TreeItem::parentItem()
{
  return m_parentItem;
}
bool TreeItem::populate()
{
  if (status)
    {
      for (QString subdir: subdirs)
        {
//          TreeItem *child =
              new TreeItem(path + "/" + subdir, this);
        }
    }
  else
    return false;

  return true;
}

