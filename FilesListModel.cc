#include "FilesListModel.h"
#include <QDebug>
#include <QDebug>
#include <QFileDialog>
#include "Node.h"
#include "TreeItem.h"
#include <QJsonArray>

FilesListModel::FilesListModel()
{}

QHash<int, QByteArray> FilesListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[file] = "file";
  roles[type] = "type";

  return roles;
}

int FilesListModel::rowCount(const QModelIndex &/*parent*/) const
{
  return sources.size() + headers.size() + others.size();
}

QVariant FilesListModel::data(const QModelIndex &index, int role) const
{
  if (role == file || Qt::DisplayRole)
    {
      int row = index.row();
      if (row < sources.size())
        return sources.at(row);

      row -= sources.size();
      if (row < headers.size())
        return headers.at(row);

      row -= headers.size();
      qInfo() << "row:" << row;
      if (row < others.size())
        return others.at(row);

      return QVariant();
    }

  if (role == type)
    {
      int row = index.row();
      if (row < sources.size())
        return "C";

      row -= sources.size();
      if (row < headers.size())
        return "H";

      row -= headers.size();
      qInfo() << "row:" << row;
      if (row < others.size())
        return "O";

      return QVariant();
    }

  return QVariant();
}

QString FilesListModel::getPath()
{
  return path;
}

void FilesListModel::addFile(QString path, TreeModel *treeModel)
{
  QList<QUrl> newFiles =
      QFileDialog::getOpenFileUrls(nullptr,
                                   "Отметьте файлы",
                                   QUrl::fromLocalFile(path),
                                   "All(*.*)"
                                   ";;Sources(*.c *.cc *.c++ *.cpp)"
                                   ";;Headers(*.h *.h++ *.hpp)");
  QStringList files;
  if (newFiles.size() > 0)
    {
      for (QUrl file: newFiles)
        files.append(file.fileName());

      beginResetModel();

      sources.clear();
      headers.clear();
      others.clear();

      for (QString file: files)
        {
          if (file.endsWith(".cc") ||
              file.endsWith(".cpp") ||
              file.endsWith(".c++"))
            sources.append(file);
          else if (file.endsWith(".h") ||
                   file.endsWith(".hpp") ||
                   file.endsWith(".h++"))
            headers.append(file);
          else others.append(file);
        }

      item->updateByKey("sources", QJsonArray::fromStringList(sources));
      item->updateByKey("headers", QJsonArray::fromStringList(headers));
      item->updateByKey("others", QJsonArray::fromStringList(others));


      endResetModel();
    }

}

void FilesListModel::resetInherits(QModelIndex currentIndex)
{
  QJsonObject indexJson = qvariant_cast<QJsonObject>(currentIndex.data(Node::getObjRole));
  TreeItem* treeItem = static_cast<TreeItem*>(currentIndex.internalPointer());

  path = treeItem->getPath();
  item = static_cast<TreeItem*>(currentIndex.internalPointer());

  QJsonArray sourcesArray = indexJson["sources"].toArray();
  QJsonArray headersArray = indexJson["headers"].toArray();
  QJsonArray othersArray = indexJson["others"].toArray();

  beginResetModel();

  sources.clear();
  for (int i = 0; i < sourcesArray.size(); i++)
    sources.append(sourcesArray[i].toString());

  headers.clear();
  for (int i = 0; i < headersArray.size(); i++)
    headers.append(headersArray[i].toString());

  others.clear();
  for (int i = 0; i < othersArray.size(); i++)
    others.append(othersArray[i].toString());

  endResetModel();

  this->currentIndex = &currentIndex;

}
