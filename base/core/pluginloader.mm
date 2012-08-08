#include <pluginloader.h>
#import <Cocoa/Cocoa.h>

@interface PluginLoaderMacPrivate : NSObject {

}

@end

@implementation PluginLoaderMacPrivate

@end

namespace PlexyDesk 
{

class PluginLoader::PrivatePluginLoader
{
public:
    PrivatePluginLoader() {}
    ~PrivatePluginLoader() {
        [impl release];
    }
    PluginLoaderMacPrivate *impl;
};

PluginLoader::PluginLoader() : d(new PrivatePluginLoader)
{
    d->impl = [[PluginLoaderMacPrivate alloc] init];
}

PluginLoader::~PluginLoader()
{
    delete d;
}

}
