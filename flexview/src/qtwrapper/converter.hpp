#ifndef CONVERTER_H
#define CONVERTER_H

namespace luabind {

template <>
struct default_converter<QString>
  : native_converter_base<QString>
{
    static int compute_score(lua_State* L, int index)
    {
        return lua_type(L, index) == LUA_TSTRING ? 0 : -1;
    }

    QString from(lua_State* L, int index)
    {
        size_t len;
        const char* str = lua_tolstring(L,index,&len);
        return QString::fromLocal8Bit(str);
    }

    void to(lua_State* L, QString const& x)
    {
        lua_pushstring(L, x.toStdString().c_str());
    }
};

template <>
struct default_converter<QString const&>
  : default_converter<QString>
{};


//template <>
//struct default_converter<Qt::ToolBarAreas>
//  : native_converter_base<Qt::ToolBarAreas>
//{
//    static int compute_score(lua_State* L, int index)
//    {
//        return lua_type(L, index) == LUA_TNUMBER ? 0 : -1;
//    }
//
//    Qt::ToolBarAreas from(lua_State* L, int index)
//    {
//        int x = lua_tonumber(L,index);
//        return Qt::ToolBarAreas(x);
//    }
//
//    void to(lua_State* L, Qt::ToolBarAreas x)
//    {
//        lua_pushnumber(L, x);
//    }
//};


#define QT_EMUN_CONVERTER(T)        \
template <>\
struct default_converter<T>\
  : native_converter_base<T>\
{\
    static int compute_score(lua_State* L, int index)\
    {\
        return lua_type(L, index) == LUA_TNUMBER ? 0 : -1;\
    }\
\
    T from(lua_State* L, int index)\
    {\
        int x = lua_tonumber(L,index);\
        return T(x);\
    }\
\
    void to(lua_State* L, T x)\
    {\
        lua_pushnumber(L, x);\
    }\
};

QT_EMUN_CONVERTER(Qt::ToolBarAreas)
QT_EMUN_CONVERTER(Qt::Orientation)
QT_EMUN_CONVERTER(Qt::DockWidgetAreas)
QT_EMUN_CONVERTER(QDockWidget::DockWidgetFeatures)
QT_EMUN_CONVERTER(Qt::Alignment)
QT_EMUN_CONVERTER(QKeySequence::StandardKey)
QT_EMUN_CONVERTER(Qt::CheckState)
QT_EMUN_CONVERTER(Qt::WindowFlags)


struct QMainWindow_wrap : QMainWindow, wrap_base
{
};

}

#endif
