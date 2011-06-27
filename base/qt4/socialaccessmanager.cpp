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
#include "socialaccessmanager.h"
#include <QStringList>
#include "pluginloader.h"

using namespace PlexyDesk;

SocialAccessManager::SocialAccessManager(QObject *parent) :
    QObject(parent)
{
    m_serviceReady = false;
    m_service = "";
    connect(ServiceEngine,SIGNAL(dataReady()),this,SIGNAL(dataReady()));
}

void SocialAccessManager::setService(QString service)
{
    m_service = service;
    m_serviceReady = this->loadServiceInstance();
}

bool SocialAccessManager::loadServiceInstance()
{
    ServiceEngine = (PlexyDesk::DataPlugin *)PlexyDesk::PluginLoader::getInstance()->instance(m_service);
    if (ServiceEngine)
        return true;
    return false;
}

void SocialAccessManager::requestService(QVariantMap &args)
{
    QVariant arg = QVariant(args);
    ServiceEngine->pushData(arg);
}

QVariantMap SocialAccessManager::getData()
{
    return ServiceEngine->readAll();
}
