#include "ModeSet.h"
#include "Node.h"
#include "TreeItem.h"

#include <QAbstractItemModel>
#include <QDebug>
#include <QJsonObject>

ModeSet::ModeSet(QObject *parent) : QObject(parent)
{

}


void ModeSet::changed(QString mode)
{
  qInfo() << "void ModeSet::changed("+mode+")";
}

void ModeSet::resetInherits(QModelIndex currentIndex)
{
  QJsonObject obj = qvariant_cast<QJsonObject>(currentIndex.data(Node::getObjRole));
  QString mode = obj["mode"].toString("App");

  if (mode == "App")
    setActiveMode("App");
  else if (mode == "StaticLib")
    setActiveMode("StaticLib");
  else if (mode == "DynamicLib")
    setActiveMode("DynamicLib");
}
