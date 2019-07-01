#ifndef TREEITEM_H
#define TREEITEM_H

#include "Node.h"

#include <QList>

class TreeItem: public Node
{
  public:
    TreeItem(QString path);
    TreeItem(QString path, TreeItem *parentItem);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int role) const;
    int row() const;
    TreeItem *parentItem();

  private:
    QList<TreeItem*> m_childItems;
    TreeItem *m_parentItem;
    QStringList subdirs;


  // my method and value:
    QStringList dirs;
  public:
    bool populate();
};

#endif // TREEITEM_H
