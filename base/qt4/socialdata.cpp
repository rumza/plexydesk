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

#include "socialdata.h"
#include <QDebug>
#include <QUrl>
SocialData *SocialData::m_instance = 0;

SocialData::SocialData(QObject *parent) :
    QObject(parent)
{
   session = new FacebookSession();
   connect(session,SIGNAL(ready()),this,SLOT(readSession()));
}

SocialData* SocialData::getInstance()
{
   if(m_instance == 0)
      m_instance = new SocialData();
   return m_instance;
}

void SocialData::setData(QHash<QString,QVariant> data)
{
   this->m_data = data;
   Q_EMIT dataReady();
}

QHash<QString,QVariant> SocialData::data()
{
   return this->m_data;
}

void SocialData::readSession()
{
   this->setData(session->parsedData());
}

void SocialData::newRequest(QString request)
{
   session->makeRequest(request);
}

