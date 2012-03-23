function edit_script()
    editor = LuaEditor()
    editor:setWindowTitle("Lua Script Editor");
    editor:loadScript("../src/script.lua");
    editor:show();
end

function init_mainwindow(mainwindow)
    local scriptMenu = mainwindow:menuBar():insertMenu(0, "脚本");
    local scriptEditAct = scriptMenu:addAction(QIcon("xx.png"),"编辑...");
    scriptEditAct.triggered = edit_script;
    --vl = QVBoxLayout(mainwindow)
    --editor = LuaEditor()
    --vl:addWidget(editor);
    --mainwindow:setLayout(vl)
    mainwindow {
        x = 300,
        y = 200,
        w = 600,
        h = 400,
        123,
        456,
        789,
        --styleSheet = "  MainWindow { background-color:gray }"
    }
end
