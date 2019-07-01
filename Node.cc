#include "Node.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

Node::Node(QString path)
  : status(false),
    path(path)
{
  openInit(path);
}

Node::Node()
  :status(false)
{}

void Node::openInit(QString& path)
{
    QFile f(path + "/init.json");

    if (f.open(QIODevice::ReadOnly))
      {
        QString ctx = f.readAll();
        obj = QJsonDocument::fromJson(ctx.toUtf8()).object();
        status = !obj.isEmpty();
      }
}
#include <QDebug>
void Node::writeInit()
{
  QFile f(path + "/init.json");
qInfo() << "!!!!!!!!!!!!!!!" << __LINE__;
  if (f.open(QIODevice::WriteOnly))
    {
      qInfo() << "!!!!!!!!!!!!!!!" << __LINE__;
//      QJsonObject jsonObj; // assume this has been populated with Json data

      QJsonDocument doc(obj);
      QString strJson(doc.toJson(QJsonDocument::Compact));
//      QString str = QJsonDocument::
      QTextStream stream(&f);
      stream << strJson;
      f.close();
      if (stream.status() != QTextStream::Ok)
      {
//          qDebug() << "Ошибка записи файла";
      }
    }
}

#include <QDebug>
void Node::updateObj(QJsonObject data)
{
  QString section = data["section"].toString();
  obj[section] = data["data"];

  qInfo() << "void Node::updateObj(QJsonObject data)";
  qInfo() << "void Node::updateObj(QJsonObject data)";
  qInfo() << data;
  qInfo() << "void Node::updateObj(QJsonObject data)";
  qInfo() << "void Node::updateObj(QJsonObject data)";
}

void Node::updateByKey(QString key, QJsonValue value)
{
  obj[key] = value;
  writeInit();
  qInfo() << ">>>" << obj << "<<<";
}

QJsonValue Node::data(QString key)
{
  if (status)
    return obj[key];

  return "Error init";
}

QJsonValue Node::operator[](const QString &key) const
{
  return obj[key];
}

QStringList Node::getDirs()
{
  QStringList ret;
  if (obj["dirs"].isArray())
    {
      QJsonArray dirs = obj["dirs"].toArray();
      for (int i = 0; i < dirs.size(); i++)
        {
          ret.append(dirs[i].toString());
        }
    }

  return ret;
}

QString Node::getName() const
{
  return obj["name"].toString();
}

QString Node::getPath() const
{
  return path;
}

QJsonObject Node::getObj() const
{
  return obj;
}
