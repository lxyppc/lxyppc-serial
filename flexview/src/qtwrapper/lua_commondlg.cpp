#include "lua_qt_wrapper.hpp"
#include <luabind/out_value_policy.hpp>
#include <luabind/iterator_policy.hpp>

int get_int(const QString & title, const QString & label, bool *ok)
{
    return QInputDialog::getInt(0,title,label,0,-2147483647,2147483647,1,ok,0);
}

int get_int(const QString & title, const QString & label, bool *ok, int value)
{
    return QInputDialog::getInt(0,title,label,value,-2147483647,2147483647,1,ok,0);
}

int get_int(const QString & title, const QString & label, bool *ok, int value, int minValue)
{
    return QInputDialog::getInt(0,title,label,value,minValue,2147483647,1,ok,0);
}

int get_int(const QString & title, const QString & label, bool *ok, int value,
            int minValue, int maxValue)
{
    return QInputDialog::getInt(0,title,label,value,minValue,maxValue,1,ok,0);
}

int get_int(const QString & title, const QString & label, bool *ok, int value,
            int minValue, int maxValue,
            int step)
{
    return QInputDialog::getInt(0,title,label,value,minValue,maxValue,step,ok,0);
}

int get_int(const QString & title, const QString & label, bool *ok, int value,
            int minValue, int maxValue,
            int step, Qt::WindowFlags flags)
{
    return QInputDialog::getInt(0,title,label,value,minValue,maxValue,step,ok,flags);
}

int get_int(QWidget* w, const QString & title, const QString & label, bool *ok)
{
    return QInputDialog::getInt(w,title,label,0,-2147483647,2147483647,1,ok,0);
}

int get_int(QWidget* w, const QString & title, const QString & label, bool *ok, int value)
{
    return QInputDialog::getInt(w,title,label,value,-2147483647,2147483647,1,ok,0);
}

int get_int(QWidget* w, const QString & title, const QString & label, bool *ok, int value, int minValue)
{
    return QInputDialog::getInt(w,title,label,value,minValue,2147483647,1,ok,0);
}

int get_int(QWidget* w, const QString & title, const QString & label, bool *ok, int value,
            int minValue, int maxValue)
{
    return QInputDialog::getInt(w,title,label,value,minValue,maxValue,1,ok,0);
}

int get_int(QWidget* w, const QString & title, const QString & label, bool *ok, int value,
            int minValue, int maxValue,
            int step)
{
    return QInputDialog::getInt(w,title,label,value,minValue,maxValue,step,ok,0);
}

int get_int(QWidget* w, const QString & title, const QString & label, bool *ok, int value,
            int minValue, int maxValue,
            int step, Qt::WindowFlags flags)
{
    return QInputDialog::getInt(w,title,label,value,minValue,maxValue,step,ok,flags);
}


double get_Double(const QString & title, const QString & label, bool *ok)
{
    return QInputDialog::getDouble(0,title,label,0,-2147483647,2147483647,1,ok,0);
}

double get_Double(const QString & title, const QString & label, bool *ok, double value)
{
    return QInputDialog::getDouble(0,title,label,value,-2147483647,2147483647,1,ok,0);
}

double get_Double(const QString & title, const QString & label, bool *ok, double value, double minValue)
{
    return QInputDialog::getDouble(0,title,label,value,minValue,2147483647,1,ok,0);
}

double get_Double(const QString & title, const QString & label, bool *ok, double value,
            double minValue, double maxValue)
{
    return QInputDialog::getDouble(0,title,label,value,minValue,maxValue,1,ok,0);
}

double get_Double(const QString & title, const QString & label, bool *ok, double value,
            double minValue, double maxValue,
            int step)
{
    return QInputDialog::getDouble(0,title,label,value,minValue,maxValue,step,ok,0);
}

double get_Double(const QString & title, const QString & label, bool *ok, double value,
            double minValue, double maxValue,
            int step, Qt::WindowFlags flags)
{
    return QInputDialog::getDouble(0,title,label,value,minValue,maxValue,step,ok,flags);
}

double get_Double(QWidget* w, const QString & title, const QString & label, bool *ok)
{
    return QInputDialog::getDouble(w,title,label,0,-2147483647,2147483647,1,ok,0);
}

