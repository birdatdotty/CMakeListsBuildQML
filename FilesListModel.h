// https://habr.com/ru/post/349822/

#ifndef FILESLISTMODEL_H
#define FILESLISTMODEL_H

#include "TreeModel.h"

#include <QAbstractListModel>
#include <QMap>

class FilesListModel : public QAbstractListModel
{
  Q_OBJECT
  public:
    enum Role {
      file = Qt::UserRole + 1,
      type
    };
    FilesListModel();
    // Собственно метод для доступа к элементу
//    Q_INVOKABLE const QString getInherit( int index );
//    Q_INVOKABLE const bool getInheritStatus( int index );


    QHash<int, QByteArray> roleNames() const override;


    // Обязательная реализация QAbstractListModel:
    int rowCount( const QModelIndex& parent ) const override;

    // Этот метод не реализован, т.к. у нас нет ролей.
    QVariant data( const QModelIndex& index, int role ) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;

    // И где-то тут должны быть методы для добавления и удаления элементов
    // в модель и внутренний QList, а также все необходимые вызовы
    // beginInsertRows(), endInsertRows() и им подобные.
    // Тут все стандартно, как в документации, никакой магии.

    Q_INVOKABLE QString getPath();
  public slots:
    Q_INVOKABLE void addFile(QString path, TreeModel *treeModel);

  private:
    QMap<QString,QString> files;
    QStringList sources, headers, others;
    QString path;
    QModelIndex *currentIndex;
    TreeItem* item;

  public slots:
    void resetInherits(QModelIndex currentIndex);
};

#endif // FILESLISTMODEL_H
