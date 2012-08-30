# -------------------------------------------------
# Project created by QtCreator 2012-03-22T13:33:06
# -------------------------------------------------
TARGET = XToolbox
TEMPLATE = app
QT += network
QT *= xml \
    opengl
TRANSLATIONS = chs.ts

 win32{ QTPLUGIN += qcncodecs \
 qjpcodecs \
 qkrcodecs \
 qtwcodecs
 }
SOURCES += ./src/main.cpp \
    ./src/mainwindow.cpp \
    src/qtwrapper/regclass.cpp \
    src/qtwrapper/qluaslot.cpp \
    src/qtwrapper/lua_qobject.cpp \
    src/qtwrapper/lua_qlayout.cpp \
    src/luahighlighter.cpp \
    src/luadialog.cpp \
    src/qtwrapper/lua_qaction.cpp \
    src/qtwrapper/lua_qmainwindow.cpp \
    src/qtwrapper/lua_qrect.cpp \
    src/qtwrapper/lua_qtextedit.cpp \
    src/qtwrapper/lua_qbutton.cpp \
    src/qtwrapper/lua_commondlg.cpp \
    src/qtwrapper/lua_qeditor.cpp \
    src/qluaedit.cpp \
    src/qtwrapper/lua_qlist.cpp \
    src/qtwrapper/lua_qdialog.cpp \
    src/qtwrapper/lua_qtabwidget.cpp \
    src/protowrapper/lua_serial.cpp \
    src/protowrapper/serialhelper.cpp \
    src/qtwrapper/lua_qevent.cpp \
    src/qtwrapper/lua_qspin.cpp \
    src/qtwrapper/lua_qpainter.cpp \
    src/qtwrapper/lua_qprocess.cpp \
    src/qtwrapper/lua_qslider.cpp \
    src/protowrapper/lua_socket.cpp \
    src/qtwrapper/lua_qurl.cpp \
    src/protowrapper/lua_usbhid.cpp \
    src/qtwrapper/lua_qfile.cpp \
    src/qtwrapper/lua_qftp.cpp \
    src/protowrapper/lua_qglviewer.cpp
HEADERS += ./src/mainwindow.h \
    src/qtwrapper/converter.hpp \
    src/qtwrapper/qluaslot.h \
    src/luahighlighter.h \
    src/luadialog.h \
    src/qluaedit.h \
    src/qtwrapper/lua_qt_wrapper.hpp \
    src/protowrapper/lua_serial.h \
    src/qtwrapper/lua_qevent.h \
    src/qtwrapper/lua_qspin.h \
    src/qtwrapper/lua_qpainter.h \
    src/qtwrapper/lua_qprocess.h \
    src/qtwrapper/lua_qslider.h \
    src/protowrapper/lua_socket.h \
    src/qtwrapper/lua_qurl.h \
    src/protowrapper/lua_usbhid.h \
    src/qtwrapper/lua_qfile.h \
    src/qtwrapper/lua_qftp.h \
    src/protowrapper/lua_qglviewer.h
HEADERS += ./qextserialport/qextserialenumerator.h \
    ./qextserialport/qextserialport.h

# -------------------------------------------------
# sources for hexeditor
# -------------------------------------------------
SOURCES += hexeditor/xbytearray.cpp \
    hexeditor/qhexedit_p.cpp \
    hexeditor/qhexedit.cpp \
    hexeditor/commands.cpp
HEADERS += hexeditor/xbytearray.h \
    hexeditor/qhexedit_p.h \
    hexeditor/qhexedit.h \
    hexeditor/commands.h

# -------------------------------------------------
# sources for lua
# -------------------------------------------------
SOURCES += lua-5.1.5/src/print.c \
    lua-5.1.5/src/lzio.c \
    lua-5.1.5/src/lvm.c \
    lua-5.1.5/src/lundump.c \
    lua-5.1.5/src/ltm.c \
    lua-5.1.5/src/ltablib.c \
    lua-5.1.5/src/ltable.c \
    lua-5.1.5/src/lstrlib.c \
    lua-5.1.5/src/lstring.c \
    lua-5.1.5/src/lstate.c \
    lua-5.1.5/src/lparser.c \
    lua-5.1.5/src/loslib.c \
    lua-5.1.5/src/lopcodes.c \
    lua-5.1.5/src/lobject.c \
    lua-5.1.5/src/loadlib.c \
    lua-5.1.5/src/lmem.c \
    lua-5.1.5/src/lmathlib.c \
    lua-5.1.5/src/llex.c \
    lua-5.1.5/src/liolib.c \
    lua-5.1.5/src/linit.c \
    lua-5.1.5/src/lgc.c \
    lua-5.1.5/src/lfunc.c \
    lua-5.1.5/src/ldump.c \
    lua-5.1.5/src/ldo.c \
    lua-5.1.5/src/ldebug.c \
    lua-5.1.5/src/ldblib.c \
    lua-5.1.5/src/lcode.c \
    lua-5.1.5/src/lbaselib.c \
    lua-5.1.5/src/lauxlib.c \
    lua-5.1.5/src/lapi.c

# -------------------------------------------------
# sources for luabind
# -------------------------------------------------
SOURCES += luabind/src/wrapper_base.cpp \
    luabind/src/weak_ref.cpp \
    luabind/src/stack_content_by_name.cpp \
    luabind/src/scope.cpp \
    luabind/src/pcall.cpp \
    luabind/src/open.cpp \
    luabind/src/object_rep.cpp \
    luabind/src/link_compatibility.cpp \
    luabind/src/inheritance.cpp \
    luabind/src/function.cpp \
    luabind/src/exception_handler.cpp \
    luabind/src/error.cpp \
    luabind/src/create_class.cpp \
    luabind/src/class_rep.cpp \
    luabind/src/class_registry.cpp \
    luabind/src/class_info.cpp \
    luabind/src/class.cpp