double get_Double(QWidget* w, const QString & title, const QString & label, bool *ok, double value)
{
    return QInputDialog::getDouble(w,title,label,value,-2147483647,2147483647,1,ok,0);
}

double get_Double(QWidget* w, const QString & title, const QString & label, bool *ok, double value, double minValue)
{
    return QInputDialog::getDouble(w,title,label,value,minValue,2147483647,1,ok,0);
}

double get_Double(QWidget* w, const QString & title, const QString & label, bool *ok, double value,
            double minValue, double maxValue)
{
    return QInputDialog::getDouble(w,title,label,value,minValue,maxValue,1,ok,0);
}

double get_Double(QWidget* w, const QString & title, const QString & label, bool *ok, double value,
            double minValue, double maxValue,
            int step)
{
    return QInputDialog::getDouble(w,title,label,value,minValue,maxValue,step,ok,0);
}

double get_Double(QWidget* w, const QString & title, const QString & label, bool *ok, double value,
            double minValue, double maxValue,
            int step, Qt::WindowFlags flags)
{
    return QInputDialog::getDouble(w,title,label,value,minValue,maxValue,step,ok,flags);
}




QString getText(const QString &title, const QString &label, bool* ok)
{
    return QInputDialog::getText(0, title, label, QLineEdit::Normal, QString(),ok);
}

QString getText(const QString &title, const QString &label, bool* ok, QLineEdit::EchoMode echo)
{
    return QInputDialog::getText(0, title, label, echo, QString(), ok);
}

QString getText(const QString &title, const QString &label, bool* ok, QLineEdit::EchoMode echo, const QString& text)
{
    return QInputDialog::getText(0, title, label, echo, text, ok);
}

QString getText(const QString &title, const QString &label, bool* ok, QLineEdit::EchoMode echo, const QString& text, Qt::WindowFlags flags)
{
    return QInputDialog::getText(0, title, label, echo, text, ok, flags);
}

QString getText(QWidget* w, const QString &title, const QString &label, bool* ok)
{
    return QInputDialog::getText(w, title, label, QLineEdit::Normal, QString(),ok);
}

QString getText(QWidget* w, const QString &title, const QString &label, bool* ok, QLineEdit::EchoMode echo)
{
    return QInputDialog::getText(w, title, label, echo, QString(),ok);
}

QString getText(QWidget* w, const QString &title, const QString &label, bool* ok, QLineEdit::EchoMode echo, const QString& text)
{
    return QInputDialog::getText(w, title, label, echo, text,ok);
}

QString getText(QWidget* w, const QString &title, const QString &label, bool* ok, QLineEdit::EchoMode echo, const QString& text, Qt::WindowFlags flags)
{
    return QInputDialog::getText(w, title, label, echo, text, ok, flags);
}

QString get_Item(QWidget *parent, const QString &title, const QString &label,
                 const object &obj, bool *ok = 0, int current = 0, bool editable = true,
                 Qt::WindowFlags flags = 0)
{
    QStringList items;
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            if(type(*i) == LUA_TSTRING){
                items.append( object_cast<QString>(*i) );
            }
        }
    }
    return QInputDialog::getItem(parent,title,label,items,current,editable,ok,flags);
}

QString getItem(const QString &title, const QString &label, const object& obj, bool* ok)
{
    return get_Item(0,title,label,obj,ok);
}

QString getItem(const QString &title, const QString &label, const object& obj, bool* ok, int current)
{
    return get_Item(0,title,label,obj,ok,current);
}

QString getItem(const QString &title, const QString &label, const object& obj, bool* ok, int current, bool editable)
{
    return get_Item(0,title,label,obj,ok,current,editable);
}

QString getItem(const QString &title, const QString &label, const object& obj, bool* ok, int current, bool editable, Qt::WindowFlags flags)
{
    return get_Item(0,title,label,obj,ok,current,editable, flags);
}

QString getItem(QWidget* w, const QString &title, const QString &label, const object& obj, bool* ok)
{
    return get_Item(w,title,label,obj,ok);
}

