#include "fbtest.h"
#include <pluginloader.h>
#include <QVariantMap>
#include <QVariant>
#include <QDebug>

fbtest::fbtest(QObject *parent){
    fbengine = (DataPlugin *)PlexyDesk::PluginLoader::getInstance()->instance("fbengine");
    if (!fbengine)
    {
        qDebug()<<"\nFacebook engine not loaded.Test failure";
    }else
    {
        connect(fbengine,SIGNAL(dataReady()),this,SLOT(listen()));
        this->runTest(1);
    }
}
void fbtest::runTest(int id)
{
    Q_UNUSED(id);
    QVariantMap map;
    map["service"] = QVariant(QString("getPublicInformation"));
    map["data"] = QVariant(QString("varunarl"));
    QVariant args = QVariant(map);
    fbengine->pushData(args);
}

void fbtest::listen()
{
    QVariantMap map = fbengine->readAll();
    QStringList keySet = map.keys();
    Q_FOREACH(QString key, keySet)
    {
        qDebug()<<map[key].toString();
    }
}
