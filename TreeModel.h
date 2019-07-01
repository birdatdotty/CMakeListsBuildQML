#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "TreeItem.h"

class TreeModel : public QAbstractItemModel
{
  Q_OBJECT
  public:
    explicit TreeModel(const TreeItem* root, QObject *parent = Q_NULLPTR);
    ~TreeModel() override;

    Q_PROPERTY(QString subProject READ getSubProjectName NOTIFY updateSubProjectName)
    Q_PROPERTY(bool selPrj READ testRow NOTIFY updateSubProjectName)

    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE const QString getSubProjectName();


    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE void setActiveIndex(QModelIndex index);
    Q_INVOKABLE void setDataActiveItem(QJsonObject obj);

  signals:
    void activeIdex(QModelIndex index);
    void activeData(QString path, QJsonObject data);
    void updateSubProjectName();

  private:
    const TreeItem *rootItem;
    QHash<int, QByteArray> roles; // роли
    QString subProjectName;
    bool existRow;
    bool testRow();
    QModelIndex *activeItem;

};

#endif // TREE_H
