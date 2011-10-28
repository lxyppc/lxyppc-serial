#-------------------------------------------------
#
# Project created by QtCreator 2011-10-27T22:50:22
#
#-------------------------------------------------

QT       += core gui

TARGET = SerialViewer
TEMPLATE = app

INCLUDEPATH  += ../qextserialport

SOURCES += main.cpp\
        mainwindow.cpp \
    ../qextserialport/qextserialport.cpp

HEADERS  += mainwindow.h \
    ../qextserialport/qextserialenumerator.h \
    ../qextserialport/qextserialport.h



unix:SOURCES           += ../qextserialport/posix_qextserialport.cpp
unix:!macx:SOURCES     += ../qextserialport/qextserialenumerator_unix.cpp
macx {
  SOURCES          += ../qextserialport/qextserialenumerator_osx.cpp
  LIBS             += -framework IOKit -framework CoreFoundation
}

win32 {
  SOURCES          += ../qextserialport/win_qextserialport.cpp ../qextserialport/qextserialenumerator_win.cpp
  DEFINES          += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
  LIBS             += -lsetupapi
}











#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -llibqextserialportd1
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -llibqextserialportd1
#else:symbian: LIBS += -llibqextserialportd1
#else:unix: LIBS += -L$$PWD/../lib/ -llibqextserialportd1

#INCLUDEPATH += $$PWD/../qextserialport
#DEPENDPATH += $$PWD/../qextserialport

















