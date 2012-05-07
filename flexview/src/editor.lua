class "LuaEditDlg" (QDialog)
function LuaEditDlg:open()
    name = QCommonDlg.getOpenFileName("Open Lua Script file",self.path, "Lua Script(*.lua);;All Files(*)")
    self:load(name)
end

function LuaEditDlg:save()
    file = io.open(self.path, "w+")
    if file then
        file:write(self.editor.plainText)
        file:close()
        self.windowModified = false
    else
        self:saveAs()
    end
end

function LuaEditDlg:saveAs()
    name = QCommonDlg.getSaveFileName("Open Lua Script file",self.path, "Lua Script(*.lua);;All Files(*)")
    file = io.open(name,"w+")
    if file then
        self.path = name
        file:write(self.editor.plainText)
        self.windowModified = false
        file:close()
    end
end

function LuaEditDlg:changed()
    self.windowModified = true
end

function LuaEditDlg:new()
    self.editor:clear()
    self.path = ""
    self.windowModified = false
end

function LuaEditDlg:load(name)
    file = io.open(name,"r")
    if file then
        self.path = name
        self.editor.plainText = file:read("*a")
        self.windowModified = false
        file:close()
    end
end

function LuaEditDlg:test()
    assert(loadstring(self.editor.plainText))()
end

function LuaEditDlg:toTag()
    self.editor:setTag("clas","[color=#800080]","[/color]")
    self.editor:setTag("key","[color=#0000FF]","[/color]")
    self.editor:setTag("quo","[color=#C80000]","[/color]")
    self.editor:setTag("com","[color=#008000]","[/color]")
    QApplication.clipboard():setText(self.editor.tagText)
end

function LuaEditDlg:__init(x)
    QDialog.__init(self,x)
    LuaEditDlg.__init(self)
end

function LuaEditDlg:__init()
   QDialog.__init(self)
   self.windowTitle = "Lua Editor [*]"
   self.path = " "
   self {  minw = 800, minh = 400 }
   self.editor = QLuaEdit()
   self.editor:addKeyWord("mainWindow")
   self.editor:addKeyWord("logEdit")
   self.editor:addKeyWord("qApp")

   self.layout = QHBoxLayout{
       QVBoxLayout{
           QPushButton("&New"){ clicked = {self, self.new}, QKeySequence("Ctrl+N"), toolTip = "Ctrl+N" },
           QPushButton("&Open"){ clicked = {self, self.open}, QKeySequence("Ctrl+O"), toolTip = "Ctrl+O" },
           QPushButton("&Save"){ clicked = {self, self.save}, QKeySequence("Ctrl+S"), toolTip = "Ctrl+S" },
           QPushButton("&Save as"){ clicked = {self, self.saveAs}, QKeySequence("Ctrl+Shift+S"), toolTip = "Ctrl+Shift+N" },
           QPushButton("to &BBS"){ clicked = {self, self.toTag}, QKeySequence("Ctrl+B"), toolTip = "Ctrl+B" },
           QLabel(),
           QPushButton("&Test"){ clicked = {self, self.test}, QKeySequence("Ctrl+T"), toolTip = "Ctrl+T"},
           "0,0,0,0,0,1,0",
       },
       self.editor,
   }
   self.editor.textChanged = {self, self.changed}
   self.windowModified = false
end
