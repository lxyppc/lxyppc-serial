function edit_script()
    editor = LuaEditor()
    editor:setWindowTitle("Lua Script Editor");
    editor:loadScript("../src/script.lua");
    editor:show();
end

function init_mainwindow(mainwindow)
    local scriptMenu = mainwindow:menuBar():insertMenu(0, "½Å±¾");
    local scriptEditAct = scriptMenu:addAction(QIcon("xx.png"),"±à¼­...");
    scriptEditAct.triggered = edit_script;
    --vl = QVBoxLayout(mainwindow)
    --editor = LuaEditor()
    --vl:addWidget(editor);
    --mainwindow:setLayout(vl)
    xx =  {
        x = 300,
        y = 200,
        w = 600,
        h = 400,
        123,
        456,
        789,
        edit_script,
        styleSheet = "  MainWindow { background-color:gray }",
        QMainWindow {
            a = 1, b = 2, c = 3, d = 4
        }
    }
    mainwindow(xx)
    --table.foreach(xx, function (k,v) print(k,v) end)
end
