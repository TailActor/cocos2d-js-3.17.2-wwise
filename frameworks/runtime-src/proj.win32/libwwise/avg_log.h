/*******************************************************************************
 @ copyright(C), 2019-2020, NETEASE
 @ filename:	  avg_log.h
 @ author:           Connor
 @ version:         1.0.0
 @ date:		  2019-05-27
 @ description:   引擎SDK接口。日志封装
 @ others:
 @ history:
 1.date:
 author:
 modification:
 ********************************************************************************/

#ifndef AVG_LOG_H_
#define AVG_LOG_H_

#include "platform/CCPlatformConfig.h"
#include "base/CCConsole.h"

#if (!defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0)
#define mylog(...)   do {} while (0)
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#define  LOG_TAG    "avg"
#define  mylog(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#include "cocos2d.h"
#define  mylog(...)  cocos2d::log(__VA_ARGS__)
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#endif // COCOS2D_DEBUG

#endif // AVG_LOG_H_
