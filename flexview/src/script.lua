class "SlotHolder" (QObject)

function SlotHolder:__init()
    QObject.__init(self)
end

slot_holder = SlotHolder()

function SlotHolder:edit_script()
    editor = LuaDialog()
    editor:setWindowTitle("Lua Script Editor");
    editor:loadScript("../src/script.lua");
    editor:show();
end

function init_mainwindow(mainwindow)
    menuBar = mainwindow:menuBar();
    scriptMenu = menuBar:addMenu("Script");
    scriptEditAct = scriptMenu:addAction("Edit...");
    connect(scriptEditAct,"triggered()", slot_holder, "edit_script()");
    mainwindow:setGeometry(300,200,600,400)
end
