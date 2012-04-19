#ifndef LUA_SOCKET_H
#define LUA_SOCKET_H
#include "../qtwrapper/lua_qt_wrapper.hpp"
#include <QtNetwork>

typedef class_<QHostAddress>  LQHostAddress;
typedef class_<QNetworkProxy> LQNetworkProxy;
typedef class_<QTcpServer,QObject>  LQTcpServer;
typedef class_<QTcpSocket,QObject>  LQTcpSocket;
typedef class_<QUdpSocket,QObject>  LQUdpSocket;



LQHostAddress lqhostaddress();
LQNetworkProxy lqnetworkproxy();
LQTcpServer lqtcpserver();
LQTcpSocket lqtcpsocket();
LQUdpSocket lqudpsocket();


#endif // LUA_SOCKET_H
