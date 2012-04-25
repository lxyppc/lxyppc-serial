dofile("../src/editor.lua")
dofile("../src/serialview.lua")
dofile("../src/tcpview.lua")
dofile("../src/udpview.lua")

mainWindow{
 x = 50, y = 50,
 w = 1000, h = 700
}

function LookColor(obj,text,color)
    log(color)
    log(text)
end

function EditScript()
    dlg = LuaEditDlg(mainWindow)
    dlg.windowIcon = mainWindow.windowIcon
    dlg:load("../src/script.lua")
    dlg:exec()
end

function LaunchSerial()
    mdiArea:addSubWindow(SerialView()):showMaximized()
end

function LaunchTcpClient()
    mdiArea:addSubWindow(TcpClientView()):showMaximized()
end

function LaunchTcpServer()
    mdiArea:addSubWindow(TcpServerView()):showMaximized()
end

function LaunchUdp()
    mdiArea:addSubWindow(UdpView()):showMaximized()
end

logEdit:append("Script started...")
menubar = mainWindow:menuBar()
menubar:addMenu("&File"){
    QAction("&Serial Viewer"){
        triggered = LaunchSerial
    },
    QAction("TCP &Client"){
        triggered = LaunchTcpClient
    },
    QAction("TCP &Server"){
        triggered = LaunchTcpServer
    },
    QAction("&UDP Socket"){
        triggered = LaunchUdp
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

frm2 = QFrame()

function onPaint(obj,evt)
    pt = QPainter()
    pt:begin(frm2)
    mainWindow.windowIcon:paint(pt,0,0,frm2.w,frm2.h)
    pt:done()
    return true
end

frm2.eventFilter = QPaintEvent.filter(onPaint)

mdiArea:addSubWindow(frm2){minw=16,minh=16}

--QCommonDlg.about(mainWindow,"Toolbox",'<p><b>Toolbox</b></p><p>by lxyppc</p><table href="mailto:lxyppc@163.com" name=xxx>lxyppc@163.com</table>')
