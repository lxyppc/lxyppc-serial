#ifndef LUA_COMMONDLG_H
#define LUA_COMMONDLG_H
#include "lua_qt_wrapper.hpp"
#include <luabind/out_value_policy.hpp>

struct QCommonDlg{};
typedef class_<QCommonDlg>                          LQCommonDlg;
LQCommonDlg  lqcommondlg();

#endif
