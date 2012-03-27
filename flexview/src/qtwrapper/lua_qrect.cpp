#include "lua_qt_wrapper.hpp"

static setter_map<QPoint> lqpoint_set_map;
static setter_map<QRect> lqrect_set_map;
static setter_map<QSize> lqsize_set_map;

template<typename T>
T* lq_general_init(T* widget, const object& obj, setter_map<T> set_map)
{
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj), e; i != e; ++i){
            if(type(i.key()) == LUA_TSTRING){
                QString key = object_cast<QString>(i.key());
                if(set_map.find(key) != set_map.end()){
                    set_map[key](widget,*i);
                }
            }
        }
    }
    return widget;
}

template<typename T>
void table_init_general(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<T>(arg), obj, lqpoint_set_map);
}

template<>
void table_init_general<QPoint>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QPoint>(arg), obj, lqpoint_set_map);
}

template<>
void table_init_general<QRect>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QRect>(arg), obj, lqrect_set_map);
}

template<>
void table_init_general<QSize>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QSize>(arg), obj, lqsize_set_map);
}

LQPoint lqpoint()
{
    return
    myclass_<QPoint>("QPoint", lqpoint_set_map)
    .def(constructor<>())
    .def(constructor<int,int>())
    .def("__call", &lq_general_init<QPoint>)
    .def("__init", &table_init_general<QPoint>)

    .property("x", &QPoint::x, &QPoint::setX)
    .property("y", &QPoint::y, &QPoint::setY)
    ;
}
LQRect  lqrect()
{
    return
    myclass_<QRect>("QRect", lqrect_set_map)
    .def(constructor<>())
    .def(constructor<const QPoint &,const QPoint &>())
    .def(constructor<const QPoint &,const QSize &>())
    .def(constructor<int,int,int,int>())
    .def("__call", &lq_general_init<QRect>)
    .def("__init", &table_init_general<QRect>)
    .def("intersect", &QRect::intersect)
    .def("intersected", &QRect::intersected)
    .def("intersects", &QRect::intersects)
    .def("contains", (bool (QRect::*)(int, int, bool) const)&QRect::contains)
    .def("contains", (bool (QRect::*)(int, int) const)&QRect::contains)
    .def("contains", (bool (QRect::*)(const QPoint&, bool) const)&QRect::contains)
    .def("contains", (bool (QRect::*)(const QRect&, bool) const)&QRect::contains)

    .property("x", &QRect::x, &QRect::setX)
    .property("y", &QRect::y, &QRect::setY)
    .property("left", &QRect::left, &QRect::setLeft)
    .property("right", &QRect::right, &QRect::setRight)
    .property("width", &QRect::width, &QRect::setWidth)
    .property("height", &QRect::height, &QRect::setHeight)
    .property("w", &QRect::width, &QRect::setWidth)
    .property("h", &QRect::height, &QRect::setHeight)
    .property("top", &QRect::top, &QRect::setTop)
    .property("bottom", &QRect::bottom, &QRect::setBottom)
    .property("topLeft", &QRect::topLeft, &QRect::setTopLeft)
    .property("topRight", &QRect::topRight, &QRect::setTopRight)
    .property("bottomLeft", &QRect::bottomLeft, &QRect::setBottomLeft)
    .property("bottomRight", &QRect::bottomRight, &QRect::setBottomRight)
    .property("size", &QRect::size, &QRect::setSize)
    .property("center", &QRect::center)

    ;
}
LQSize  lqsize()
{
    return
    myclass_<QSize>("QSize", lqsize_set_map)
    .def(constructor<>())
    .def(constructor<int,int>())
    .def("__call", &lq_general_init<QSize>)
    .def("__init", &table_init_general<QSize>)

    .property("width", &QSize::width, &QSize::setWidth)
    .property("height", &QSize::height, &QSize::setHeight)
    .property("w", &QSize::width, &QSize::setWidth)
    .property("h", &QSize::height, &QSize::setHeight)
    ;
}