QString getItem(QWidget* w, const QString &title, const QString &label, const object& obj, bool* ok, int current)
{
    return get_Item(w,title,label,obj,ok,current);
}

QString getItem(QWidget* w, const QString &title, const QString &label, const object& obj, bool* ok, int current, bool editable)
{
    return get_Item(w,title,label,obj,ok,current,editable);
}

QString getItem(QWidget* w, const QString &title, const QString &label, const object& obj, bool* ok, int current, bool editable, Qt::WindowFlags flags)
{
    return get_Item(w,title,label,obj,ok,current,editable, flags);
}


QColor getColor()
{
    return QColorDialog::getColor();
}

QColor getColor(const QColor &initial)
{
    return QColorDialog::getColor(initial);
}

QColor getColor(const QColor &initial, QWidget *parent)
{
    return QColorDialog::getColor(initial,parent);
}

QColor getColor(const QColor &initial, QWidget *parent, const QString &title)
{
    return QColorDialog::getColor(initial,parent,title);
}

QColor getColor(const QColor &initial, QWidget *parent, const QString &title,
                           QColorDialog::ColorDialogOptions options)
{
    return QColorDialog::getColor(initial,parent,title,options);
}

std::vector<std::string> getOpenFileNames()
{
    std::vector<std::string> xxx;
    //xxx.clear();
    QStringList r = QFileDialog::getOpenFileNames();
    foreach(const QString& s , r){
        xxx.push_back(s.toStdString());
    }
    return xxx;
}


struct GetFileNames
{
    GetFileNames(){
        names = QFileDialog::getOpenFileNames();
        foreach(const QString& s , names){
            //char* p = new char[strlen(s.toStdString().c_str()) + 1];
            //strcpy(p, s.toStdString().c_str());
            names2.push_back(s.toStdString());
        }
    }
    QStringList names;
    std::vector<std::string> names2;
};

