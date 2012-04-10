#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addLog(const QString& log);

    QTextEdit* getLogEdit() const { return logText;}
    QMdiArea* getMdiArea()const { return mdi; }

public slots:
    void my_about();
private:
    QMdiArea* mdi;
    QTextEdit* logText;
};

#endif // MAINWINDOW_H
