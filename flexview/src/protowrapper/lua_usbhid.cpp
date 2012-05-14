#include "lua_usbhid.h"
#ifdef Q_OS_WIN
#include "luabind/tag_function.hpp"
#include "../qtwrapper/qluaslot.h"
#include "luabind/out_value_policy.hpp"
namespace luabind{
    QT_EMUN_CONVERTER(QUsbHid::QueryMode)
}

LQUsbHidInfo lqusbhidinfo()
{
    return
    class_<QUsbHidInfo>("QUsbHidInfo")
    .def(constructor<>())
    .def_readwrite("path", &QUsbHidInfo::path)
    .def_readwrite("friendName", &QUsbHidInfo::friendName)
    .def_readwrite("physName", &QUsbHidInfo::physName)
    .def_readwrite("enumName", &QUsbHidInfo::enumName)
    .def_readwrite("productID", &QUsbHidInfo::productID)
    .def_readwrite("vendorID", &QUsbHidInfo::vendorID)
    .def_readwrite("version", &QUsbHidInfo::version)
    ;
}

LQHidAttr lqhidattr()
{
    return
    class_<QHidAttr>("QHidAttr")
    .def(constructor<>())
    .def_readwrite("productID", &QHidAttr::productID)
    .def_readwrite("vendorID", &QHidAttr::vendorID)
    .def_readwrite("version", &QHidAttr::version)
    ;
}

LQHidCaps lqhidcaps()
{
    return
    class_<QHidCaps>("QHidCaps")
    .def(constructor<>())
    .def_readwrite("productID", &QHidCaps::usage)
    .def_readwrite("vendorID", &QHidCaps::uasgePage)
    .def_readwrite("inputReportLength", &QHidCaps::inputReportLength)
    .def_readwrite("outputReportLength", &QHidCaps::outputReportLength)
    .def_readwrite("featureReportLength", &QHidCaps::featureReportLength)
    ;
}

SIGNAL_PROPERYT(lqusbhid,connected, QUsbHid, "(const QUsbHidInfo &)")
SIGNAL_PROPERYT(lqusbhid,disconnected, QUsbHid, "(const QUsbHidInfo &)")
SIGNAL_PROPERYT(lqusbhid,readyRead, QUsbHid, "()")

LQUsbHid lqusbhid()
{
    return
    class_<QUsbHid>("QUsbHid")
    .def(constructor<>())
    .def(constructor<QObject*>())
    .def(constructor<QObject*,QUsbHid::QueryMode>())
    .def(constructor<const QString&>())
    .def(constructor<const QString&,QObject*>())
    .def(constructor<const QString&,QObject*,QUsbHid::QueryMode>())
    .def("open", &QUsbHid::open)
    .def("open", tag_function<bool(QUsbHid*)>(boost::bind(&QUsbHid::open, _1, QUsbHid::ReadWrite)))
    .def("close", &QUsbHid::close)
    .def("flush", &QUsbHid::flush)
    .def("readAll", &QUsbHid::readAll)
    .def("readData", (QByteArray (QUsbHid::*)(int,qint64))&QUsbHid::readData)
    .def("readData", (QByteArray (QUsbHid::*)(qint64))&QUsbHid::readData)
    .def("writeData", (qint64 (QUsbHid::*)(int, const QByteArray&))&QUsbHid::writeData)
    .def("writeData", (qint64 (QUsbHid::*)(const QByteArray&))&QUsbHid::writeData)
    .def("monitor", (void (QUsbHid::*)(int,int))&QUsbHid::monitor)
    .def("monitor", (void (QUsbHid::*)(int))&QUsbHid::monitor)
    .def("monitor", (void (QUsbHid::*)())&QUsbHid::monitor)
    .def("getAttributes", &QUsbHid::GetAttributes, pure_out_value(_2))
    .def("getFeature", (QByteArray(QUsbHid::*)(int,bool*))&QUsbHid::getFeature, pure_out_value(_3))
    .def("getFeature", (QByteArray(QUsbHid::*)(int,int,bool*))&QUsbHid::getFeature, pure_out_value(_4))
    .def("getInputReport", (QByteArray(QUsbHid::*)(int,bool*))&QUsbHid::getInputReport, pure_out_value(_3))
    .def("getInputReport", (QByteArray(QUsbHid::*)(int,int,bool*))&QUsbHid::getInputReport, pure_out_value(_4))
    .def("getNumInputBuffers", &QUsbHid::getNumInputBuffers, pure_out_value(_2))
    .def("getPhysicalDescriptor", &QUsbHid::getPhysicalDescriptor, pure_out_value(_3))
    .def("getIndexedString", &QUsbHid::getIndexedString, pure_out_value(_3))
    .def("getManufacturerString", &QUsbHid::getManufacturerString)
    .def("getProductString", &QUsbHid::getProductString)
    .def("getSerialNumberString", &QUsbHid::getSerialNumberString)
    .def("setFeature", (bool(QUsbHid::*)(int, const QByteArray&))&QUsbHid::setFeature)
    .def("setFeature", (bool(QUsbHid::*)(const QByteArray&))&QUsbHid::setFeature)
    .def("setOutputReport", (bool(QUsbHid::*)(int, const QByteArray&))&QUsbHid::setOutputReport)
    .def("setOutputReport", (bool(QUsbHid::*)(const QByteArray&))&QUsbHid::setOutputReport)
    .def("setNumInputBuffers", &QUsbHid::setNumInputBuffers)


    .property("path", &QUsbHid::path, &QUsbHid::setPath)
    .property("queryMode", &QUsbHid::queryMode, &QUsbHid::setQueryMode)
    .property("timeout", &QUsbHid::timeout, &QUsbHid::setTimeout)

    .property("isSequential", &QUsbHid::isSequential)
    .property("bytesAvailable", &QUsbHid::bytesAvailable)
    .property("bytesToWrite", &QUsbHid::bytesToWrite)
    .property("caps", &QUsbHid::caps)
    .property("errorString", &QUsbHid::errorString)

    .sig_prop(lqusbhid,connected)
    .sig_prop(lqusbhid,disconnected)
    .sig_prop(lqusbhid,readyRead)

    .scope[
        def("enumDevices", (QList<QUsbHidInfo>(*)(int,int))&QUsbHid::enumDevices),
        def("enumDevices", (QList<QUsbHidInfo>(*)(int))&QUsbHid::enumDevices),
        def("enumDevices", (QList<QUsbHidInfo>(*)())&QUsbHid::enumDevices)
    ]
    ;
}
#else
LQUsbHidInfo lqusbhidinfo()
{
    return
    class_<QUsbHidInfo>("QUsbHidInfo");
}

LQUsbHid lqusbhid()
{
    return
    class_<QUsbHid>("QUsbHid");
}

LQHidAttr lqhidattr()
{
    return
    class_<QHidAttr>("QHidAttr");
}

LQHidCaps lqhidcaps()
{
    return
    class_<QHidCaps>("QHidCaps");
}
#endif
