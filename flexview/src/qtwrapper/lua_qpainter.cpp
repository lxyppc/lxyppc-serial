#include "lua_qpainter.h"
#include "luabind/tag_function.hpp"
#include "luabind/out_value_policy.hpp"
namespace luabind{
template <>
struct default_converter<QPolygon>
  : native_converter_base<QPolygon>
{
    static int compute_score(lua_State* L, int index)
    {
        return lua_type(L, index) == LUA_TTABLE ? 0 : -1;
    }

    QPolygon from(lua_State* L, int index)
    {
        object obj(luabind::from_stack(L,index));
        QPolygon arr;
        for(iterator i(obj),e; i!=e; ++i){
            QPoint v;
            if(type(*i) == LUA_TSTRING){
                v = object_cast<QPoint>(*i);
                arr.append(v);
            }
        }
        return arr;
    }

    void to(lua_State* L, QPolygon const& arr)
    {
        object obj = luabind::newtable(L);
        for(int i=0;i<arr.count();i++){
            obj[i+1] = arr.at(i);
        }
        obj.push(L);
    }
};

template <>
struct default_converter<QPolygon const&>
  : default_converter<QPolygon>
{};
}

bool lqpainter_begin(QPainter* p, QWidget* w)
{
    return p->begin(w);
}

bool lqpainter_begin2(QPainter* p, QImage* w)
{
    return p->begin(w);
}

namespace luabind{
    QT_EMUN_CONVERTER(Qt::BGMode)
    QT_EMUN_CONVERTER(Qt::BrushStyle)
    QT_EMUN_CONVERTER(Qt::PenStyle)
    QT_EMUN_CONVERTER(QPainter::RenderHint)
    QT_EMUN_CONVERTER(QPainter::RenderHints)
    QT_EMUN_CONVERTER(Qt::FillRule)
    QT_EMUN_CONVERTER(Qt::SizeMode)
    QT_EMUN_CONVERTER(Qt::GlobalColor)
}


#define _r const QRect&
#define _ri int,int,int,int
#define _i int
#define _p const QPoint&
#define _pi int,int
#define _s const QString&
#define _g const QPolygon&
#define _l const QLine&
#define _vl const QVector<QLine>&
#define _vp const QVector<QPoint>&
#define _vr const QVector<QRect>&
#define _d qreal
#define _CT(a,arg...)        (void(QPainter::*)(a, ## arg))
#define _CF(a,arg...)        void(QPainter*, a, ## arg)

