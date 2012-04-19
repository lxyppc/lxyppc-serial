dofile("../src/editor.lua")
dofile("../src/serialview.lua")

mainWindow{
 x = 50, y = 50,
 w = 1000, h = 700
}

function EditScript()
    dlg = LuaEditDlg(mainWindow)
    dlg.windowIcon = mainWindow.windowIcon
    dlg:load("../src/script.lua")
    dlg:exec()
    logEdit.plainText = dlg.editor.html
end

function LaunchSerial()
    mdiArea:addSubWindow(SerialView()):showMaximized()
end

logEdit:append("Script started...")
menubar = mainWindow:menuBar()
menubar:addMenu("&File"){
    QAction("&Serial Viewer ..."){
        triggered = LaunchSerial
    },
}

editMenu = menubar:addMenu("&Edit")
actEdit = editMenu:addAction("&Edit script...")
actEdit.statusTip = "Edit the default script file"
actClear = editMenu:addAction("&Clear Log")
actClear.statusTip = "Clear scrip execute log"

actEdit.triggered = EditScript
actClear.triggered = {logEdit,logEdit.clear}

function log(v)
    logEdit:append(tostring(v))
end

windowMenu = menubar:addMenu("&Window")
closeAct = QAction("Cl&ose", mainWindow){ triggered = {mdiArea, mdiArea.closeActiveSubWindow}}
closeAllAct = QAction("Close &All", mainWindow){ triggered = {mdiArea, mdiArea.closeAllSubWindows}}
tileAct = QAction("&Tile", mainWindow){ triggered = {mdiArea, mdiArea.tileSubWindows}}
cascadeAct = QAction("&Cascade", mainWindow){ triggered = {mdiArea, mdiArea.cascadeSubWindows}}
windowMenu.aboutToShow = function()
    local list = mdiArea:subWindowList()
    windowMenu:clear()
    windowMenu:addAction(closeAct)
    windowMenu:addAction(closeAllAct)
    windowMenu:addSeparator()
    windowMenu:addAction(tileAct)
    windowMenu:addAction(cascadeAct)
    windowMenu:addSeparator()
    table.foreach(list, function(k,v)
        local act = windowMenu:addAction(k .. " " .. v.windowTitle)
        act.checkable = true
        act.checked = mdiArea.currentSubWindow == v
        act.data = {window = v}
    end)
end

windowMenu.triggered = function(ac)
    if ac.data.window then
        mdiArea:setActiveSubWindow(ac.data.window)
    end
end

icon = mainWindow.windowIcon

frm2 = QFrame{
w=800,h=600
}

sp = QSplitter(frm2)
sp2 = QSplitter(2,frm2)
sp2:addWidget(QDial(frm2))
sp2:addWidget(QTextEdit(frm2))
sp:addWidget(QDial(frm2))
sp:addWidget(sp2)
sp:addWidget(QTextEdit(frm2))
mdiArea:addSubWindow(frm2){w=800,h=600}:show()

log(QHostAddress(4).protocol)


