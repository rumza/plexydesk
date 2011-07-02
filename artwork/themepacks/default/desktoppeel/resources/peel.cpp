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

#include "peel.h"
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QPixmap>
#include <QFile>
#include <plexyconfig.h>

using namespace PlexyDesk;

Peel::Peel(QObject *parent)
{
    path = QDir::toNativeSeparators(QDesktopServices::storageLocation(QDesktopServices::HomeLocation)+"/.config/plexydesk/artwork/images/");
//    changeImage();
//    connect(PlexyDesk::Config::getInstance(),SIGNAL(wallpaperChanged()),this,SLOT(changeImage()));
}
Peel::~Peel(){}
void Peel::viewBack(QString str)
{
    PlexyDesk::Config::getInstance()->changeLayer(str);
}
void Peel::changeImage()
{
    Q_EMIT beginImageChange();
    QString wallpaper = QDir::toNativeSeparators(PlexyDesk::Config::getInstance()->wallpaper());
    QString source = path + "peel-image.png";
    QPixmap imageMap;
    if (imageMap.load(wallpaper))
    {
        if(!QFile::remove(source))
            qDebug()<<Q_FUNC_INFO<<"File not found : "<<source;
        if(imageMap.copy(imageMap.size().width()-100,0,100,100).save(source,"PNG"))
            Q_EMIT imageChanged();
        else
            qDebug()<<Q_FUNC_INFO<<"Image Save error";
    }else{
        qDebug()<<Q_FUNC_INFO<<"Image load error";
    }
    Q_EMIT endImageChange();
}

QString Peel::icon()
{
    return path + "peel-image.png";
}
