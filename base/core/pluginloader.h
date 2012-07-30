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
#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H

#include <abstractplugininterface.h>
#include <plexy.h>

namespace PlexyDesk
{
class PLEXYDESK_EXPORT PluginLoader
{
public:
    PluginLoader();
    virtual ~PluginLoader();

    static PluginLoader *getInstanceWithPrefix(const String &desktopPrefix, const String &libPrefix);

    static PluginLoader *getInstance();

    StringList listPlugins(const String &types);

    AbstractSource *instance(const String &name);

    void scanForPlugins();

    void setPluginPrefix(const String &path);

    String pluginPrefix() const;

    void setPluginInfoPrefix(const String &path);

    String pluginInforPrefix() const;

protected:
    void loadDesktop(const String &path);

    void load(const String &_interface, const String &plugin);

private:
    class PrivatePluginLoader;
    PrivatePluginLoader *const d;
#ifdef Q_WS_WIN
    static PluginLoader *mInstance;
#else
    static PLEXYDESK_EXPORT PluginLoader *mInstance;
#endif
};

} // namespace PlexDesk
#endif
