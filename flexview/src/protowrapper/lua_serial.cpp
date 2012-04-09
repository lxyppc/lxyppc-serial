#include "lua_serial.h"

LQextPortInfo lqextportinfo()
{
    return
    class_<QextPortInfo>("QSerialInfo")
    .def(constructor<>())
    .def_readwrite("portName", &QextPortInfo::portName)
    .def_readwrite("friendName", &QextPortInfo::friendName)
    .def_readwrite("physName", &QextPortInfo::physName)
    .def_readwrite("enumName", &QextPortInfo::enumName)
    .def_readwrite("productID", &QextPortInfo::productID)
    .def_readwrite("vendorID", &QextPortInfo::vendorID)
    ;
}

LQextSerialPort lqextserialport()
{
    return
    class_<QextSerialPort>("QSerialPort")
    .def(constructor<>())
    .scope[
        def("enumPort", &QextSerialEnumerator::getPorts)
    ]
    ;
}
