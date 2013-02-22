#ifndef LUA_QPAINTER_H
#define LUA_QPAINTER_H
#include "lua_qt_wrapper.hpp"
#include "../qrencoder.h"

typedef class_<QPainter> LQPainter;
typedef class_<QImage> LQImage;
typedef class_<QPixmap> LQPixmap;
typedef class_<QBitmap,QPixmap> LQBitmap;
typedef class_<QMovie,QObject> LQMovie;
typedef class_<QREncoder> LQREncoder;

LQPainter lqpainter();
LQImage lqimage();
LQPixmap lqpixmap();
LQBitmap lqbitmap();
LQMovie  lqmovie();
LQREncoder lqrencoder();
#endif // LUA_QPAINTER_H
