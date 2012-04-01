#ifndef CONVERTER_H
#define CONVERTER_H

Q_DECLARE_METATYPE(luabind::object)

struct QVariant_wrapper{
    QVariant variant()const{ return m_var;}
    void setVariant(const QVariant& var){ m_var = var;}
private:
    QVariant m_var;
};
template<typename T>bool is_class(const luabind::object& obj);
//  leave the function body empty,this will cause a compile error when type no defined in lua_qobject.cpp
//{ return false;}

QVariant var_from(lua_State* L, int index);
void var_to(lua_State* L, QVariant const& v);

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





template <>
struct default_converter<QByteArray>
  : native_converter_base<QByteArray>
{
    static int compute_score(lua_State* L, int index)
    {
        return lua_type(L, index) == LUA_TTABLE ? 0 : -1;
    }

    QByteArray from(lua_State* L, int index)
    {
        object obj(luabind::from_stack(L,index));
        QByteArray arr;
        for(iterator i(obj),e; i!=e; ++i){
            int v = 0;
            if(type(*i) == LUA_TNUMBER){
                v = object_cast<int>(*i);
            }
            arr.append((char)v);
        }
        return arr;
    }

    void to(lua_State* L, QByteArray const& arr)
    {
        object obj = luabind::newtable(L);
        for(int i=0;i<arr.length();i++){
            obj[i+1] = (int)arr.at(i);
        }
        obj.push(L);
    }
};

template <>
struct default_converter<QByteArray const&>
  : default_converter<QByteArray>
{};



//template <>
//struct default_converter<QVariant>
//  : native_converter_base<QVariant>
//{
//    static int compute_score(lua_State* L, int index)
//    {
//        lua_type(L, index);
//        return 0;
//    }
//
//    QVariant from(lua_State* L, int index)
//    {
//        return var_from(L,index);
//    }
//
//    void to(lua_State* L, QVariant const& v)
//    {
//        var_to(L,v);
//    }
//};
//
//template <>
//struct default_converter<QVariant const&>
//  : default_converter<QVariant>
//{};

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
QT_EMUN_CONVERTER(QMessageBox::StandardButtons)
QT_EMUN_CONVERTER(QFileDialog::Options)


struct QMainWindow_wrap : QMainWindow, wrap_base
{
};

}

#endif
