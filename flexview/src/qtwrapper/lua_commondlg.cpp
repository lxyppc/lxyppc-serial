#include "lua_commondlg.h"

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

extern lua_State* __pL;


object getOpenFileNames2(object& selectedFilter, QWidget *parent = 0,
                        const QString &caption = QString(),
                        const QString &dir = QString(),
                        const QString &filter = QString(),
                        QFileDialog::Options options = 0)
{
    QString fit;
    object obj = luabind::newtable(__pL);
    QStringList r = QFileDialog::getOpenFileNames(parent,caption,dir,filter,&fit,options);
    for(int i=0;i<r.count(); i++){
        obj[i+1] = r.at(i).toStdString();
    }
    obj["filter"] = fit.toStdString();
    selectedFilter = obj["filter"];
    obj["filter"] = nil;
    return obj;
}


object getOpenFileNames(object& filter)
{
    return getOpenFileNames2(filter);
}

object getOpenFileNames(object& filter,const QString &caption)
{
    return getOpenFileNames2(filter, 0, caption);
}

object getOpenFileNames(object& filter,const QString &caption, const QString &dir)
{
    return getOpenFileNames2(filter, 0, caption, dir);
}

object getOpenFileNames(object& filter,const QString &caption, const QString &dir,const QString &fit)
{
    return getOpenFileNames2(filter, 0, caption, dir, fit);
}

object getOpenFileNames(object& filter,const QString &caption, const QString &dir,const QString &fit,QFileDialog::Options options)
{
    return getOpenFileNames2(filter, 0, caption, dir, fit, options);
}

object getOpenFileNames(object& filter, QWidget* w)
{
    return getOpenFileNames2(filter, w);
}

object getOpenFileNames(object& filter, QWidget* w,const QString &caption)
{
    return getOpenFileNames2(filter, w, caption);
}

object getOpenFileNames(object& filter, QWidget* w,const QString &caption, const QString &dir)
{
    return getOpenFileNames2(filter, w, caption, dir);
}

object getOpenFileNames(object& filter, QWidget* w,const QString &caption, const QString &dir,const QString &fit)
{
    return getOpenFileNames2(filter, w, caption, dir, fit);
}

object getOpenFileNames(object& filter, QWidget* w,const QString &caption, const QString &dir,const QString &fit,QFileDialog::Options options)
{
    return getOpenFileNames2(filter, w, caption, dir, fit, options);
}

QString getOpenFileName2(object& selectedFilter,
                         QWidget *parent = 0,
                         const QString &caption = QString(),
                         const QString &dir = QString(),
                         const QString &filter = QString(),
                         QFileDialog::Options options = 0)
{
    QString fit;
    QString res;
    res = QFileDialog::getOpenFileName(parent,caption,dir,filter,&fit,options);
    lua_pushstring(__pL, fit.toStdString().c_str());
    detail::stack_pop pop(__pL,1);
    selectedFilter = object(luabind::from_stack(__pL, -1));
    return res;
}

QString getOpenFileName(object& filter)
{
    return getOpenFileName2(filter);
}

QString getOpenFileName(object& filter,const QString &caption)
{
    return getOpenFileName2(filter, 0, caption);
}

QString getOpenFileName(object& filter,const QString &caption, const QString &dir)
{
    return getOpenFileName2(filter, 0, caption, dir);
}

QString getOpenFileName(object& filter,const QString &caption, const QString &dir,const QString &fit)
{
    return getOpenFileName2(filter, 0, caption, dir, fit);
}

QString getOpenFileName(object& filter,const QString &caption, const QString &dir,const QString &fit,QFileDialog::Options options)
{
    return getOpenFileName2(filter, 0, caption, dir, fit, options);
}

QString getOpenFileName(object& filter, QWidget* w)
{
    return getOpenFileName2(filter, w);
}

QString getOpenFileName(object& filter, QWidget* w,const QString &caption)
{
    return getOpenFileName2(filter, w, caption);
}

QString getOpenFileName(object& filter, QWidget* w,const QString &caption, const QString &dir)
{
    return getOpenFileName2(filter, w, caption, dir);
}

QString getOpenFileName(object& filter, QWidget* w,const QString &caption, const QString &dir,const QString &fit)
{
    return getOpenFileName2(filter, w, caption, dir, fit);
}

QString getOpenFileName(object& filter, QWidget* w,const QString &caption, const QString &dir,const QString &fit,QFileDialog::Options options)
{
    return getOpenFileName2(filter, w, caption, dir, fit, options);
}


