#include <QtGui/QApplication>
#include "mainwindow.h"
#include "lua.hpp"


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
    ret = a.exec();
    lua_close(L);
    return ret;
}
