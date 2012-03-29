function edit_script()
    editor = LuaEditor()
    editor.windowTitle = "Lua Script Editor";
    editor:loadScript("../src/script.lua");
    editor:show();
    --res, ok = QCommonDlg.getDouble(editor, "get", "double", 34, 2, 324, 3)
    --res, ok = QCommonDlg.getText(editor, "get", "Text", 1)
    res, ok = QCommonDlg.getItem(editor, "get", "Text", {"123", "456"})
    print(res, ok)
end

function do_something(f)
    print("do_something",f)
    edit_script()

end

function init_mainwindow(mainwindow)
    local scriptMenu = mainwindow:menuBar():insertMenu(0, "??");
    local scriptEditAct = scriptMenu:addAction(QIcon("xx.png"),"??...");
    scriptEditAct.triggered = {mainwindow, "showMaximized"} -- edit_script;
    --vl = QVBoxLayout(mainwindow)
    --editor = LuaEditor()
    --vl:addWidget(editor);
    --mainwindow:setLayout(vl)
    mb = QMdiArea()
    me = QMenu("Hello")
    me1 = QMenu("Hello")
    me2 = QMenu("Hello")

    tb = QToolBar("123") {
        scriptEditAct,
        QAction("xxx") { QIcon("xx.png") },
        QAction("yyy") { QIcon("xx.png") },
    }

    tb2 = QToolBar("456") {
        scriptEditAct,
        QAction("xxx") { QIcon("xx.png") },
        QAction("yyy") { QIcon("xx.png") },
    }

    btn = QPushButton("xxxx")
    {
        --text = "uuuu",
        QKeySequence("Alt+T"),
        QIcon("xx.png"),
        clicked = do_something,
        QMenu{ QAction("xxx") },
        --minh = 180,
        styleSheet = " QPushButton {background-color: #ff0000}",
    }

    btn { --QKeySequence("Alt+O"),
    --styleSheet = " QPushButton {background-color: #ff0000}"
    }
    --print (btn)
    --s = btn.shortcut -- = QKeySequence("Alt+T")
    --sm = btn:getMenu()
    --print (btn)

    frame = QFrame();
    hlayout = QVBoxLayout{
        QHBoxLayout{
            QVBoxLayout{
                QLabel("IP Address"),
                QLineEdit{ inputMask = "000.000.000.000;_" },
            },
            QVBoxLayout{
                QLabel("Mac Address"),
                QLineEdit{ inputMask = "HH:HH:HH:HH:HH:HH;_" },
            },
            QPushButton{
                text = "123",
                clicked = do_something,

            },
            QCheckBox{
                text = "456",
                toggled = do_something,
            },
            btn,
            QLabel(),
            "0,0,0,0,0,1"
        },
        QTextEdit(),

    }

    --hlayout:addWidget(LuaEditor());
    --hlayout:addWidget(LuaEditor());
    frame {
        layout = hlayout
    }

    --QCommonDlg.getInt(editor,2)

    t = {

    --[[
        modified = false,
        maxh = 600,
        maxw = 800,
        minh = 200,
        minw = 300,
        --]]
        geometry = QRect{ x = 300, y = 200,  w = 600, h = 200,},
        --123,
        --456,
        --789,
        --styleSheet = "  QMainWindow { background-color:darkblue } ",
        title = "Flex Data Viewer",
        --styleSheet = "  background-color:darkblue ",
        tb,
        mb,
        me,
        QMenuBar {
            "zzz"
        },
        QMenu("123"),
        QMenu("456"){
            QAction(){ text = "xxx", triggered = do_something}
        },
        QDockWidget{
        frame,
        },
        QAction("789"){ triggered = do_something, QMenu{ QAction("111"), QAction("222")}, QKeySequence("Alt+F") },
        --[[QDockWidget("cccc"){
            titlebar = LuaEditor(),
            LuaEditor()
        },--]]
    }
    me.title = "sfdsgsfdhds"
    tb.allowedAreas = 8
    rect = QRect { x= 400, y = 300, w = 400, h = 300 }
    --print (rect)
    mainwindow (t)
    --mainwindow.geometry = rect
    tp = QTestType();
    print (tp.showText);
    --table.foreach(t, function(i, v) print (i, v) end)
end