LQPainter lqpainter()
{
    return
    class_<QPainter>("QPainter")
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def(constructor<QImage*>())
    .def("begin", lqpainter_begin)
    .def("begin", lqpainter_begin2)
    //.def("end", &QPainter::end) /* end is a keyword in lua*/
    .def("done", &QPainter::end)
    .def("save", &QPainter::save)
    .def("restore", &QPainter::restore)
    .def("boundingRect", (QRect(QPainter::*)(int,int,int,int,int,const QString&))&QPainter::boundingRect)
    .def("boundingRect", (QRect(QPainter::*)(const QRect&,int,const QString&))&QPainter::boundingRect)
    .def("scale", &QPainter::scale)
    .def("setPen", (void (QPainter::*)(const QPen&))&QPainter::setPen)
    .def("setPen", (void (QPainter::*)(const QColor&))&QPainter::setPen)
    .def("setPen", (void (QPainter::*)(Qt::PenStyle))&QPainter::setPen)
    .def("setBrush", (void (QPainter::*)(const QBrush&))&QPainter::setBrush)
    .def("setBrush", (void (QPainter::*)(Qt::BrushStyle))&QPainter::setBrush)
    .def("setBrushOrigin", (void (QPainter::*)(const QPoint&))&QPainter::setBrushOrigin)
    .def("setBrushOrigin", (void (QPainter::*)(int,int))&QPainter::setBrushOrigin)
    .def("setRenderHints", &QPainter::setRenderHints)
    .def("setRenderHint", &QPainter::setRenderHint)
    .def("setRenderHint", tag_function<void(QPainter*, QPainter::RenderHint)>(boost::bind(&QPainter::setRenderHint, _1, _2, true)))

    .property("brush", &QPainter::brush, (void (QPainter::*)(const QBrush&))&QPainter::setBrush)
    .property("brushOrigin", &QPainter::brushOrigin, (void (QPainter::*)(const QPoint&))&QPainter::setBrushOrigin)
    .property("font", &QPainter::font, &QPainter::setFont)
    .property("pen", &QPainter::pen, (void (QPainter::*)(const QPen&))&QPainter::setPen)
    .property("background", &QPainter::background, &QPainter::setBackground)
    .property("backgroundMode", &QPainter::backgroundMode, &QPainter::setBackgroundMode)
    .property("opacity", &QPainter::opacity, &QPainter::setOpacity)
    .property("renderHints", &QPainter::renderHints, tag_function<void(QPainter*, QPainter::RenderHints)>(boost::bind(&QPainter::setRenderHints, _1, _2, true)))

    .def("drawArc", _CT(_r,_i,_i)&QPainter::drawArc)
    .def("drawArc", _CT(_ri,_i,_i)&QPainter::drawArc)
    .def("drawChord", _CT(_r,_i,_i)&QPainter::drawChord)
    .def("drawChord", _CT(_ri,_i,_i)&QPainter::drawChord)
    .def("drawConvexPolygon", _CT(_g)&QPainter::drawConvexPolygon)
    .def("drawEllipse", _CT(_r)&QPainter::drawEllipse)
    .def("drawEllipse", _CT(_ri)&QPainter::drawEllipse)
    .def("drawEllipse", _CT(_p,_i,_i)&QPainter::drawEllipse)
    .def("drawLine", _CT(_l)&QPainter::drawLine)
    .def("drawLine", _CT(_p,_p)&QPainter::drawLine)
    .def("drawLine", _CT(_pi,_pi)&QPainter::drawLine)
    .def("drawLines", _CT(_vp)&QPainter::drawLines)
    .def("drawLines", _CT(_vl)&QPainter::drawLines)
    .def("drawPie", _CT(_r,_i,_i)&QPainter::drawPie)
    .def("drawPie", _CT(_ri,_i,_i)&QPainter::drawPie)
    .def("drawPoint", _CT(_p)&QPainter::drawPoint)
    .def("drawPoint", _CT(_pi)&QPainter::drawPoint)
    .def("drawPoints", _CT(_g)&QPainter::drawPoints)
    .def("drawPolygon", _CT(_g, Qt::FillRule)&QPainter::drawPolygon)
    .def("drawPolygon", tag_function<_CF(_g)>(boost::bind(_CT(_g, Qt::FillRule)&QPainter::drawPolygon,_1,_2, Qt::OddEvenFill) ) )
    .def("drawPolyline", _CT(_g)&QPainter::drawPolyline)
    .def("drawRect", _CT(_r)&QPainter::drawRect)
    .def("drawRect", _CT(_ri)&QPainter::drawRect)
    .def("drawRects", _CT(_vr)&QPainter::drawRects)
    .def("drawRoundedRect", _CT(_r,_d,_d,Qt::SizeMode)&QPainter::drawRoundedRect)
    .def("drawRoundedRect", _CT(_ri,_d,_d,Qt::SizeMode)&QPainter::drawRoundedRect)
    .def("drawRoundedRect", tag_function<_CF(_r,_d,_d)>(boost::bind(_CT(_r,_d,_d,Qt::SizeMode)&QPainter::drawRoundedRect,_1,_2,_3,_4,Qt::AbsoluteSize) ) )
    .def("drawRoundedRect", tag_function<_CF(_ri,_d,_d)>(boost::bind(_CT(_ri,_d,_d,Qt::SizeMode)&QPainter::drawRoundedRect,_1,_2,_3,_4,_5,_6,_7,Qt::AbsoluteSize) ) )
    .def("drawText", _CT(_p,_s)&QPainter::drawText)
    .def("drawText", _CT(_pi,_s)&QPainter::drawText)
    .def("drawText", _CT(_r,_i,_s,QRect*)&QPainter::drawText, pure_out_value(_5))
    .def("drawText", _CT(_ri,_i,_s,QRect*)&QPainter::drawText, pure_out_value(_8))
    .def("eraseRect", _CT(_r)&QPainter::eraseRect)
    .def("eraseRect", _CT(_ri)&QPainter::eraseRect)
    .def("fillRect", _CT(_r,const QBrush&)&QPainter::fillRect)
    .def("fillRect", _CT(_r,const QColor&)&QPainter::fillRect)
    .def("fillRect", _CT(_r,Qt::GlobalColor)&QPainter::fillRect)
    .def("fillRect", _CT(_r,Qt::BrushStyle)&QPainter::fillRect)
    .def("fillRect", _CT(_ri,const QBrush&)&QPainter::fillRect)
    .def("fillRect", _CT(_ri,const QColor&)&QPainter::fillRect)
    .def("fillRect", _CT(_ri,Qt::GlobalColor)&QPainter::fillRect)
    .def("fillRect", _CT(_ri,Qt::BrushStyle)&QPainter::fillRect)
    ;
}

