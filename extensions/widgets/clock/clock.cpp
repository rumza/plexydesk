/*******************************************************************************
* This file is part of PlexyDesk.
*  Maintained by : Siraj Razick <siraj@kde.org>
*  Authored By  :
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
#include "clock.h"
#include "clockwidget.h"

Clock::Clock(QObject *parent) : PlexyDesk::ControllerInterface (parent)
{
    clock = new ClockWidget(QRectF(0, 0, 210, 210));

    if (connectToDataSource("timerengine")) {
        connect(dataSource(), SIGNAL(sourceUpdated(QVariantMap)), this, SLOT(onDataUpdated(QVariantMap)));
    }
}

Clock::~Clock()
{
    if (clock)
        delete clock;
}

PlexyDesk::AbstractDesktopWidget *Clock::defaultView()
{
    return clock;
}

void Clock::revokeSession(const QVariantMap &args)
{
}

void Clock::setViewRect(const QRectF &rect)
{
    if (clock)
        clock->setPos(rect.x(), rect.y());
}

void Clock::onDataUpdated(const QVariantMap &data)
{
    if (clock)
        clock->updateTime(data);
}
