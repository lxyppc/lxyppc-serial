#include "luadialog.h"
#include "ui_luadialog.h"
#include <QDebug>
#include "luahighlighter.h"
#include <QFile>
#include <QFileDialog>

LuaDialog::LuaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LuaDialog)
{
    ui->setupUi(this);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    ui->editLua->setFont(font);

    LuaHighlighter *h = new LuaHighlighter(ui->editLua->document());
    h->addUserKeyword("CANFrame");

    qDebug()<<"create LuaDialog";

    path = QDir::currentPath();
}

bool LuaDialog::loadScript(const QString& name)
{
    QFile file(name);
    if(file.open(QFile::ReadOnly|QFile::Text)){
        ui->editLua->setPlainText(file.readAll().data());
        filePath = name;
        QFileInfo info(name);
        setWindowTitle(info.fileName());
        path = name;
        return true;
    }
    return false;
}

bool LuaDialog::newScript()
{
    ui->editLua->setPlainText("");
    setWindowTitle("Lua Script Editor");
    path = QDir::currentPath();
    filePath = "";
    return true;
}

bool LuaDialog::saveScript(const QString& name)
{
    QFile file(name);
    if(file.open(QFile::WriteOnly | QFile::Text)){
        QFileInfo info(name);
        setWindowTitle(info.fileName());
        path = name;
        file.write(ui->editLua->toPlainText().toAscii());
        filePath = name;
        return true;
    }
    return false;
}

void  LuaDialog::on_btnNew_clicked()
{
    newScript();
}

void  LuaDialog::on_btnOpen_clicked()
{
    QString name = QFileDialog::getOpenFileName(this,"Select a lua script file",path,"Lua Script(*.lua);;All Files(*.* *)");
    if(name.length()){
        loadScript(name);
    }
}

void  LuaDialog::on_btnSave_clicked()
{
    if(filePath.length()){
        saveScript(filePath);
    }else{
        on_btnSaveAs_clicked();
    }
}

void  LuaDialog::on_btnSaveAs_clicked()
{
    QString name = QFileDialog::getSaveFileName(this,"Select a lua script file",path,"Lua Script(*.lua);;All Files(*.* *)");
    saveScript(name);
}

LuaDialog::~LuaDialog()
{
    qDebug()<<"destroy LuaDialog";
    delete ui;
}

void LuaDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
local n;
b = {};
for n=1,8 do
  a = CANFrame.new();
  a:setData({1,2,3,4,5,6,7,8});
  a:setDLC(n);
  b[n] = a;
end
SendCANFrame(b);
*/


/** array in lua
   str = "123456";
   local t = {str:byte(1,-1)}
   */
#define CANFRAME "CANSpider.CANFrame"
