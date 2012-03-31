#ifndef LUA_QRECT_H
#define LUA_QRECT_H
#include "lua_qt_wrapper.hpp"


typedef class_<QPoint>                      LQPoint;
typedef class_<QRect>                       LQRect;
typedef class_<QSize>                       LQSize;
typedef class_<QMargins>                    LQMargins;
typedef class_<QColor>                      LQColor;
typedef class_<QBrush>                      LQBrush;
typedef class_<QFont>                       LQFont;

LQPoint lqpoint();
LQRect  lqrect();
LQSize  lqsize();
LQMargins lqmargins();
LQColor lqcolor();

LQBrush  lqbrush();
LQFont lqfont();

#endif
