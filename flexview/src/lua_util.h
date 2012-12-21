#ifndef LUA_UTIL_H
#define LUA_UTIL_H
#include "./qtwrapper/lua_qt_wrapper.hpp"


class QUtil
{
    // dummy class, used to strore the static functions
};
typedef class_<QUtil> LQUtil;

LQUtil lqutil();

#endif // LUA_QFTP_H
