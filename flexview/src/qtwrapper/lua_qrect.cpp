#include "lua_qt_wrapper.hpp"

static setter_map<QPoint> lqpoint_set_map;
static setter_map<QRect> lqrect_set_map;
static setter_map<QSize> lqsize_set_map;
static setter_map<QMargins> lqmargins_set_map;

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

template<>
void table_init_general<QMargins>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QMargins>(arg), obj, lqmargins_set_map);
}

QPoint* lqpoint_init(QPoint* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqpoint_set_map);
}
QRect* lqrect_init(QRect* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqrect_set_map);
}
QSize* lqsize_init(QSize* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqsize_set_map);
}
QMargins* lqmargins_init(QMargins* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqmargins_set_map);
}

LQPoint lqpoint()
{
    return
    myclass_<QPoint>("QPoint", lqpoint_set_map)
    .def(constructor<>())
    .def(constructor<int,int>())
    .def("__call", &lqpoint_init)
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
    .def("__call", &lqrect_init)
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
    .def("__call", &lqsize_init)
    .def("__init", &table_init_general<QSize>)

    .property("width", &QSize::width, &QSize::setWidth)
    .property("height", &QSize::height, &QSize::setHeight)
    .property("w", &QSize::width, &QSize::setWidth)
    .property("h", &QSize::height, &QSize::setHeight)
    ;
}

LQMargins lqmargins()
{
    return
    myclass_<QMargins>("QMargins", lqmargins_set_map)
    .def(constructor<>())
    .def(constructor<int,int,int,int>())
    .def("__call", &lqmargins_init)
    .def("__init", &table_init_general<QMargins>)

    .property("left", &QMargins::left, &QMargins::setLeft)
    .property("right", &QMargins::right, &QMargins::setRight)
    .property("top", &QMargins::top, &QMargins::setTop)
    .property("bottom", &QMargins::bottom, &QMargins::setBottom)
    ;
}
