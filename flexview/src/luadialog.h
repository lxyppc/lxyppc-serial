#ifndef LUADIALOG_H
#define LUADIALOG_H

#include <QDialog>
#include "lua.hpp"

namespace Ui {
    class LuaDialog;
}

class LuaDialog : public QDialog {
    Q_OBJECT
public:
    LuaDialog(QWidget *parent = 0);
    ~LuaDialog();
    bool loadScript(const QString& filePath);
    bool newScript();
    bool saveScript(const QString& filePath);

protected slots:
    void  on_btnNew_clicked();
    void  on_btnOpen_clicked();
    void  on_btnSave_clicked();
    void  on_btnSaveAs_clicked();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::LuaDialog *ui;
    QString filePath;
    QString path;
};

#endif // LUADIALOG_H
