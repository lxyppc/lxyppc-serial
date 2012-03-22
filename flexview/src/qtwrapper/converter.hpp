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
        return QString(str);
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


struct QMainWindow_wrap : QMainWindow, wrap_base
{
};

}

#endif
