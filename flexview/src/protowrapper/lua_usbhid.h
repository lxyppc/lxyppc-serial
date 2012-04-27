#ifndef LUA_USBHID_H
#define LUA_USBHID_H
#include "../qtwrapper/lua_qt_wrapper.hpp"
#ifdef Q_OS_WIN
#include "../../qusbhid/qusbhid.h"
#else
struct QUsbHid{};
struct QUsbHidInfo{};
struct QHidAttr{};
struct QHidCaps{};
#endif

typedef class_<QUsbHid> LQUsbHid;
typedef class_<QUsbHidInfo> LQUsbHidInfo;
typedef class_<QHidAttr> LQHidAttr;
typedef class_<QHidCaps> LQHidCaps;
LQUsbHidInfo lqusbhidinfo();
LQUsbHid lqusbhid();
LQHidAttr lqhidattr();
LQHidCaps lqhidcaps();

#endif // LUA_USBHID_H
