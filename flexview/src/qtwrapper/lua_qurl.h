#ifndef LUA_QURL_H
#define LUA_QURL_H
#include "lua_qt_wrapper.hpp"

typedef class_<QUrl> LQUrl;
typedef class_<QMimeData,QObject> LQMimeData;

LQUrl lqurl();
LQMimeData lqmimedata();

#endif // LUA_QURL_H