QString getSaveFileName2(object& selectedFilter,
                         QWidget *parent = 0,
                         const QString &caption = QString(),
                         const QString &dir = QString(),
                         const QString &filter = QString(),
                         QFileDialog::Options options = 0)
{
    QString fit;
    QString res;
    res = QFileDialog::getSaveFileName(parent,caption,dir,filter,&fit,options);
    lua_pushstring(__pL, fit.toStdString().c_str());
    detail::stack_pop pop(__pL,1);
    selectedFilter = object(luabind::from_stack(__pL, -1));
    return res;
}

QString getSaveFileName(object& filter)
{
    return getSaveFileName2(filter);
}

QString getSaveFileName(object& filter,const QString &caption)
{
    return getSaveFileName2(filter, 0, caption);
}

QString getSaveFileName(object& filter,const QString &caption, const QString &dir)
{
    return getSaveFileName2(filter, 0, caption, dir);
}

QString getSaveFileName(object& filter,const QString &caption, const QString &dir,const QString &fit)
{
    return getSaveFileName2(filter, 0, caption, dir, fit);
}

QString getSaveFileName(object& filter,const QString &caption, const QString &dir,const QString &fit,QFileDialog::Options options)
{
    return getSaveFileName2(filter, 0, caption, dir, fit, options);
}

QString getSaveFileName(object& filter, QWidget* w)
{
    return getSaveFileName2(filter, w);
}

QString getSaveFileName(object& filter, QWidget* w,const QString &caption)
{
    return getSaveFileName2(filter, w, caption);
}

QString getSaveFileName(object& filter, QWidget* w,const QString &caption, const QString &dir)
{
    return getSaveFileName2(filter, w, caption, dir);
}

QString getSaveFileName(object& filter, QWidget* w,const QString &caption, const QString &dir,const QString &fit)
{
    return getSaveFileName2(filter, w, caption, dir, fit);
}

QString getSaveFileName(object& filter, QWidget* w,const QString &caption, const QString &dir,const QString &fit,QFileDialog::Options options)
{
    return getSaveFileName2(filter, w, caption, dir, fit, options);
}

QString getDir()
{
    return QFileDialog::getExistingDirectory();
}

QString getDir(const QString &caption)
{
    return QFileDialog::getExistingDirectory(0,caption);
}

QString getDir(const QString &caption,
               const QString &dir)
{
    return QFileDialog::getExistingDirectory(0,caption,dir);
}

QString getDir(const QString &caption,
               const QString &dir,
               QFileDialog::Options options)
{
    return QFileDialog::getExistingDirectory(0,caption,dir,options);
}

QString getDir(QWidget *parent)
{
    return QFileDialog::getExistingDirectory(parent);
}

QString getDir(QWidget *parent,
               const QString &caption)
{
    return QFileDialog::getExistingDirectory(parent,caption);
}

QString getDir(QWidget *parent,
               const QString &caption,
               const QString &dir)
{
    return QFileDialog::getExistingDirectory(parent,caption,dir);
}

QString getDir(QWidget *parent,
               const QString &caption,
               const QString &dir,
               QFileDialog::Options options)
{
    return QFileDialog::getExistingDirectory(parent,caption,dir,options);
}


QFont getFont(bool* ok)
{
    return QFontDialog::getFont(ok);
}

QFont getFont(bool* ok, QWidget* w)
{
    return QFontDialog::getFont(ok,w);
}

QFont getFont(bool* ok, const QFont& init)
{
    return QFontDialog::getFont(ok,init);
}

QFont getFont(bool* ok, const QFont& init, QWidget* w)
{
    return QFontDialog::getFont(ok,init,w);
}

QFont getFont(bool* ok, const QFont& init, QWidget* w, const QString& title)
{
    return QFontDialog::getFont(ok,init,w,title);
}

QFont getFont(bool* ok, const QFont& init, QWidget* w, const QString& title, int f)
{
    return QFontDialog::getFont(ok,init,w,title,QFontDialog::FontDialogOptions(f));
}


void about(QWidget* w, const QString& title,const QString& text)
{
    QMessageBox::about(w,title,text);
}

void about(const QString& title,const QString& text)
{
    QMessageBox::about(0,title,text);
}

QMessageBox::StandardButton critical(QWidget* w, const QString& title,const QString& text)
{
    return QMessageBox::critical(w,title,text);
}

QMessageBox::StandardButton critical(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::critical(w,title,text,btn);
}

QMessageBox::StandardButton critical(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::critical(w,title,text,btn,dbtn);
}

QMessageBox::StandardButton critical(const QString& title,const QString& text)
{
    return QMessageBox::critical(0,title,text);
}

