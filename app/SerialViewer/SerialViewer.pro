# -------------------------------------------------
# Project created by QtCreator 2011-10-27T22:50:22
# -------------------------------------------------
QT += core \
    gui
TARGET = SerialViewer
TEMPLATE = app
INCLUDEPATH += ../qextserialport
SOURCES += main.cpp \
    mainwindow.cpp \
    ../qextserialport/qextserialport.cpp \
    serialmonitor.cpp \
    serialhelper.cpp \
    ../hexeditor/commands.cpp \
    ../hexeditor/qhexedit.cpp \
    ../hexeditor/qhexedit_p.cpp \
    ../hexeditor/xbytearray.cpp
HEADERS += mainwindow.h \
    ../qextserialport/qextserialenumerator.h \
    ../qextserialport/qextserialport.h \
    serialmonitor.h \
    serialhelper.h \
    ../hexeditor/commands.h \
    ../hexeditor/qhexedit.h \
    ../hexeditor/qhexedit_p.h \
    ../hexeditor/xbytearray.h
unix:SOURCES += ../qextserialport/posix_qextserialport.cpp
unix:!macx:SOURCES += ../qextserialport/qextserialenumerator_unix.cpp
macx { 
    SOURCES += ../qextserialport/qextserialenumerator_osx.cpp
    LIBS += -framework \
        IOKit \
        -framework \
        CoreFoundation
}
win32 { 
    SOURCES += ../qextserialport/win_qextserialport.cpp \
        ../qextserialport/qextserialenumerator_win.cpp
    DEFINES += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
    LIBS += -lsetupapi
}
FORMS += BasicView.ui
