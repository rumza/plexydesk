//
//  SampleEcho.h
//  PluginLoader
//
//  Created by Siraj Razick on 12-08-07.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PrinterInterface.h"

@interface SampleEcho : NSObject<PrinterInterface>

+ (void) echo;

@end
