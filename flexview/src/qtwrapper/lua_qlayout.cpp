#include "lua_qlayout.h"
using namespace luabind;

/*
LQLayout lqlayout()
{
    return
    class_<QLayout,QObject>("QLayout")
            .def(constructor<>())
            .def(constructor<QWidget*>())
            .def("activate",&QLayout::activate)
            .def("addWidget", &QLayout::addWidget)
            .def("contentsMargins", &QLayout::contentsMargins)
            .def("contentsRect", &QLayout::contentsRect)
            .def("getContentsMargins", &QLayout::getContentsMargins)
            .def("isEnabled", &QLayout::isEnabled)
            .def("count", &QLayout::count)
            .def("indexOf", &QLayout::indexOf)
            .def("menuBar", &QLayout::menuBar);
}
*/
//*
static setter_map<QLayout> lqlayout_set_map;
static setter_map<QVBoxLayout> lqvboxlayout_set_map;
static setter_map<QHBoxLayout> lqhboxlayout_set_map;
QLayout* lqlayout_init(QLayout* widget, const object& obj)
{
    return lq_general_init(widget, obj, lqlayout_set_map);
}


void setLayoutStretch(QBoxLayout* layout, const QString& strech)
{
    QStringList res = strech.split(QChar(','));
    int i = 0;
    foreach(const QString& s, res){
        bool ok = false;
        int stretch = s.toInt(&ok,10);
        if(ok && i<layout->count()){
            layout->setStretch(i,stretch);
            i++;
        }
    }
}

QString layoutStretch(QBoxLayout* layout)
{
    int cnt = layout->count();
    QString res;
    for(int i=0;i<cnt;i++){
        res += QString("%1,").arg(layout->stretch(i));
    }
    return res;
}

template<class T>
void addLayoutAndWidget(T* widget, const object& obj)
{
    if(type(obj) == LUA_TTABLE){
        for (iterator i(obj), e; i != e; ++i){
            if(is_class<QLayout>(*i)){
                widget->addLayout( object_cast<QLayout*>(*i));
            }else if(is_class<QString>(*i)){
                setLayoutStretch(widget, object_cast<QString>(*i));
            }else{
                QWidget* w = 0;
                try{ w = object_cast<QWidget*>(*i);}
                catch(...){}
                if(w){
                    widget->addWidget(w);
                }
            }
        }
    }
}

QVBoxLayout* lqvboxlayout_init(QVBoxLayout* widget, const object& obj)
{
    lq_general_init(widget, obj, lqvboxlayout_set_map);
    addLayoutAndWidget(widget, obj);
    return widget;
}

QHBoxLayout* lqhboxlayout_init(QHBoxLayout* widget, const object& obj)
{
    lq_general_init(widget, obj, lqhboxlayout_set_map);
    addLayoutAndWidget(widget, obj);
    return widget;
}

template<>
void table_init_general<QVBoxLayout>(const luabind::argument & arg, const object& obj)
{
    lqvboxlayout_init(construct<QVBoxLayout>(arg), obj);
}

template<>
void table_init_general<QHBoxLayout>(const luabind::argument & arg, const object& obj)
{
    lqhboxlayout_init(construct<QHBoxLayout>(arg), obj);
}

LQLayout lqlayout()
{
    return
    myclass_<QLayout,QLayoutWarp>("QLayout",lqlayout_set_map)
            .def(constructor<>())
            .def(constructor<QWidget*>())
            .def("setContentsMargins", (void (QLayout::*)(int,int,int,int))&QLayout::setContentsMargins)
            .def("addWidget", &QLayout::addWidget)
            .def("__call", lqlayout_init)

            .property("contentsMargins", &QLayout::contentsMargins, (void (QLayout::*)(const QMargins &))&QLayout::setContentsMargins)
            .property("spacing", &QLayout::spacing, &QLayout::setSpacing)
            .property("geometry", &QLayout::geometry, &QLayout::setGeometry)
    ;
}
//*/
LQStackedLayout lqstatckedlayout()
{
    return
    class_<QStackedLayout, QLayout>("QStackedLayout")
        .def(constructor<>())
    ;
}
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();

void lqboxlayout_add_widget(QBoxLayout* layout, QWidget* w)
{
    layout->addWidget(w,0,0);
}

void lqboxlayout_add_widget2(QBoxLayout* layout, QWidget* w, int stretch)
{
    layout->addWidget(w,stretch,0);
}
void lqboxlayout_add_layout(QBoxLayout* layout, QLayout* l)
{
    layout->addLayout(l,0);
}

LQBoxLayout  lqboxlayout()
{
    return
    class_<QBoxLayout, QLayout>("QBoxLayout")
        .def(constructor<QBoxLayout::Direction>())
        .def(constructor<QBoxLayout::Direction,QWidget*>())
        .def("addLayout", lqboxlayout_add_layout)
        .def("addLayout", (void (QBoxLayout::*)(QLayout *, int))&QBoxLayout::addLayout)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *, int, Qt::Alignment)) &QBoxLayout::addWidget)
        .def("addWidget", lqboxlayout_add_widget2)
        .def("addWidget", lqboxlayout_add_widget)
        .def("setStretch", &QBoxLayout::setStretch)
        .def("stretch", &QBoxLayout::stretch)
        .property("layoutStrech", layoutStretch, setLayoutStretch)
    ;
}

LQVBoxLayout lqvboxlayout()
{
    return
    class_<QVBoxLayout, QBoxLayout>("QVBoxLayout")
        .def(constructor<>())
        .def(constructor<QWidget*>())
        .def("__call", lqvboxlayout_init)
        .def("__init", table_init_general<QVBoxLayout>)
    ;
}
LQHBoxLayout lqhboxlayout()
{
    return
    class_<QHBoxLayout, QBoxLayout>("QHBoxLayout")
        .def(constructor<>())
        .def(constructor<QWidget*>())
        .def("__call", lqhboxlayout_init)
        .def("__init", table_init_general<QHBoxLayout>)
    ;
}

