function edit_script()
    editor = LuaEditor()
    editor.windowTitle = "Lua Script Editor";
    editor:loadScript("../src/script.lua");
    editor:show();
end

function do_something()
    edit_script()
end

function init_mainwindow(mainwindow)
    local scriptMenu = mainwindow:menuBar():insertMenu(0, "脚本");
    local scriptEditAct = scriptMenu:addAction(QIcon("xx.png"),"编辑...");
    scriptEditAct.triggered = {mainwindow, mainwindow.showMaximized} -- edit_script;
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
    t = {

    --[[
        modified = false,
        maxh = 600,
        maxw = 800,
        minh = 200,
        minw = 300,
        --]]
        geometry = QRect{ x = 300, y = 200,  w = 600, h = 400,},
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
        LuaEditor(),
        QAction("789"){ triggered = do_something },
        --[[QDockWidget("cccc"){
            titlebar = LuaEditor(),
            LuaEditor()
        },--]]
    }
    me.title = "sfdsgsfdhds"
    tb.allowedAreas = 8
    mainwindow (t)
    tp = QTestType();
    print (tp.showText);
    --table.foreach(t, function(i, v) print (i, v) end)
end
