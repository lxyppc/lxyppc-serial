#include <QtGui/QApplication>
#include <QMutex>
#include "mainwindow.h"
#include "lua.hpp"

void run_script_init(MainWindow* mainwindow);
void register_classes(lua_State* L, char const* name = 0);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int ret = 0;
    lua_State* L = lua_open();
    luaL_openlibs(L);

    register_classes(L);

    MainWindow w;
    w.show();
    //run_script_init(0);
    ret = a.exec();
    //lua_close(L);
    return ret;
}

#ifdef Q_OS_WIN
#include <windows.h>
std::string fromQString(const QString& str)
{
    std::wstring sstr = str.toStdWString();
    int len = ::WideCharToMultiByte(CP_ACP,0,sstr.c_str(),-1,NULL,0,NULL,NULL);
    char *pStr = new char[len+1];
    ::WideCharToMultiByte(CP_ACP,0,sstr.c_str(),-1,pStr,len+1,NULL,NULL);
    std::string res(pStr);
    delete [] pStr;
    return res;
}

QString fromStdString(const std::string& str)
{
    return QString::fromStdString(str);
}

QString fromStdWString(const std::wstring& str)
{
    int len = ::WideCharToMultiByte(CP_ACP,0,str.c_str(),-1,NULL,0,NULL,NULL);
    char *pStr = new char[len+1];
    ::WideCharToMultiByte(CP_ACP,0,str.c_str(),-1,pStr,len+1,NULL,NULL);
    QString res = QString::fromLocal8Bit(pStr);
    delete [] pStr;
    return res;
}
#else
std::string fromQString(const QString& str)
{
    return str.toStdString();
}

QString fromStdString(const std::string& str)
{
    return QString::fromStdString(str);
}

QString fromStdWString(const std::wstring& str)
{
    return QString::fromStdString(str);
}
#endif
