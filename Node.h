#ifndef NODE_H
#define NODE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class Node
{
  public:
    Node(QString path);
    Node();

    enum {
      getObjRole = Qt::UserRole + 7,
      dirs,
      headers,
      mode,
      name,
      sources,
      pcs
    };

    void openInit(QString &file);
    void writeInit();
    void updateObj(QJsonObject);
    void updateByKey(QString key, QJsonValue value);
    QJsonValue data(QString key);
    QJsonValue operator[](const QString &key) const;
    QString getName() const;
    QString getPath() const;
    QJsonObject getObj() const;


  protected:
    QStringList getDirs();
    bool status;
    QString path;

  private:
    QJsonObject obj;
};

#endif // NODE_H
