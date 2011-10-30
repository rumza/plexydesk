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

#ifndef QMLFRIENDLISTMODEL_H
#define QMLFRIENDLISTMODEL_H

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>

#include "friendlist.h"
#include "friend.h"


class QmlFriendListModelPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("PlexyDesk.Facebook.FriendListModel"));
        qmlRegisterType<FriendListModel>(uri,1,0,"FriendListModel");
        qmlRegisterType<Friend>(uri,1,0,"FriendModel");
    }
};

Q_EXPORT_PLUGIN2(friendlistmodel, QmlFriendListModelPlugin);

#endif // QMLFRIENDLISTMODEL_H
