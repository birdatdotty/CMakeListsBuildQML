#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>
#include <QAbstractItemModel>

#include "Node.h"
#include "ComponentsModel.h"

class MyClass : public QObject
{
    Q_OBJECT
  public:
    void setListModel(ListModel* listModel)
    {
      m_ListModel = listModel;
    }
  public slots:
    void cppSlot(const QString &msg) {
        qInfo() << "1 Called the C++ slot with message:" << msg;
    }
//    Q_INVOKABLE void forIndex(const QModelIndex* index)
    Q_INVOKABLE void forIndex(QModelIndex index)
    {
      qInfo() << "2 void forIndex(QModelIndex* index)";
      qInfo() << index.data(Node::getObjRole);
      QString name = QJsonValue::fromVariant( index.data(Node::getObjRole) ).toObject()["name"].toString();
      changeText(name);
      m_ListModel->resetInherits(index);
    }
  signals:
    Q_INVOKABLE void changeText(QString str);

  private:
    ListModel* m_ListModel;
};


#endif // MYCLASS_H
