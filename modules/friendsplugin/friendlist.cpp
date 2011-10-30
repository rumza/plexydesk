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

#include "friendlist.h"
#include <QDebug>
#include <QHash>
#include <QVariant>
#include <QVariantMap>
#include <QList>

FriendListModel::FriendListModel(QObject *parent) :
    QAbstractListModel(parent)
{
   QHash<int, QByteArray> roles;
   roles[facebookIdRole] = "facebookId";
   roles[facebookNameRole] = "facebookName";
   roles[facebookProfilePicture] = "profilePicture";
   roles[facebookProfile] = "facebookProfile";
   setRoleNames(roles);
   this->m_social = SocialData::getInstance();
   connect(m_social,SIGNAL(dataReady()), this, SLOT(resetModel()));
}
FriendListModel::~FriendListModel()
{

}

void FriendListModel::resetModel()
{
   QHash<QString,QVariant> data = m_social->data();
   QList<QVariant> friends = data["data"].toMap().values();
   QVariant friendDetails,friendDetail;
   Friend *fr = new Friend();
   Q_FOREACH(friendDetails,friends)
   {
      QVariant::Type T = friendDetails.type();
      if(friendDetails.convert(T))
      {
         switch(T)
         {
         case QVariant::Map :
            fr->setId(friendDetails.toMap()["id"].toString());
            fr->setName(friendDetails.toMap()["name"].toString());
            this->list.append(fr);
            fr = new Friend();
            break;;
         case QVariant::List:
            Q_FOREACH(friendDetail,friendDetails.toList())
            {
               QVariant::Type T = friendDetail.type();
               if(friendDetail.convert(T))
               {
                  switch(T)
                  {
                  case QVariant::Map :
                     fr->setId(friendDetail.toMap()["id"].toString());
                     fr->setName(friendDetail.toMap()["name"].toString());
                     this->list.append(fr);
                     fr = new Friend();
                     break;;
                  }

               }
            }
         case QVariant::Double:

            if(this->list.size() == friendDetails.toDouble())
            {
               qDebug()<<"model complete";
               return;
            }
            break;;
         }
      }
   }
   qDebug()<<"model complete";
}

QVariant FriendListModel::data(const QModelIndex &index, int role) const
{
   QVariant rv;
   if (role == facebookIdRole)
      rv = ((Friend *)this->list.at(index.row()))->id();
   else if (role == facebookNameRole)
      rv = ((Friend *)this->list.at(index.row()))->name();
   else if (role == facebookProfilePicture)
      rv = ((Friend *)this->list.at(index.row()))->picture();
   else if (role == facebookProfile)
      rv = ((Friend *)this->list.at(index.row()))->profile();
   return rv;
}

int FriendListModel::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent);
   this->list.count();
}

QDeclarativeListProperty<Friend> FriendListModel::friends()
{
   return QDeclarativeListProperty<Friend>(new QObject(),list);
}

void FriendListModel::friendSelected(QString pid)
{
   qDebug()<<Q_FUNC_INFO<<"selected :"+pid;
   this->m_social->newRequest("https://graph.facebook.com/"+pid);
}
