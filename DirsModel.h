#ifndef DIRS_H
#define DIRS_H

#include <QAbstractListModel>

class DirsModel : public QAbstractListModel
{
  Q_OBJECT
  public:
  //Q_PROPERTY(int someProperty READ getSomeProperty WRITE setSomeProperty NOTIFY somePropertyChanged)
    DirsModel();
    enum Role { dir = Qt::UserRole + 1 };

    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    Q_INVOKABLE void addDir(QString curDir);
    Q_INVOKABLE QString getPath();

  public slots:
    void resetInherits(QModelIndex currentIndex);

  private:
    QStringList dirs;
    QString path;
};

#endif // DIRS_H
