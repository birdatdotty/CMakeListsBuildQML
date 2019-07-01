#ifndef MODESET_H
#define MODESET_H

#include <QAbstractItemModel>
#include <QObject>

class ModeSet : public QObject
{
  Q_OBJECT
  public:
    explicit ModeSet(QObject *parent = nullptr);
    Q_INVOKABLE void changed(QString mode);

  signals:
    void setActiveMode(QString mode);

  public slots:
    void resetInherits(QModelIndex currentIndex);
};

#endif // MODESET_H
