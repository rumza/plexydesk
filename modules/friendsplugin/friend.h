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

#ifndef FRIEND_H
#define FRIEND_H

#include <QObject>
#include <QString>
#include <QUrl>
class Friend : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString name READ name WRITE setName)
   Q_PROPERTY(QString id READ id WRITE setId)
public:
   Friend(QObject *parent = 0);
   Friend(const Friend &pfriend);
   void setName(QString pname);
   void setId(QString pid);
   QString name() const;
   QString id() const;
   QUrl picture() const;
   QUrl largePicture() const;
   QUrl profile() const;
private:
   QString m_name;
   QString m_id;
   QUrl m_picture;
   QUrl m_profile;
   QUrl m_lPicture;
   Friend &operator=(const Friend &);
};

#endif // FRIEND_H