LQCommonDlg  lqcommondlg()
{
    return
    namespace_("QCommonDlg")
//    class_<QCommonDlg>("QCommonDlg")
//    .def(constructor<>())
//    .scope
    [
        class_<GetFileNames>("getOpenFileNames")
            .def(constructor<>())
            .def_readonly("names", &GetFileNames::names2, return_stl_iterator),
        def("getInt",(int(*)(QWidget*,const QString &, const QString &,bool*))get_int, pure_out_value(_4)),
        def("getInt",(int(*)(QWidget*,const QString &, const QString &,bool*,int))get_int,pure_out_value(_4)),
        def("getInt",(int(*)(QWidget*,const QString &, const QString &,bool*,int,int))get_int,pure_out_value(_4)),
        def("getInt",(int(*)(QWidget*,const QString &, const QString &,bool*,int,int,int))get_int, pure_out_value(_4)),
        def("getInt",(int(*)(QWidget*,const QString &, const QString &,bool*,int,int,int,int))get_int,pure_out_value(_4)),
        def("getInt",(int(*)(QWidget*,const QString &, const QString &,bool*,int,int,int,int,Qt::WindowFlags))get_int, pure_out_value(_4)),
        def("getInt",(int(*)(const QString &, const QString &,bool*))get_int, pure_out_value(_3)),
        def("getInt",(int(*)(const QString &, const QString &,bool*,int))get_int,pure_out_value(_3)),
        def("getInt",(int(*)(const QString &, const QString &,bool*,int,int))get_int,pure_out_value(_3)),
        def("getInt",(int(*)(const QString &, const QString &,bool*,int,int,int))get_int, pure_out_value(_3)),
        def("getInt",(int(*)(const QString &, const QString &,bool*,int,int,int,int))get_int,pure_out_value(_3)),
        def("getInt",(int(*)(const QString &, const QString &,bool*,int,int,int,int,Qt::WindowFlags))get_int, pure_out_value(_3)),

        def("getDouble",(double(*)(QWidget*,const QString &, const QString &,bool*))get_Double, pure_out_value(_4)),
        def("getDouble",(double(*)(QWidget*,const QString &, const QString &,bool*,double))get_Double,pure_out_value(_4)),
        def("getDouble",(double(*)(QWidget*,const QString &, const QString &,bool*,double,double))get_Double,pure_out_value(_4)),
        def("getDouble",(double(*)(QWidget*,const QString &, const QString &,bool*,double,double,double))get_Double, pure_out_value(_4)),
        def("getDouble",(double(*)(QWidget*,const QString &, const QString &,bool*,double,double,double,int))get_Double,pure_out_value(_4)),
        def("getDouble",(double(*)(QWidget*,const QString &, const QString &,bool*,double,double,double,int,Qt::WindowFlags))get_Double, pure_out_value(_4)),
        def("getDouble",(double(*)(const QString &, const QString &,bool*))get_Double, pure_out_value(_3)),
        def("getDouble",(double(*)(const QString &, const QString &,bool*,double))get_Double,pure_out_value(_3)),
        def("getDouble",(double(*)(const QString &, const QString &,bool*,double,double))get_Double,pure_out_value(_3)),
        def("getDouble",(double(*)(const QString &, const QString &,bool*,double,double,double))get_Double, pure_out_value(_3)),
        def("getDouble",(double(*)(const QString &, const QString &,bool*,double,double,double,int))get_Double,pure_out_value(_3)),
        def("getDouble",(double(*)(const QString &, const QString &,bool*,double,double,double,int,Qt::WindowFlags))get_Double, pure_out_value(_3)),

        def("getText", (QString (*)(const QString &,const QString&,bool*))getText, pure_out_value(_3)),
        def("getText", (QString (*)(const QString &,const QString&,bool*,QLineEdit::EchoMode))getText, pure_out_value(_3)),
        def("getText", (QString (*)(const QString &,const QString&,bool*,QLineEdit::EchoMode,const QString&))getText, pure_out_value(_3)),
        def("getText", (QString (*)(const QString &,const QString&,bool*,QLineEdit::EchoMode,const QString&,Qt::WindowFlags))getText, pure_out_value(_3)),
        def("getText", (QString (*)(QWidget*,const QString &,const QString&,bool*))getText, pure_out_value(_4)),
        def("getText", (QString (*)(QWidget*,const QString &,const QString&,bool*,QLineEdit::EchoMode))getText, pure_out_value(_4)),
        def("getText", (QString (*)(QWidget*,const QString &,const QString&,bool*,QLineEdit::EchoMode,const QString&))getText, pure_out_value(_4)),
        def("getText", (QString (*)(QWidget*,const QString &,const QString&,bool*,QLineEdit::EchoMode,const QString&,Qt::WindowFlags))getText, pure_out_value(_4)),


        def("getItem", (QString (*)(const QString &, const QString &, const object&, bool*))getItem, pure_out_value(_4)),
        def("getItem", (QString (*)(const QString &, const QString &, const object&, bool*, int))getItem, pure_out_value(_4)),
        def("getItem", (QString (*)(const QString &, const QString &, const object&, bool*, int, bool))getItem, pure_out_value(_4)),
        def("getItem", (QString (*)(const QString &, const QString &, const object&, bool*, int, bool, Qt::WindowFlags))getItem, pure_out_value(_4)),
        def("getItem", (QString (*)(QWidget*, const QString &, const QString &, const object&, bool*))getItem, pure_out_value(_5)),
        def("getItem", (QString (*)(QWidget*, const QString &, const QString &, const object&, bool*, int))getItem, pure_out_value(_5)),
        def("getItem", (QString (*)(QWidget*, const QString &, const QString &, const object&, bool*, int, bool))getItem, pure_out_value(_5)),
        def("getItem", (QString (*)(QWidget*, const QString &, const QString &, const object&, bool*, int, bool, Qt::WindowFlags))getItem, pure_out_value(_5)),

        def("getColor", (QColor (*)())getColor ),
        def("getColor", (QColor (*)(const QColor &))getColor ),
        def("getColor", (QColor (*)(const QColor &,QWidget *))getColor ),
        def("getColor", (QColor (*)(const QColor &,QWidget *,const QString &))getColor ),
        def("getColor", (QColor (*)(const QColor &,QWidget *,const QString &, QColorDialog::ColorDialogOptions))getColor )

        //def("getOpenFileNames",getOpenFileNames, return_stl_iterator)
    ]
;
}


