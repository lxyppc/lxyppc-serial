#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->btnRun, SIGNAL(clicked()), this, SLOT(runFile()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(sendCommand()));
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(stdoutReady()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(stderrReady()));
    connect(process, SIGNAL(started()), this, SLOT(procStarted()));
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(procFinished(int,QProcess::ExitStatus)));
    connect(ui->btnClear, SIGNAL(clicked()), ui->textStderr, SLOT(clear()));
    connect(ui->btnClear, SIGNAL(clicked()), ui->textStdout, SLOT(clear()));
    connect(ui->btnClear, SIGNAL(clicked()), ui->textLog, SLOT(clear()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabCurrentChanged(int)));
    ui->tabWidget->setCurrentIndex(0);
    isRunning = false;
    ui->textPath->setText("c:/windows/system32/cmd.exe");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeEvent(QEvent *e)
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

void Dialog::tabCurrentChanged(int index)
{
    if(index == 0){
        ui->tabWidget->setTabText(0, "Stdout");
    }else if(index == 1){
        ui->tabWidget->setTabText(1, "Stderr");
    }
}

void Dialog::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, ui->textPath->text());
    if(!path.isEmpty()){
        ui->textPath->setText(path);
    }
}

void Dialog::runFile()
{
    if(isRunning){
        process->kill();
        isRunning = false;
    }else{
        process->start(ui->textPath->text());
        isRunning = true;
    }
}

void Dialog::sendCommand()
{
    process->write((ui->comboStdin->currentText()+"\r\n").toAscii());
    ui->comboStdin->clearEditText();
}

void Dialog::stdoutReady()
{
    ui->textStdout->append(
    QString(process->readAllStandardOutput())
    );
    QTextCursor c(ui->textStdout->textCursor());
    c.movePosition(QTextCursor::End);
    if(ui->tabWidget->currentIndex() != 0){
        ui->tabWidget->setTabText(0,"Stdout *");
    }
}

void Dialog::stderrReady()
{
    ui->textStderr->append(
    QString(process->readAllStandardError())
    );

    QTextCursor c(ui->textStderr->textCursor());
    c.movePosition(QTextCursor::End);
    if(ui->tabWidget->currentIndex() != 1){
        ui->tabWidget->setTabText(1,"Stderr *");
    }
}

void Dialog::procStarted()
{
    ui->btnRun->setText("Stop");
    logInfo(ui->textPath->text() + " started");
    isRunning = true;
}

void Dialog::procFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->btnRun->setText("Run");
    logInfo(ui->textPath->text() +
            tr(" finished. exitcode = %1, status = %2")
            .arg(exitCode)
            .arg(exitStatus?"Crash":"Normal"));
    isRunning = false;
}

void Dialog::logInfo(const QString& info)
{
    ui->textLog->append(QTime::currentTime().toString() + "  " + info);
    QTextCursor c(ui->textLog->textCursor());
    c.movePosition(QTextCursor::End);
}
