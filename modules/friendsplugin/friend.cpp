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

#include "friend.h"

Friend::Friend(QObject *parent)
{
   Q_UNUSED(parent);
   this->m_id = "";
   this->m_name = "";
}
Friend::Friend(const Friend &pfriend)
{
   this->m_id = pfriend.id();
   this->m_name = pfriend.name();
}

void Friend::setName(QString pname)
{
   this->m_name = pname;
}

void Friend::setId(QString pid)
{
   this->m_id = pid;
   this->m_picture = QUrl("http://graph.facebook.com/"+m_id+"/picture");
   this->m_profile = QUrl("http://graph.facebook.com/"+m_id);
}
QString Friend::id() const
{
   return this->m_id;
}
QString Friend::name() const
{
   return this->m_name;
}
QUrl Friend::picture() const
{
   return this->m_picture;
}
QUrl Friend::profile() const
{
   return this->m_profile;
}