QMessageBox::StandardButton critical(const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::critical(0,title,text,btn);
}

QMessageBox::StandardButton critical(const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::critical(0,title,text,btn,dbtn);
}

QMessageBox::StandardButton information(QWidget* w, const QString& title,const QString& text)
{
    return QMessageBox::information(w,title,text);
}

QMessageBox::StandardButton information(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::information(w,title,text,btn);
}

QMessageBox::StandardButton information(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::information(w,title,text,btn,dbtn);
}

QMessageBox::StandardButton information(const QString& title,const QString& text)
{
    return QMessageBox::information(0,title,text);
}

QMessageBox::StandardButton information(const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::information(0,title,text,btn);
}

QMessageBox::StandardButton information(const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::information(0,title,text,btn,dbtn);
}


QMessageBox::StandardButton question(QWidget* w, const QString& title,const QString& text)
{
    return QMessageBox::question(w,title,text);
}

QMessageBox::StandardButton question(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::question(w,title,text,btn);
}

QMessageBox::StandardButton question(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::question(w,title,text,btn,dbtn);
}

QMessageBox::StandardButton question(const QString& title,const QString& text)
{
    return QMessageBox::question(0,title,text);
}

QMessageBox::StandardButton question(const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::question(0,title,text,btn);
}

QMessageBox::StandardButton question(const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::question(0,title,text,btn,dbtn);
}


QMessageBox::StandardButton warning(QWidget* w, const QString& title,const QString& text)
{
    return QMessageBox::warning(w,title,text);
}

QMessageBox::StandardButton warning(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::warning(w,title,text,btn);
}

QMessageBox::StandardButton warning(QWidget* w, const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::warning(w,title,text,btn,dbtn);
}

QMessageBox::StandardButton warning(const QString& title,const QString& text)
{
    return QMessageBox::warning(0,title,text);
}

QMessageBox::StandardButton warning(const QString& title,const QString& text, QMessageBox::StandardButtons btn)
{
    return QMessageBox::warning(0,title,text,btn);
}

QMessageBox::StandardButton warning(const QString& title,const QString& text, QMessageBox::StandardButtons btn, QMessageBox::StandardButton dbtn)
{
    return QMessageBox::warning(0,title,text,btn,dbtn);
}


#define BTN_NAME(name)   case QMessageBox::name:  return  QString::fromLocal8Bit( #name);
QString buttonName(QMessageBox::StandardButton btn)
{
    switch(btn){
        BTN_NAME(Ok)
        BTN_NAME(Open)
        BTN_NAME(Save)
        BTN_NAME(Cancel)
        BTN_NAME(Close)
        BTN_NAME(Discard)
        BTN_NAME(Apply)
        BTN_NAME(Reset)
        BTN_NAME(RestoreDefaults)
        BTN_NAME(Help)
        BTN_NAME(SaveAll)
        BTN_NAME(Yes)
        BTN_NAME(YesToAll)
        BTN_NAME(No)
        BTN_NAME(NoToAll)
        BTN_NAME(Abort)
        BTN_NAME(Retry)
        BTN_NAME(Ignore)
        BTN_NAME(NoButton)
    default:
        break;
    }
    return QString::fromLocal8Bit("unknown");
}

