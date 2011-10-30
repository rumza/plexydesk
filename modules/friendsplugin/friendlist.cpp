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
   roles[selectedFriendPicture] = "contactPicture";
   roles[selectedFriendName] = "contactName";
   setRoleNames(roles);
   this->m_SelectedFriendContact = 0;
   this->m_social = SocialData::getInstance();
   connect(m_social,SIGNAL(dataReady()), this, SLOT(resetModel()));
   connect(this,SIGNAL(friendContact(QString)),Config::getInstance(),SLOT(requestContact(QString)));
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
            this->m_List.append(fr);
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
                     this->m_List.append(fr);
                     fr = new Friend();
                     break;;
                  }

               }
            }
         case QVariant::Double:

            if(this->m_List.size() == friendDetails.toDouble())
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

void FriendListModel::readFriend()
{
   QHash<QString,QVariant> data = m_social->data();
   QList<QVariant> friends = data["data"].toMap().values();
}

QVariant FriendListModel::data(const QModelIndex &index, int role) const
{
   QVariant rv;
   if (role == facebookIdRole)
      rv = ((Friend *)this->m_List.at(index.row()))->id();
   else if (role == facebookNameRole)
      rv = ((Friend *)this->m_List.at(index.row()))->name();
   else if (role == facebookProfilePicture)
      rv = ((Friend *)this->m_List.at(index.row()))->picture();
   else if (role == facebookProfile)
      rv = ((Friend *)this->m_List.at(index.row()))->profile();
   else if (role == selectedFriendPicture)
      rv = this->m_SelectedFriendContact->picture();
   else if (role == selectedFriendName)
      rv = this->m_SelectedFriendContact->name();
   return rv;
}

int FriendListModel::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent);
   this->m_List.count();
}

QDeclarativeListProperty<Friend> FriendListModel::friends()
{
   return QDeclarativeListProperty<Friend>(new QObject(),m_List);
}

void FriendListModel::friendSelected(QString pid)
{
   qDebug()<<Q_FUNC_INFO<<"selected :"+pid;
   Friend * friendSelect = new Friend();
   friendSelect->setId(0);
   Q_FOREACH(friendSelect,this->m_List)
   {
      if (friendSelect->id() == pid){
         this->m_SelectedFriendContact = friendSelect;
         break;
      }
   }

   if (m_SelectedFriendContact->id() == pid)
   {
      this->m_social->disconnect();
      QHash<QString,QVariant> data;
      data["selectedFriendPicture"] = QVariant(this->m_SelectedFriendContact->picture());
      data["selectedFriendLargePicture"] = QVariant(this->m_SelectedFriendContact->largePicture());
      data["selectedFriendName"] = QVariant(this->m_SelectedFriendContact->name());
      data["selectedFriendId"] = QVariant(this->m_SelectedFriendContact->id());
      data["selectedFriendProfile"] = QVariant(this->m_SelectedFriendContact->profile());
      this->m_social->setData(data);
      Q_EMIT friendContact(m_SelectedFriendContact->id());
   }
}
void FriendListModel::getSelectedFriendFromData()
{
   QString id = this->m_social->data()["selectedFriendId"].toString();
   QString name = this->m_social->data()["selectedFriendName"].toString();
   if (!this->m_SelectedFriendContact)
      this->m_SelectedFriendContact = new Friend();
   this->m_SelectedFriendContact->setId(id);
   this->m_SelectedFriendContact->setName(name);
}

QUrl FriendListModel::contactPicture()
{
   if(this->m_SelectedFriendContact){
      qDebug()<<"got here"<<this->m_SelectedFriendContact->largePicture();
      return this->m_SelectedFriendContact->largePicture();
   }
   else{
      getSelectedFriendFromData();
      qDebug()<<"got here"<<m_social->data()["selectedFriendLargePicture"];
      return m_social->data()["selectedFriendLargePicture"].toUrl();
   }
}

QString FriendListModel::contactName()
{

   if(this->m_SelectedFriendContact)
      return this->m_SelectedFriendContact->name();
   else{
      getSelectedFriendFromData();
      return m_social->data()["selectedFriendName"].toString();
   }
}

