#include "TreeItem.h"
#include "ComponentsModel.h"
#include "TreeModel.h"
#include "FilesListModel.h"
#include "DirsModel.h"
#include "ModeSet.h"

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

//#include <QtScript>


int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  //////////
  TreeItem *rootItem = new TreeItem("/tmp/qwe");
  TreeModel *prjTree = new TreeModel(rootItem);

  ComponentsModel componentsModel;
  FilesListModel filesListModel;
  DirsModel dirsModel;
  ModeSet modeSet;

  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view.rootContext();

  QObject::connect(prjTree, &TreeModel::activeIdex,
                   &filesListModel, &FilesListModel::resetInherits);
  QObject::connect(prjTree, &TreeModel::activeIdex,
                  &componentsModel, &ComponentsModel::resetInherits);
  QObject::connect(prjTree, &TreeModel::activeIdex,
                  &dirsModel, &DirsModel::resetInherits);
  QObject::connect(prjTree, &TreeModel::activeIdex,
                  &modeSet, &ModeSet::resetInherits);

  ctxt->setContextProperty("prjTree", prjTree);
  ctxt->setContextProperty("componentsModel", &componentsModel);
  ctxt->setContextProperty("filesListModel", &filesListModel);
  ctxt->setContextProperty("dirsModel", &dirsModel);
  ctxt->setContextProperty("modeSet", &modeSet);


  view.setSource(QUrl("qrc:/main.qml"));





  return app.exec();
}