LQCommonDlg  lqcommondlg()
{
    return
//    namespace_("QCommonDlg")
    class_<QCommonDlg>("QCommonDlg")
//    .def(constructor<>())
    .scope
    [
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
        def("getColor", (QColor (*)(const QColor &,QWidget *,const QString &, QColorDialog::ColorDialogOptions))getColor ),

        def("getOpenFileNames",(object (*)(object&))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,const QString &))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,const QString &, const QString &))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,const QString &, const QString &,const QString &))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,const QString &, const QString &,const QString &,QFileDialog::Options))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,QWidget*))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,QWidget*,const QString &))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,QWidget*,const QString &, const QString &))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,QWidget*,const QString &, const QString &,const QString &))getOpenFileNames, pure_out_value(_1)),
        def("getOpenFileNames",(object (*)(object&,QWidget*,const QString &, const QString &,const QString &,QFileDialog::Options))getOpenFileNames, pure_out_value(_1)),

        def("getOpenFileName",(QString (*)(object&))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,const QString &))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,const QString &, const QString &))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,const QString &, const QString &,const QString &))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,const QString &, const QString &,const QString &,QFileDialog::Options))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,QWidget*))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,QWidget*,const QString &))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,QWidget*,const QString &, const QString &))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,QWidget*,const QString &, const QString &,const QString &))getOpenFileName, pure_out_value(_1)),
        def("getOpenFileName",(QString (*)(object&,QWidget*,const QString &, const QString &,const QString &,QFileDialog::Options))getOpenFileName, pure_out_value(_1)),


        def("getSaveFileName",(QString (*)(object&))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,const QString &))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,const QString &, const QString &))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,const QString &, const QString &,const QString &))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,const QString &, const QString &,const QString &,QFileDialog::Options))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,QWidget*))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,QWidget*,const QString &))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,QWidget*,const QString &, const QString &))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,QWidget*,const QString &, const QString &,const QString &))getSaveFileName, pure_out_value(_1)),
        def("getSaveFileName",(QString (*)(object&,QWidget*,const QString &, const QString &,const QString &,QFileDialog::Options))getSaveFileName, pure_out_value(_1)),


        def("getDir", (QString(*)()) getDir ),
        def("getDir", (QString(*)(const QString &)) getDir ),
        def("getDir", (QString(*)(const QString &,const QString &)) getDir ),
        def("getDir", (QString(*)(const QString &,const QString &,QFileDialog::Options)) getDir ),
        def("getDir", (QString(*)(QWidget *)) getDir ),
        def("getDir", (QString(*)(QWidget *, const QString &)) getDir ),
        def("getDir", (QString(*)(QWidget *, const QString &,const QString &)) getDir ),
        def("getDir", (QString(*)(QWidget *, const QString &,const QString &,QFileDialog::Options)) getDir ),

        def("getFont", (QFont (*)(bool*))getFont,pure_out_value(_1)),
        def("getFont", (QFont (*)(bool*,QWidget*))getFont,pure_out_value(_1)),
        def("getFont", (QFont (*)(bool*,const QFont&))getFont,pure_out_value(_1)),
        def("getFont", (QFont (*)(bool*,const QFont&,QWidget*))getFont,pure_out_value(_1)),
        def("getFont", (QFont (*)(bool*,const QFont&,QWidget*,const QString&))getFont,pure_out_value(_1)),
        def("getFont", (QFont (*)(bool*,const QFont&,QWidget*,const QString&,int))getFont,pure_out_value(_1)),


        def("critical", (QMessageBox::StandardButton (*)(const QString& ,const QString& ))critical),
        def("critical", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons ))critical),
        def("critical", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))critical),
        def("critical", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& ))critical),
        def("critical", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons ))critical),
        def("critical", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))critical),

        def("information", (QMessageBox::StandardButton (*)(const QString& ,const QString& ))information),
        def("information", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons ))information),
        def("information", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))information),
        def("information", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& ))information),
        def("information", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons ))information),
        def("information", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))information),


        def("question", (QMessageBox::StandardButton (*)(const QString& ,const QString& ))question),
        def("question", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons ))question),
        def("question", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))question),
        def("question", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& ))question),
        def("question", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons ))question),
        def("question", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))question),


        def("warning", (QMessageBox::StandardButton (*)(const QString& ,const QString& ))warning),
        def("warning", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons ))warning),
        def("warning", (QMessageBox::StandardButton (*)(const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))warning),
        def("warning", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& ))warning),
        def("warning", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons ))warning),
        def("warning", (QMessageBox::StandardButton (*)(QWidget*, const QString& ,const QString& , QMessageBox::StandardButtons , QMessageBox::StandardButton ))warning),

        def("about", (void (*)(QWidget*, const QString&,const QString&))about),
        def("about", (void (*)(const QString&,const QString&))about),

        def("buttonName", buttonName)

    ]
    .enum_("Buttons")
    [
            value("Ok",QMessageBox::Ok),
            value("Open",QMessageBox::Open),
            value("Save",QMessageBox::Save),
            value("Cancel",QMessageBox::Cancel),
            value("Close",QMessageBox::Close),
            value("Discard",QMessageBox::Discard),
            value("Apply",QMessageBox::Apply),
            value("Reset",QMessageBox::Reset),
            value("RestoreDefaults",QMessageBox::RestoreDefaults),
            value("Help",QMessageBox::Help),
            value("SaveAll",QMessageBox::SaveAll),
            value("Yes",QMessageBox::Yes),
            value("YesToAll",QMessageBox::YesToAll),
            value("No",QMessageBox::No),
            value("NoToAll",QMessageBox::NoToAll),
            value("Abort",QMessageBox::Abort),
            value("Retry",QMessageBox::Retry),
            value("Ignore",QMessageBox::Ignore),
            value("NoButton",QMessageBox::NoButton)
    ]
;
}


