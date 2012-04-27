#ifndef LUA_QURL_H
#define LUA_QURL_H
#include "lua_qt_wrapper.hpp"

typedef class_<QUrl> LQUrl;
typedef class_<QMimeData,QObject> LQMimeData;
typedef class_<QDrag,QObject> LQDrag;
typedef class_<QRegExp> LQRegExp;

LQUrl lqurl();
LQMimeData lqmimedata();
LQDrag lqdrag();
LQRegExp lqregexp();

#endif // LUA_QURL_H
