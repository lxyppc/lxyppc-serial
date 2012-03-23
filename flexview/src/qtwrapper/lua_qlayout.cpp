#include "lua_qt_wrapper.hpp"
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

struct MyQLayout : public QLayout
{
    MyQLayout(){}
    MyQLayout(QWidget*){}
    virtual void addItem ( QLayoutItem * item ) {}
    virtual int	count () const {return 0;}
    virtual int	indexOf ( QWidget * widget ) const{return -1;}
    virtual QLayoutItem * itemAt ( int index ) const { return 0;}
    virtual QLayoutItem *	takeAt ( int index ) {return 0;}
    virtual QSize sizeHint() const {return QSize();}
    virtual QSize minimumSize() const {return QSize();}
    virtual QSize maximumSize() const {return QSize();}
    virtual Qt::Orientations expandingDirections() {return 0;}
    virtual void setGeometry(const QRect&) {}
    virtual QRect geometry() const { return QRect();}
    virtual bool isEmpty() const {return true;}
    virtual bool hasHeightForWidth() const{ return false;}
    virtual int heightForWidth(int) const{ return 0;}
    virtual int minimumHeightForWidth(int) const{ return 0;}
    virtual void invalidate(){}

    virtual QWidget *widget(){ return 0;}
    virtual QLayout *layout(){ return 0;}
    virtual QSpacerItem *spacerItem(){ return 0;}
};
MyQLayout x;
/*
LQLayout lqlayout()
{
    return
    class_<QLayout,QObject>("QLayout")
            .def(constructor<>())
            .def(constructor<QWidget*>())
    ;
}
*/
LQStackedLayout lqstatckedlayout()
{
    return
    class_<QStackedLayout, QLayout>("QStackedLayout")
        .def(constructor<>())
    ;
}
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();
LQBoxLayout  lqboxlayout()
{
    return
    class_<QBoxLayout, QLayout>("QBoxLayout")
        .def(constructor<QBoxLayout::Direction>())
        .def(constructor<QBoxLayout::Direction,QWidget*>())
        .def("addLayout", (void (QBoxLayout::*)(QLayout *))&QBoxLayout::addLayout)
        .def("addLayout", (void (QBoxLayout::*)(QLayout *, int))&QBoxLayout::addLayout)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *, int, Qt::Alignment)) &QBoxLayout::addWidget)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *, int)) &QBoxLayout::addWidget)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *)) &QBoxLayout::addWidget)
    ;
}

LQVBoxLayout lqvboxlayout()
{
    return
    class_<QVBoxLayout, QBoxLayout>("QVBoxLayout")
        .def(constructor<>())
        .def(constructor<QWidget*>())
    ;
}
LQHBoxLayout lqhboxlayout();

