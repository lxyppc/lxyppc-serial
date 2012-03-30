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

function LuaEditDlg:__init()
   QDialog.__init(self)
   self.windowTitle = "Lua Editor [*]"
   self.path = " "
   self {  minw = 800, minh = 400 }
   self.editor = QLuaEdit()
   self.layout = QHBoxLayout{
       QVBoxLayout{
           QPushButton("&New"){ clicked = {self, self.new}, QKeySequence("Ctrl+N") },
           QPushButton("&Open"){ clicked = {self, self.open}, QKeySequence("Ctrl+O") },
           QPushButton("&Save"){ clicked = {self, self.save}, QKeySequence("Ctrl+S") },
           QPushButton("&Save as"){ clicked = {self, self.saveAs}, QKeySequence("Ctrl+Shift+S") },
           QLabel(),
           "0,0,0,0,1",
       },
       self.editor,
   }
   self.editor.textChanged = {self, self.changed}
   self.windowModified = false
end
