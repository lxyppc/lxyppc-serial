#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void openFile();
    void runFile();
    void sendCommand();
    void stdoutReady();
    void stderrReady();
    void procStarted();
    void procFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void tabCurrentChanged(int index);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
    QProcess*  process;
    void logInfo(const QString& info);
};

#endif // DIALOG_H
