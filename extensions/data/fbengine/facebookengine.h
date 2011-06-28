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

#ifndef FACEBOOKENGINE_H
#define FACEBOOKENGINE_H

#include <QObject>
#include <plexy.h>
#include "facebooklib.h"
#include <dataplugin.h>
#include <QVariantMap>
#include <QVariant>
#include <QString>
#include <datainterface.h>
#include <pluginloader.h>

class FacebookEngine : public PlexyDesk::DataPlugin
{
    Q_OBJECT
public:
    FacebookEngine(QObject *parent=0);
    QVariantMap readAll();
signals:
    void dataReady();

public Q_SLOTS:
    void pushData(QVariant &data);

private:
    void requestService(QVariantMap service);
    class Private;
    Private *const d;
};

#endif // FACEBOOKENGINE_H
