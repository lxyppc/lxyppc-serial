#include "lua_qlibrary.h"
#include <luabind/adopt_policy.hpp>
#include <luabind/out_value_policy.hpp>


extern lua_State* __pL;
QString lqinvoker_makecall(QInvoker* w, const QString& input)
{
    QString result;
    int res;
    res = w->make_call(input, result);
    return result;
}

QByteArray lqinvoker_makecal2(QInvoker* w, const QByteArray& input)
{
    QByteArray result;
    int res;
    res = w->make_call(input, result);
    return result;
}

LQInvoker lqinvoker()
{
    return
    class_<QInvoker>("QInvoker")
            .def(constructor<>())
            .def(constructor<void*>())
            .def(constructor<uint32_t>())

            .def("__call", lqinvoker_makecall)
            .def("__call", lqinvoker_makecal2)
            .property("value", &QInvoker::value)
            .property("result", &QInvoker::result)
            ;
}



ENUM_FILTER(QLibrary,loadHints,setLoadHints)

void lqlibrary_setFileNameAndVersion1(QLibrary* w, const QString& fileName, const QString& version)
{
    w->setFileNameAndVersion(fileName, version);
}

void lqlibrary_setFileNameAndVersion2(QLibrary* w, const QString& fileName, int version)
{
    w->setFileNameAndVersion(fileName, version);
}

QInvoker lqlibrary_resolve(QLibrary* w, const char* symbol)
{
    void* r = w->resolve(symbol);
    return QInvoker(r);
}

QInvoker lqlibrary_resolve1(const QString& fileName, const char* symbol)
{
    void* r = QLibrary::resolve(fileName, symbol);
    return QInvoker(r);
}

QInvoker lqlibrary_resolve2(const QString& fileName, int version, const char* symbol)
{
    void* r = QLibrary::resolve(fileName, version, symbol);
    return QInvoker(r);
}

QInvoker lqlibrary_resolve3(const QString& fileName, const QString& version, const char* symbol)
{
    void* r = QLibrary::resolve(fileName, version, symbol);
    return QInvoker(r);
}

LQLibrary lqlibrary()
{
    return
    class_<QLibrary, QObject>("QLibrary")
            .def(constructor<>())
            .def(constructor<QObject*>())
            .def(constructor<const QString&>())
            .def(constructor<const QString&, QObject*>())
            .def(constructor<const QString&, int>())
            .def(constructor<const QString&, int, QObject*>())
            .def(constructor<const QString&, const QString&>())
            .def(constructor<const QString&, const QString&, QObject*>())

            .def("load", &QLibrary::load)
            .def("setFileNameAndVersion", lqlibrary_setFileNameAndVersion1)
            .def("setFileNameAndVersion", lqlibrary_setFileNameAndVersion2)
            .def("resolve", lqlibrary_resolve)


            .property("fileName", &QLibrary::fileName, &QLibrary::setFileName)
            .property("loadHints", QLibrary_loadHints, QLibrary_setLoadHints)
            .property("isLoaded", &QLibrary::isLoaded)

            .scope[
                def("isLibrary", &QLibrary::isLibrary),
                def("resolve", lqlibrary_resolve1),
                def("resolve", lqlibrary_resolve2),
                def("resolve", lqlibrary_resolve3)
            ]
            ;
}

