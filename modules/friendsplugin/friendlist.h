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
*******************************************************************************/

#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <qdeclarative.h>
#include <QAbstractListModel>
#include <QDeclarativeListProperty>
#include "friend.h"
#include <socialdata.h>
#include <QUrl>
#include <plexy.h>
#include <plexyconfig.h>

using namespace PlexyDesk;

QT_MODULE(Declarative)

#define FRIENDLISTMODEL_EXPORT Q_DECL_EXPORT

class QDeclarativeContext;
class QModelIndex;

class FRIENDLISTMODEL_EXPORT FriendListModel : public QAbstractListModel, public QDeclarativeParserStatus
{
   Q_OBJECT
   Q_INTERFACES(QDeclarativeParserStatus)
public:
   FriendListModel(QObject *parent = 0);
   ~FriendListModel();

   Q_PROPERTY(QDeclarativeListProperty<Friend> friendList READ friends)

   enum Roles{
      facebookIdRole = Qt::UserRole,
      facebookNameRole = Qt::UserRole + 1,
      facebookProfilePicture = Qt::UserRole + 2,
      facebookProfile = Qt::UserRole + 3,
      selectedFriendPicture = Qt::UserRole+10,
      selectedFriendName = Qt::UserRole+11
   };

   QVariant data(const QModelIndex &index, int role) const;
   int rowCount(const QModelIndex &parent = QModelIndex()) const;
   //TODO:future functionality
   //void addFriend(Friend &pfriend);
   //void removeFriend(Friend &pfriend);
   QDeclarativeListProperty<Friend> friends();
   Q_INVOKABLE void friendSelected(QString pid);
   Q_INVOKABLE QUrl contactPicture();
   Q_INVOKABLE QString contactName();

   void componentComplete(){};
   void classBegin(){};

signals:
   void friendContact(QString id);

private slots:
   void resetModel();
   void readFriend();

private:
   Q_DISABLE_COPY(FriendListModel);
   QList<Friend *> m_List;
   SocialData *m_social;
   Friend * m_SelectedFriendContact;
   void getSelectedFriendFromData();
};

QML_DECLARE_TYPE(FriendListModel)
#endif // FRIENDLIST_H
