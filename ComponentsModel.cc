#include "ComponentsModel.h"

ComponentsModel::ComponentsModel()
{
//  Core Gui Widgets Sql Network
  inherits.insert("Core", true);
  inherits.insert("Gui", false);
  inherits.insert("Widgets", false);
  inherits.insert("Sql", false);
  inherits.insert("Network", false);
}

const QString ComponentsModel::getInherit(int index)
{
  return inherits.keys().at(index);
}

bool ComponentsModel::getInheritStatus(int index) const
{
  return inherits.values().at(index);
}

QHash<int, QByteArray> ComponentsModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[text] = "text";
  roles[active] = "active";

  return roles;
}


int ComponentsModel::rowCount(const QModelIndex &/*parent*/) const
{
  return inherits.count();
}

QVariant ComponentsModel::data(const QModelIndex &index, int role) const
{
  if (role == text || Qt::DisplayRole)
    {
      return inherits.keys().at(index.row());
    }

  if (role == active)
    {
      return inherits.values().at(index.row());
    }

  return QVariant();
}

bool ComponentsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role == text)
    {
      inherits.keys()[index.row()] = value.toString();
      dataChanged(index,index);
      return true;
    }
  if (role == active)
    {
      const QString key = inherits.keys()[index.row()];
      inherits[key] = value.toBool();
      dataChanged(index,index);
      return true;
    }

  return false;

}

#include <QDebug>
#include "Node.h"
#include <QJsonArray>
void ComponentsModel::resetInherits(QModelIndex currentIndex)
{
  qInfo() << QString::number(__LINE__) + ":" __FILE__;
  qInfo() << __LINE__ << currentIndex;
  QJsonObject json = qvariant_cast<QJsonObject>(currentIndex.data(Node::getObjRole));
  qInfo() << currentIndex.data(Node::getObjRole);
  qInfo() << json["Qt"].toArray();
  QJsonArray jsonArr = json["Qt"].toArray();

  beginResetModel();

  for (int i = 0; i < inherits.size(); i++)
    {
      const QString key = inherits.keys()[i];
      inherits[key] = false;
    }

  qInfo() << __LINE__ << inherits;
  foreach ( QJsonValue value, jsonArr)
    {
      qInfo() << __LINE__ << value;
      inherits[value.toString()] = true;
    }

  qInfo() << __LINE__ << inherits;

//  dataChanged(index(0), index(inherits.size()));
//  qInfo() << index(3).data();
//  dataChanged(QModelIndex(0,0), QModelIndex());
  endResetModel();

}
