#include "lua_qrect.h"
static setter_map<QPoint> lqpoint_set_map;
static setter_map<QRect> lqrect_set_map;
static setter_map<QSize> lqsize_set_map;
static setter_map<QMargins> lqmargins_set_map;
static setter_map<QColor> lqcolor_set_map;
static setter_map<QBrush> lqbrush_set_map;
static setter_map<QFont> lqfont_set_map;

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

template<>
void table_init_general<QColor>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QColor>(arg), obj, lqcolor_set_map);
}

template<>
void table_init_general<QBrush>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QBrush>(arg), obj, lqbrush_set_map);
}

template<>
void table_init_general<QFont>(const luabind::argument & arg, const object& obj)
{
    lq_general_init(construct<QFont>(arg), obj, lqfont_set_map);
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
QColor* lqcolor_init(QColor* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqcolor_set_map);
}

QBrush* lqbrush_init(QBrush* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqbrush_set_map);
}

QFont* lqfont_init(QFont* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqfont_set_map);
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

LQColor lqcolor()
{
    return
    myclass_<QColor>("QColor", lqcolor_set_map)
    .def(constructor<>())
    .def(constructor<Qt::GlobalColor>())
    .def(constructor<int,int,int>())
    .def(constructor<int,int,int,int>())
    .def(constructor<const QString&>())
    .def(constructor<const QColor&>())
    .def("__call", &lqcolor_init)
    .def("__init", &table_init_general<QColor>)

    .property("red", &QColor::red, &QColor::setRed)
    .property("green", &QColor::green, &QColor::setGreen)
    .property("blue", &QColor::blue, &QColor::setBlue)
    .property("r", &QColor::red, &QColor::setRed)
    .property("g", &QColor::green, &QColor::setGreen)
    .property("b", &QColor::blue, &QColor::setBlue)
    .property("name", &QColor::name, &QColor::setNamedColor)
    ;
}


void lqbursh_set_style(QBrush* f, int s)
{
    f->setStyle(Qt::BrushStyle(s));
}

int lqbursh_get_style(QBrush* f)
{
    return f->style();
}
LQBrush  lqbrush()
{
    return
    myclass_<QBrush>("QBrush", lqbrush_set_map)
    .def(constructor<>())
    .def(constructor<Qt::BrushStyle>())
    .def(constructor<const QColor &>())
    .def(constructor<const QColor &, Qt::BrushStyle>())
    .def(constructor<Qt::GlobalColor>())
    .def(constructor<Qt::GlobalColor, Qt::BrushStyle>())
    .def("__call", &lqbrush_init)
    .def("__init", &table_init_general<QBrush>)
    .def("setColor", (void(QBrush::*)(Qt::GlobalColor))&QBrush::setColor)

    .property("color", &QBrush::color, (void(QBrush::*)(const QColor&))&QBrush::setColor)
    .property("style", lqbursh_get_style, lqbursh_set_style)
    ;
}


void lqfont_set_cap(QFont* f, int cap)
{
    f->setCapitalization(QFont::Capitalization( cap));
}

int lqfont_get_cap(QFont* f)
{
    return f->capitalization();
}

void lqfont_set_style(QFont* f, int s)
{
    f->setStyle(QFont::Style(s));
}

int lqfont_get_style(QFont* f)
{
    return f->style();
}

LQFont lqfont()
{
    return
    myclass_<QFont>("QFont", lqfont_set_map)
    .def(constructor<>())
    .def(constructor<const QFont &>())
    .def(constructor<const QString &>())
    .def(constructor<const QString &,int>())
    .def(constructor<const QString &,int,int>())
    .def(constructor<const QString &,int,int,bool>())
    .def("__call", &lqfont_init)
    .def("__init", &table_init_general<QFont>)

    .property("family", &QFont::family, &QFont::setFamily)
    .property("bold", &QFont::bold, &QFont::setBold)
    .property("capitalization", lqfont_get_cap, lqfont_set_cap)
    .property("fixedPitch", &QFont::fixedPitch, &QFont::setFixedPitch)
    .property("italic", &QFont::italic, &QFont::setItalic)
    .property("kerning", &QFont::kerning, &QFont::setKerning)
    .property("overline", &QFont::overline, &QFont::setOverline)
    .property("pixelSize", &QFont::pixelSize, &QFont::setPixelSize)
    .property("pointSize", &QFont::pointSize, &QFont::setPointSize)
    .property("stretch", &QFont::stretch, &QFont::setStretch)
    .property("strikeOut", &QFont::strikeOut, &QFont::setStrikeOut)
    .property("style", lqfont_get_style, lqfont_set_style)
    .property("underline", &QFont::underline, &QFont::setUnderline)
    .property("weight", &QFont::weight, &QFont::setWeight)
    .property("wordSpacing", &QFont::wordSpacing, &QFont::setWordSpacing)
    ;
}
