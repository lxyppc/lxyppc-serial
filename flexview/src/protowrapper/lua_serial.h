#ifndef LUA_SERIAL_H
#define LUA_SERIAL_H
#include "../../qextserialport/qextserialport.h"
#include "../../qextserialport/qextserialenumerator.h"
#include "../qtwrapper/lua_qt_wrapper.hpp"

typedef class_<QextSerialPort>  LQextSerialPort;
typedef class_<QextPortInfo>  LQextPortInfo;

LQextSerialPort lqextserialport();
LQextPortInfo lqextportinfo();
#endif // LUA_SERIAL_H
