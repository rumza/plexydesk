/*******************************************************************************
* This file is part of PlexyDesk.
*  Maintained by : Siraj Razick <siraj@kde.org>
*  Authored By  : Varuna Lekamwasam <vrlekamwasam@gmail.com>
*
*  PlexyDesk is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  PlexyDesk is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with PlexyDesk. If not, see <http://www.gnu.org/licenses/lgpl.html>
*******************************************************************************/

#include "facebooklib.h"
#include <QVariantMap>
#include <QVariant>
#include <plexyconfig.h>
#include <plexy.h>
#include <datainterface.h>
#include <pluginloader.h>

namespace PlexyDesk{
class FacebookLib::Private : public QObject
{
public:
    Private()
    {
        connect(networkMgr,SIGNAL(dataReady()),this,SLOT(networkResponse()));
    }
    ~Private(){}
    PlexyDesk::DataPlugin *networkMgr;
    QVariant args;
    QVariantMap response;
public:
    void requestNetwork()
    {
        if(args.isNull())
            return;
        networkMgr->pushData(args);
    }
signals:
    void dataReady();
    private slots:
    void networkResponse()
    {
        response = networkMgr->readAll();
        emit dataReady();
    }
    //TODO
    //FacebookStateManager * stateMgr;
    //FacebookCacheManager * cacheMgr;
};
QStringList FacebookLib::availableServices()
{
    QStringList servicesRegistry;
    servicesRegistry<<"getPublicInformation";
    return servicesRegistry;
}


FacebookLib::FacebookLib(QObject *parent) : d (new Private), QObject(parent)
{
    d->networkMgr = (PlexyDesk::DataPlugin *)PlexyDesk::PluginLoader::getInstance()->instance("restengine");
    connect(d,SIGNAL(dataReady()),d, SLOT(networkResponse()));
}
QVariantMap FacebookLib::data()
{
    return d->response;
}

void FacebookLib::getPublicInfomation(QString user)
{
    QUrl req = QUrl("http://graph.facebook.com/"+user);
    QVariantMap argsMap;
    argsMap.insert("url",req);
    argsMap.insert("type",0);
    d->args = QVariant(argsMap);
    d->requestNetwork();
}
void FacebookLib::invokeService(QString service, QVariant args)
{
    if (service == "getPublicInformation")
        this->getPublicInfomation(args.toString());
}
}
