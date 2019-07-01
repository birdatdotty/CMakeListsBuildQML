// https://habr.com/ru/post/349822/

#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <QMap>

class ComponentsModel : public QAbstractListModel
{
  Q_OBJECT
  public:
    enum Role {
      text = Qt::UserRole + 1,
      active
    };
    ComponentsModel();
    // Собственно метод для доступа к элементу
    Q_INVOKABLE const QString getInherit( int index );
    Q_INVOKABLE bool getInheritStatus( int index ) const;

    QHash<int, QByteArray> roleNames() const override;

    // Обязательная реализация QAbstractListModel:
    int rowCount( const QModelIndex& parent ) const override;

    // Этот метод не реализован, т.к. у нас нет ролей.
    QVariant data( const QModelIndex& index, int role ) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;

    // И где-то тут должны быть методы для добавления и удаления элементов
    // в модель и внутренний QList, а также все необходимые вызовы
    // beginInsertRows(), endInsertRows() и им подобные.
    // Тут все стандартно, как в документации, никакой магии.

  private:
    QMap<QString,bool> inherits;

  public slots:
    void resetInherits(QModelIndex currentIndex);
};

#endif // LISTMODEL_H
