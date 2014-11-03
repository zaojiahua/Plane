//
//  WapsAd.h
//  Plane
//
//  Created by gaohuang on
//
//

#ifndef __Plane__WapsAd__
#define __Plane__WapsAd__

#include <cocos2d.h>
using namespace cocos2d;


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif


class WapsAd
{
public:
    WapsAd();
    virtual ~WapsAd();
    //通过JNI调用JAVA静态函数，实现展示AD
    static void showAd(int adTag);
//    static void uninstallAd();
};

#endif /* defined(__Plane__WapsAd__) */
