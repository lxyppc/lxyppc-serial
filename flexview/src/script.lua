dofile("../src/editor.lua")
dofile("../src/serialview.lua")
dofile("../src/tcpview.lua")
dofile("../src/udpview.lua")

mainWindow{
 x = 50, y = 50,
 w = 1000, h = 700
}

function EditScript()
    dlg = LuaEditDlg(mainWindow)
    dlg.windowIcon = mainWindow.windowIcon
    dlg:load("../src/clocktree.lua")
    dlg:show()
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

function onDrop(obj,evt)
    log("Drop")
    evt:acceptProposedAction()
    xx = evt.mimeData.formats
    log(xx)
    table.foreach(xx, function(k,v) log(v) end)
    return true
end

function onDragEnter(obj,evt)
    log("Drag enter")
    evt:acceptProposedAction()
    return true
end

frm2.acceptDrops = true
frm2.eventFilter = QPaintEvent.filter(onPaint)
frm2.eventFilter = QDropEvent.filter(onDrop)
frm2.eventFilter = QDragEnterEvent.filter(onDragEnter)
mdiArea:addSubWindow(frm2){minw=160,minh=160}

hid = QUsbHid(frm2)
hid:monitor(0x051a,0x511b)
hid.connected = function(v)
 log("connected" .. v.path)
end
hid.disconnected = function(v)
 log("disconnected" .. v.path)
end

devs = QUsbHid.enumDevices(0x051a,0x511b)
table.foreach(devs, function(k,v)
 log(v.path .. "||" .. v.friendName)
end)

hid.path = devs[1].path
res = hid:open()
log(res)
log(hid.caps.inputReportLength)
log(hid.caps.outputReportLength)
log(hid.caps.featureReportLength)
--hid:writeData({0,1,4,0xc6,0,0,0,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3})
--hid:writeData({0x03,4,0xc6,0,0,0,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3})
--hid:writeData({0x03,4,0xb6,0,0,0,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9})
len = hid:writeData({0x03,4,0xc6,0,0,0,})
log(len .. "|||" .. hid.errorString)
hid:close()

--[[
ftp = QFtp()
ftp.stateChanged = function (state)
    log(state)
end
ftp.listInfo = function (info)
    codec = QTextCodec.codecForName("GBK")
    log( codec:toUnicode(info.name) .. "     " .. info.owner)
end


url = QUrl("ftp://ftp.21ic.com")

ftp:connectToHost(url.host, url:getPort(21))
ftp:login("hotuser","250")
ftp:list()
ftp:close()
--]]
-- test

menubar{
    "menu1",
    "menu2",
    QMenu("menu3"){
        QAction("act1"),
        QAction("act2"),
        QMenu("menu4"){
            "act3",
            "act4",
        },
    },
}
