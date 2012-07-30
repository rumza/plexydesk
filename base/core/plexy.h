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
/*
 * PlexyDesk
 *
 * Sci-Fi Desktop for the Hurd
 *
 * Authored By Siraj Razick <siraj@kde.org>
 *      Dariusz Mikulski <dariusz.mikulski@gmail.com>
 *
 * Copyright (C) 2006 PlexyDeskTeam
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* visibility options
 * note only support GCC 4.x and not Windows
 * */

#ifndef __PLEXY_EXPORTS
#define __PLEXY_EXPORTS

#include <QtCore/QtGlobal>
#include <QGraphicsView>

#ifdef Q_CC_MSVC
#define __PRETTY_FUNCTION__ QString("%1 %2 %3 %4 %4").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg(__FUNCDNAME__).arg(__FUNCSIG__)
#endif

#ifdef __GNUC__
#define PACK __attribute__((__packed__))
#endif

#define __SYSTEM_HAVE_GCC_VISIBILITY

/*
#if defined(plexydeskcore_EXPORTS)
  #define  PLEXYDESK_EXPORT Q_DECL_EXPORT
#else
  #define  PLEXYDESK_EXPORT Q_DECL_IMPORT
#endif
*/

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define PLEXYDESK_EXPORT __attribute__ ((dllexport))
    #else
      #define PLEXYDESK_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define PLEXYDESK_EXPORT __attribute__ ((dllimport))
    #else
      #define PLEXYDESK_EXPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define PLEXYDESK_IMPORT
#else
  #if __GNUC__ >= 4
    #define PLEXYDESK_EXPORT __attribute__ ((visibility ("default")))
    #define PLEXYDESK_IMPORT  __attribute__ ((visibility ("hidden")))
  #else
    #define PLEXYDESK_EXPORT
    #define PLEXYDESK_IMPORT
  #endif
#endif

//TODO
//add dllexport for windows
/*
 * this  provides a helper macro for exporting plugin Classes
 * example usage  PLUGIN_EXPORT(libmyone,ClassName)
 * you will find many example usages as we include them in this
 * source distrubution.
 * */
namespace PlexyDesk
{
    typedef QString String;
    typedef QGraphicsView ViewportHost;
    typedef QRectF FloatRect;
    typedef QStringList StringList;
}

#define  Q_UINT32 unsigned int

#define PLEXYDESK_PLUGIN_META_DATA \
    static const char plexydesk_plugin_meta_data[] = \
    "api=1.0";

#define PLEXYDESK_EXPORT_EXTENSION(CLASSNAME)  \
    __attribute__ ((section (".plexyext"))) __attribute__((used)) PLEXYDESK_PLUGIN_META_DATA \
    void *get_instance() \
    { \
        return new CLASSNAME; \
    }



#endif
