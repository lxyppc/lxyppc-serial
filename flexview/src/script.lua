dofile("../src/editor.lua")
dofile("../src/serialview.lua")
dofile("../src/tcpview.lua")
dofile("../src/udpview.lua")

quickScript = QLuaEdit(mainWindow)
mainWindow{
 x = 50, y = 50,
 w = 1000, h = 700,
 QDockWidget("Quick Script"){
    quickScript
 }
}

function EditScript()
    dlg = LuaEditDlg(mainWindow)
    dlg.windowIcon = mainWindow.windowIcon
    dlg:load("../src/hid.lua")
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
actRun = editMenu:addAction("&Run script")
actRun.shortcut = QKeySequence("Ctrl+R")

actEdit.triggered = EditScript
actClear.triggered = {logEdit,logEdit.clear}
actRun.triggered = function()
    assert(loadstring(quickScript.plainText))()
end

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

--[[
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
len = hid:writeData({0x03,4,0xb6,0,0,0,})
log(len .. "|||" .. hid.errorString)
hid:close()
--]]
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
--[[
list = QTextCodec.availableCodecs()
for k,v in pairs(list) do
    log(v)
end
--]]

--[[
frm = QFrame{
    minW = 300, minH = 200,
    title = "Test",
    styleSheet = "QFrame{background-color:black}"
}

step = 3.1415926/50
start = 0

function timer_frm(obj,evt)
    start = start + step
    frm:update()
    return true
end

function paint_frm(obj,evt)
    local margin = 10
    local pt = QPainter()
    pt:begin(frm)
    pt:setBrush(QBrush(QColor("black")))
   -- pt:drawRect(0,0,frm.w,frm.h)
    pt:setPen(QColor("#00ff00"))
    pt:drawLine(margin,0,margin,frm.h)
    pt:drawLine(0,frm.h-margin,frm.w,frm.h-margin)
    pt:setPen(QColor("#ff83ff"))
    local scale = frm.h/3
    local st = start
    for i=1,frm.w do
        pt:drawPoint(i, frm.h - margin - (math.sin(st) * scale + scale) )
        st = st + step
    end
    pt:done()
    return true
end

frm.eventFilter = QPaintEvent.filter(paint_frm)
frm.eventFilter = QTimerEvent.filter(timer_frm)
frm:startTimer(1000/20)

mdiArea:addSubWindow(frm):show()
--]]


--[[  -- about dialog
dlg = QDialog()
dlg.windowFlags = dlg.windowFlags + 0x00000800
dlg:setAttribute(55,true)  -- delete on close
dlg.windowIcon = mainWindow.windowIcon
function on_paint(obj,evt)
    local pt = QPainter()
    pt:begin(dlg)
    local px = mainWindow.windowIcon:pixmap(512,512)
    dlg:setMask(px.mask)
    mainWindow.windowIcon:paint(pt,0,0,px.size.w,px.size.h)
    pt:done()
    return true
end
function on_mouse(obj,evt)
    local p = dlg:mapToGlobal(QPoint(evt.x,evt.y))
    if evt.type == 2 then -- mouse down
        dlg.mouseDown = true
        dlg.dx = dlg.pos.x - p.x
        dlg.dy = dlg.pos.y - p.y
    elseif evt.type == 3 then  -- mouse up
        dlg.mouseDown = false
    elseif evt.type == 5 and dlg.mouseDown then -- mouse move
        local pos = QPoint(p.x + dlg.dx, p.y+dlg.dy)
        dlg:move(pos)
    end
    return true
end
dlg:resize(512,440)
QLabel("<b>Toolbox</b> (beta)",dlg){
    x = 130, y = 70, w = 200
}
QLabel("by <b>lxyppc</b>",dlg){
    x = 350, y = 270
}
QLabel([=[<a href="mailto:lxyppc@163.com">lxyppc@163.com</a>]=],dlg){
    x = 350, y = 290, w = 200
}
--QPushButton("OK",dlg){
--    x = 380, y = 350, w = 80,
--    clicked = {dlg,dlg.accept},
--}
QPushButton("X",dlg){
    x = 110, y = 76, w = 20, h = 20,
    clicked = {dlg,dlg.reject}, flat = true,
}
dlg.eventFilter = QPaintEvent.filter(on_paint)
dlg.eventFilter = QMouseEvent.filter(on_mouse)
dlg:show()
--]]
