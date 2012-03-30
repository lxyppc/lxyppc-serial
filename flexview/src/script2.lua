class "XMainWindow" (QMainWindow)

function XMainWindow:__init()
    QMainWindow.__init(self)
    mdi = QMdiArea()
    self:setCentralWidget(mdi)
    mbar = self:menuBar()
    menu1 = QMenu('test2', self)
    menu2 = mbar:addMenu('test')
    mbar:addMenu(menu1)
    act = menu1:addAction('hello')
    connect(act,"triggered()", self, "testsignal()")
    connect(self,"testsignal()", self, "showMaximized()")
    connect(self,"testsignal()", self, "test()")
    connect(self,"strSignal(QString)", self, "strSlot(QString)")
    connect(self,"intSignal(int)", self, "intSlot(int)")
end

function XMainWindow:testslot()
    self:showMaximized()
end

function XMainWindow:test()
    print("test")
    self:strSignal("hello")
    self:intSignal(123);
end

function XMainWindow:test1()
    print("test1 0")
end

function testsignal2()
    print("test")
end

function XMainWindow:testsignal()
    emit_signal(self, "testsignal()");
end

function XMainWindow:strSignal(str)
    emit_signal(self, "strSignal(QString)", str);
end

function XMainWindow:strSlot(str)
    print(str);
end

function XMainWindow:intSignal(val)
    emit_signal(self, "intSignal(int)", val);
end

function XMainWindow:intSlot(val)
    print(val);
end

--[[
mainwindow = XMainWindow()
--mainwindow:test();
--mainwindow:testsignal()
mainwindow:setWindowTitle('123123')
--mainwindow:showMaximized()
mainwindow:show()
]]

class "SlotHolder" (QObject)

function SlotHolder:__init()
    QObject.__init(self)
end

slot_holder = SlotHolder()

function SlotHolder:edit_script()
    editor = LuaDialog()
    editor:setWindowTitle("Lua Script Editor");
    editor:show();
end

function init_mainwindow(mainwindow)
    menuBar = mainwindow:menuBar();
    scriptMenu = menuBar:addMenu("Script");
    scriptEditAct = scriptMenu:addAction("Edit...");
    connect(scriptEditAct,"triggered()", slot_holder, "edit_script()");
    --mdi = LuaDialog();
    --mainwindow:setCentralWidget(mdi)
    mainwindow:setGeometry(300,200,600,400)
end
