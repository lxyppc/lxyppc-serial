#include "lua_socket.h"
#include "../qtwrapper/qluaslot.h"
namespace luabind{
QT_EMUN_CONVERTER(QHostAddress::SpecialAddress)
QT_EMUN_CONVERTER(QAbstractSocket::NetworkLayerProtocol)
QT_EMUN_CONVERTER(QAbstractSocket::SocketError)
QT_EMUN_CONVERTER(QNetworkProxy::ProxyType)
QT_EMUN_CONVERTER(QNetworkProxy::Capability)
QT_EMUN_CONVERTER(QNetworkProxy::Capabilities)
}

void lqhostaddress_setAddr_ipv6(QHostAddress* w, const QByteArray& arr)
{
    Q_IPV6ADDR v6;
    memcpy(v6.c, arr.data(), 16);
    w->setAddress(v6);
}

QByteArray lqhostaddress_to_ipv6(QHostAddress* w)
{
    Q_IPV6ADDR addr = w->toIPv6Address();
    return QByteArray::fromRawData((const char*)addr.c, sizeof(addr.c));
}

void lqhostaddress_init(const luabind::argument & arg, const QByteArray& arr)
{
    QHostAddress* r = construct<QHostAddress>(arg);
    Q_IPV6ADDR v6;
    memcpy(v6.c, arr.data(), 16);
    r->setAddress(v6);
}

LQHostAddress lqhostaddress()
{
    return
    class_<QHostAddress>("QHostAddress")
    .def(constructor<>())
    .def(constructor<const QString&>())
    .def(constructor<const QHostAddress&>())
    .def(constructor<QHostAddress::SpecialAddress>())
    .def("__init", lqhostaddress_init)
    .def("clear", &QHostAddress::clear)
    .def("isNull", &QHostAddress::isNull)
    .def("__tostring", &QHostAddress::toString)
    .def("toString", &QHostAddress::toString)
    .def("setAddress", (bool(QHostAddress::*)(const QString &))&QHostAddress::setAddress)
    .def("setAddress", (void(QHostAddress::*)(quint32))&QHostAddress::setAddress)
    .def("setAddress", lqhostaddress_setAddr_ipv6)
    .def("toIPv4Address", &QHostAddress::toIPv4Address)
    .def("toIPv6Address", lqhostaddress_to_ipv6)

    .property("scopeId", &QHostAddress::scopeId, &QHostAddress::setScopeId)
    .property("protocol", &QHostAddress::protocol)
    ;
}

static setter_map<QNetworkProxy> lqnp_set_map;
QNetworkProxy* lqnp_init(QNetworkProxy* widget, const object& table)
{
    lq_general_init(widget, table, lqnp_set_map);
    return widget;
}
template<>
void table_init_general<QNetworkProxy>(const luabind::argument & arg, const object& obj)
{
    lqnp_init(construct<QNetworkProxy>(arg), obj);
}

ENUM_FILTER(QNetworkProxy,type,setType)
ENUM_FILTER(QNetworkProxy,port,setPort)
ENUM_FILTER(QNetworkProxy,capabilities,setCapabilities)
LQNetworkProxy lqnetworkproxy()
{
    return
    myclass_<QNetworkProxy>("QNetworkProxy",lqnp_set_map)
    .def(constructor<>())
    .def(constructor<QNetworkProxy::ProxyType>())
    .def(constructor<QNetworkProxy::ProxyType,const QString&>())
    .def(constructor<QNetworkProxy::ProxyType,const QString&, quint16>())
    .def(constructor<QNetworkProxy::ProxyType,const QString&, quint16, const QString&>())
    .def(constructor<QNetworkProxy::ProxyType,const QString&, quint16, const QString&, const QString&>())
    .def("__call", lqnp_init)
    .def("__init", table_init_general<QNetworkProxy>)

    .property("hostName", &QNetworkProxy::hostName, &QNetworkProxy::setHostName)
    .property("isCachingProxy", &QNetworkProxy::isCachingProxy)
    .property("isTransparentProxy", &QNetworkProxy::isTransparentProxy)
    .property("capabilities", QNetworkProxy_capabilities, QNetworkProxy_setCapabilities)
    .property("password", &QNetworkProxy::password, &QNetworkProxy::setPassword)
    .property("port", QNetworkProxy_port, QNetworkProxy_setPort)
    .property("type", QNetworkProxy_type, QNetworkProxy_setType)
    .property("user", &QNetworkProxy::user, &QNetworkProxy::setUser)

    .scope[
            def("applicationProxy", &QNetworkProxy::applicationProxy),
            def("setApplicationProxy", &QNetworkProxy::setApplicationProxy)
    ]
    ;
}

bool lqtcpserver_listen1(QTcpServer* w)
{
    return w->listen();
}
bool lqtcpserver_listen2(QTcpServer* w, const QHostAddress& a)
{
    return w->listen(a);
}

bool lqtcpserver_waitForNewConnection1(QTcpServer* w)
{
    return w->waitForNewConnection();
}

bool lqtcpserver_waitForNewConnection2(QTcpServer* w, int ms)
{
    return w->waitForNewConnection(ms);
}

static setter_map<QTcpServer> lqtcpserver_set_map;
QTcpServer* lqtcpserver_init(QTcpServer* widget, const object& table)
{
    lq_general_init(widget, table, lqtcpserver_set_map);
    return widget;
}
template<>
void table_init_general<QTcpServer>(const luabind::argument & arg, const object& obj)
{
    lqtcpserver_init(construct<QTcpServer>(arg), obj);
}

SIGNAL_PROPERYT(lqtcpserver, newConnection, QTcpServer, "()")
LQTcpServer lqtcpserver()
{
    return
    myclass_<QTcpServer,QObject>("QTcpServer",lqtcpserver_set_map)
    .def(constructor<>())
    .def(constructor<QObject*>())
    .def("__call", lqtcpserver_init)
    .def("__init", table_init_general<QTcpServer>)
    .def("close", &QTcpServer::close)
    .def("listen", &QTcpServer::listen)
    .def("listen", lqtcpserver_listen1)
    .def("listen", lqtcpserver_listen2)
    .def("waitForNewConnection", lqtcpserver_waitForNewConnection1)
    .def("waitForNewConnection", lqtcpserver_waitForNewConnection2)
    .def("setSocketDescriptor", &QTcpServer::setSocketDescriptor)

    .property("hasPendingConnections", &QTcpServer::hasPendingConnections)
    .property("isListening", &QTcpServer::isListening)
    .property("maxPendingConnections", &QTcpServer::maxPendingConnections, &QTcpServer::setMaxPendingConnections)    
    .property("errorString", &QTcpServer::errorString)
    .property("socketDescriptor", &QTcpServer::socketDescriptor)
    .sig_prop(lqtcpserver, newConnection)

    .class_<QTcpServer,QObject>::property("serverError", &QTcpServer::serverError)
    .property("proxy", &QTcpServer::proxy, &QTcpServer::setProxy)
    .property("nextPendingConnection", &QTcpServer::nextPendingConnection)
    ;
}

LQTcpSocket lqtcpsocket()
{
    return
    myclass_<QTcpSocket,QObject>("QTcpServer",lqtcpserver_set_map)
    .def(constructor<>())
    .def(constructor<QObject*>())
    ;
}
