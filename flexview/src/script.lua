function edit_script()
    editor = LuaEditor()
    editor.windowTitle = "Lua Script Editor";
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
    mb = QMdiArea()
    t = {

    --[[
        modified = false,
        maxh = 600,
        maxw = 800,
        minh = 200,
        minw = 300,
        --]]
        x = 300,
        y = 200,
        w = 600,
        h = 400,
        --123,
        --456,
        --789,
        styleSheet = "  QMainWindow { background-color:darkblue } ",
        title = "Flex Data Viewer",
        --styleSheet = "  background-color:darkblue ",
        mb,
    }
    mainwindow (t)
    --table.foreach(t, function(i, v) print (i, v) end)
end
