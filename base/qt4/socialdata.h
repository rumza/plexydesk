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

#ifndef SOCIALDATA_H
#define SOCIALDATA_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include <facebooksession.h>

class SocialData : public QObject
{
    Q_OBJECT
public:
   static SocialData * getInstance();
   QHash<QString,QVariant> data();
   void newRequest(QString request);
   void setData(QHash<QString,QVariant>);
public slots:
   void readSession();
signals:
   void dataReady();

private:
   Q_DISABLE_COPY(SocialData);
   SocialData(QObject *parent = 0);
   static SocialData * m_instance;
   QHash<QString,QVariant> m_data;
   FacebookSession *session;

};

#endif // SOCIALDATA_H
