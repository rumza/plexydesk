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
#include "facebookengine.h"
#include "facebooklib.h"
#include <datainterface.h>
#include <pluginloader.h>
#include <QDebug>
#include <QStringList>
namespace PlexyDesk{
class FacebookEngine::Private
{
public:
    Private(){}
    ~Private(){}

    FacebookLib * library;
};
FacebookEngine::FacebookEngine(QObject *parent) : d(new Private)
{
    d->library = new FacebookLib(parent);
    connect(d->library,SIGNAL(dataReady()),this,SIGNAL(dataReady()));
}
void FacebookEngine::pushData(QVariant &data)
{
    requestService((QVariantMap)data.toMap());
}

void FacebookEngine::requestService(QVariantMap service)
{
    QString serviceName = service["name"].toString();
    QStringList availableServices = d->library->availableServices();
    if(availableServices.contains(serviceName))
    {
        QVariant args = service["data"];
        d->library->invokeService(serviceName,args);
    }else
    {
        qDebug()<<Q_FUNC_INFO<<"Unregistered service name ::"<<serviceName;
    }
}
QVariantMap FacebookEngine::readAll()
{
    return d->library->data();
}
}
