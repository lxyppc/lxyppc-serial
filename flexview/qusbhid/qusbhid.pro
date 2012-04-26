# -------------------------------------------------
# Project created by QtCreator 2012-03-22T13:33:06
# -------------------------------------------------
TARGET = usbhid
TEMPLATE = app
QT += network
SOURCES += main.cpp \
    mainwindow.cpp \
    qusbhidenumerator.cpp \
    qusbhid.cpp
HEADERS += mainwindow.h \
    qusbhidenumerator.h \
    qusbhid.h \
    qwineventnotifier_p.h

win32 {
    DEFINES += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
    LIBS += -lsetupapi -lhid
}