# -------------------------------------------------
# sources for qextserialport
# -------------------------------------------------
SOURCES += ./qextserialport/qextserialport.cpp
unix:SOURCES += ./qextserialport/posix_qextserialport.cpp
unix:!macx:SOURCES += ./qextserialport/qextserialenumerator_unix.cpp
macx { 
    SOURCES += ./qextserialport/qextserialenumerator_osx.cpp
    LIBS += -framework \
        IOKit \
        -framework \
        CoreFoundation
}
win32 { 
    SOURCES += ./qextserialport/win_qextserialport.cpp \
        ./qextserialport/qextserialenumerator_win.cpp \
        qusbhid/qusbhid.cpp \
        qusbhid/qusbhidenumerator.cpp
    HEADERS += qusbhid/qusbhidenumerator.h \
        qusbhid/qusbhid.h
    DEFINES += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
    LIBS += -lsetupapi \
        -lhid
    RC_FILE = ./res/app.rc
}

# sources for QGLViewer
HEADERS += QGLViewer/vec.h \
    QGLViewer/ui_VRenderInterface.Qt4.h \
    QGLViewer/ui_ImageInterface.Qt4.h \
    QGLViewer/quaternion.h \
    QGLViewer/qglviewer.h \
    QGLViewer/mouseGrabber.h \
    QGLViewer/manipulatedFrame.h \
    QGLViewer/manipulatedCameraFrame.h \
    QGLViewer/keyFrameInterpolator.h \
    QGLViewer/frame.h \
    QGLViewer/domUtils.h \
    QGLViewer/constraint.h \
    QGLViewer/config.h \
    QGLViewer/camera.h
SOURCES += QGLViewer/vec.cpp \
    QGLViewer/saveSnapshot.cpp \
    QGLViewer/quaternion.cpp \
    QGLViewer/qglviewer.cpp \
    QGLViewer/mouseGrabber.cpp \
    QGLViewer/manipulatedFrame.cpp \
    QGLViewer/manipulatedCameraFrame.cpp \
    QGLViewer/keyFrameInterpolator.cpp \
    QGLViewer/frame.cpp \
    QGLViewer/constraint.cpp \
    QGLViewer/camera.cpp
QT_VERSION = $$[QT_VERSION]
contains( QT_VERSION, "^4.*" ):FORMS *= QGLViewer/ImageInterface.Qt4.ui
else:FORMS *= QGLViewer/ImageInterface.Qt3.ui
contains( DEFINES, NO_VECTORIAL_RENDER ):message( Vectorial rendering disabled )
else { 
    contains( QT_VERSION, "^4.*" ):FORMS *= QGLViewer/VRenderInterface.Qt4.ui
    else:FORMS *= QGLViewer/VRenderInterface.Qt3.ui
    SOURCES *= QGLViewer/VRender/BackFaceCullingOptimizer.cpp \
        QGLViewer/VRender/BSPSortMethod.cpp \
        QGLViewer/VRender/EPSExporter.cpp \
        QGLViewer/VRender/Exporter.cpp \
        QGLViewer/VRender/FIGExporter.cpp \
        QGLViewer/VRender/gpc.cpp \
        QGLViewer/VRender/ParserGL.cpp \
        QGLViewer/VRender/Primitive.cpp \
        QGLViewer/VRender/PrimitivePositioning.cpp \
        QGLViewer/VRender/TopologicalSortMethod.cpp \
        QGLViewer/VRender/VisibilityOptimizer.cpp \
        QGLViewer/VRender/Vector2.cpp \
        QGLViewer/VRender/Vector3.cpp \
        QGLViewer/VRender/NVector3.cpp \
        QGLViewer/VRender/VRender.cpp
    VRENDER_HEADERS = QGLViewer/VRender/AxisAlignedBox.h \
        QGLViewer/VRender/Exporter.h \
        QGLViewer/VRender/gpc.h \
        QGLViewer/VRender/NVector3.h \
        QGLViewer/VRender/Optimizer.h \
        QGLViewer/VRender/ParserGL.h \
        QGLViewer/VRender/Primitive.h \
        QGLViewer/VRender/PrimitivePositioning.h \
        QGLViewer/VRender/SortMethod.h \
        QGLViewer/VRender/Types.h \
        QGLViewer/VRender/Vector2.h \
        QGLViewer/VRender/Vector3.h \
        QGLViewer/VRender/VRender.h
    HEADERS *= $${VRENDER_HEADERS}
}

# QGLView source end

# lua gl source

INCLUDEPATH += luagl/include
SOURCES *= \
    luagl/src/luagl_util.c \
    luagl/src/luagl.c \
    luagl/src/luaglu.c \
    luagl/src/luagl_const.c

HEADERS *= \
    luagl/include/luagl.h \
    luagl/include/luaglu.h
# lua gl source end

INCLUDEPATH += ./lua-5.1.5/src \
    ./luabind
QMAKE_CXXFLAGS += -Wno-ignored-qualifiers \
    -Wno-strict-aliasing
FORMS += src/luadialog.ui
OTHER_FILES += src/script.lua \
    src/serialview.lua \
    src/tcpview.lua \
    src/editor.lua \
    src/udpview.lua \
    src/ftp.lua \
    src/clocktree.lua \
    res/app.rc \
    src/hid.lua
RESOURCES += res.qrc
