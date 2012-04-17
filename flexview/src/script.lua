function EditScript()
    dofile("../src/editor.lua")
    dlg = LuaEditDlg()
    dlg:load("../src/script.lua")
    dlg:show()
end

function filter(mw, obj,evt)
    if evt.type == 19 then
        evt:ignore()
        return true
    end
    mw.logEdit:append(string.format("type:%d",evt.type))
    return false
end

class "MyListItem"(QListItem)
function MyListItem:__init(x)
    QListItem.__init(self,x);
end

function MyListItem:data(role)
    if role == 8 then
        r = self.row % 2
        if r == 1 then
            return QBrush(QColor("lightgray"))
        else
            return QBrush(QColor("darkgray"))
        end
    end
    return QListItem.data(self,role)
end

function MyListItem:__lt(x)
    return QListItem.__lt(self,x) == false
end

logEdit:append("sfsdfdsgds")
mainwindow = mainWindow

--function init_mainwindow2(mainwindow)
    mdi = mainwindow.mdiArea
    log = mainwindow.logEdit

    mx = 0
    my = 0

---[[
    tray = QSystemTrayIcon(mainwindow.windowIcon,mainwindow)
    tray:show()
    tray.activated = function(r) log:append(string.format("reason:%d",r))  end
    tray.messageClicked = function() log:append(string.format("Clicked"))  end

    act = mainwindow:menuBar():addMenu("Test"):addAction("tray")
    act.triggered = function() tray:showMessage("22312","xxxxxxxxxxxxxxx",3);mx=mx+1;my=my+1; end

    portList = QComboBox();
    ports = QSerialPort.enumPort()
    table.foreach(ports, function (k,v) portList:addItem(v.portName, v)  end)
    serial = QSerialPort()

    baudList = QComboBox{ QSerialPort.ValidBaudRate() }
    parityList = QComboBox{ QSerialPort.ValidParity() }
    dataBitsList = QComboBox{ QSerialPort.ValidDataBits() }
    stopBitsList = QComboBox{ QSerialPort.ValidStopBits() }
    flowList = QComboBox{ QSerialPort.ValidFlow() }
    settingString = QLineEdit(serial.settingString){
        readonly = true
    }
    baudList.currentIndex = serial.baudRate
    parityList.currentIndex = serial.parity
    dataBitsList.currentIndex = serial.dataBits
    stopBitsList.currentIndex = serial.stopBits
    flowList.currentIndex = serial.flowControl

    baudList.currentIndexChanged = {serial,serial.setBaudRate}
    parityList.currentIndexChanged = {serial,serial.setParity}
    dataBitsList.currentIndexChanged = {serial,serial.setDataBits}
    stopBitsList.currentIndexChanged = {serial,serial.setStopBits}
    flowList.currentIndexChanged = {serial,serial.setFlowControl}
    serial.settingChange = {settingString, settingString.setText}


    baudBtn = QPushButton("BaudRate:")
    settingGroup = QGroupBox("Port Settings"){
        layout = QVBoxLayout{
            QHBoxLayout{
                QVBoxLayout{
                    QLabel("Port:"),QLabel("Baud:"),QLabel("Parity:"),QLabel("Data Bits:"),
                    QLabel("Stop Bits:"),QLabel("Flow:"),
                },
                QVBoxLayout{
                    portList,baudList,parityList,dataBitsList,stopBitsList,flowList
                },
            },
            settingString,
        }
    }


    btnOpen = QPushButton("open")
    btnOpen.clicked =
    function ()
        if serial.isOpen then
            serial:close()
            btnOpen.text = "open"
        else
            i = portList.currentIndex
            portInfo = portList:itemData(i)
            log:append("open: " .. portInfo.portName)
            serial.portName = portInfo.portName
            res = serial:open()
            log:append(serial.errorString)
            if res then
                btnOpen.text = "close"
            end
        end
    end

    timeui = QVBoxLayout{
        QDateEdit(QDate.currentDate()) { calendarPopup = false },
        QTimeEdit(QTime.currentTime()) { calendarPopup = true },
        QDateTimeEdit(QDateTime.currentDateTime()) { calendarPopup = true },
        QSpinBox(),
        QDoubleSpinBox(),
    }

    hlay = QHBoxLayout{
    settingGroup,
    QPushButton("Refresh"),
    btnOpen,
    timeui,
    }

    frm = QFrame{
        windowtitle = "Serial Port Viewer",
        layout = hlay
    }

    mdi:addSubWindow(frm)
--]]
    frm2 = QFrame{
        windowtitle = "Painter Test",
        minh = 200,
        minw = 400,
    }

    function MouseMove(obj,evt)
        mx = evt.x
        my = evt.y
        frm2:update()
        --dfdf = dfdf + 1
        --log:append(string.format("x:%d,y:%d",evt.x,evt.x))
        --log:append(string.format("type:%d,%s",xxx(evt.type),class_info(evt).name))
        return true
    end
    function NeedPaint(obj,evt)
        pt = QPainter();
        pt:begin(frm2);
        pt.brush = QBrush(QColor("darkgray"))
        pt:drawRect(frm2.geometry)
        rect = pt:drawText(1,1,100,50,0,"Hello World")
        pt:drawRect(rect)
        rect = pt:drawText(1,1,100,50,0,string.format("x:%d,y:%d",mx,my))
        pt:done();
        btn.text = string.format("x:%d,y:%d",mx,my)
        return true
    end
    frm2:installEventFilter(QPaintEvent.filter(NeedPaint))
    frm2:installEventFilter(QMouseEvent.filter(MouseMove))
    --frm2.eventFilter = QPaintEvent.filter(NeedPaint)
    --frm2.eventFilter = QMouseEvent.filter(MouseMove)
    frm2.mouseTracking = true

    --frm2:startTimer(200)
    btn = QLabel("hello",frm2){
        x = 100, y = 0,
        w = 100,h = 20
    }
    function on_time()
        frm2:update();
        return true
    end
    frm2.eventFilter = QTimerEvent.filter(on_time)


    mdi:addSubWindow(frm2)

    listw = QListWidget()
    listw:addItem(MyListItem("123"))
    listw:addItem(MyListItem("456"))
    listw:addItem(MyListItem("789"))
    table.foreach({"2342","32432","sdfds","3435","gfdg45"},
        function(k,v) listw:addItem(MyListItem(v)) end
    )
    listw:sortItems()
    frm3 = QFrame{
        windowtitle = "List Test",
        minh = 200,
        minw = 400,
        layout = QVBoxLayout{
            listw,
        },
    }

    mdi:addSubWindow(frm3)

x = [==[
    menubar = mainwindow:menuBar()
    editMenu = menubar:addMenu("&Edit")
    actEdit = editMenu:addAction("&Edit script...")
    actEdit.statusTip = "Edit the default script file"
    actClear = editMenu:addAction("&Clear Log")
    actClear.statusTip = "Clear scrip execute log"
    actEdit.triggered = EditScript
    menu = menubar:addMenu("&Help")
    log = mainwindow.logEdit
    log:append("Script started...")
    actClear.triggered = {log,log.clear}

    combo = QComboBox{
        minw = 260,
        editable = true,
        {"123","456","789",
            where = QColor("blue"),
        },
        editTextChanged = {log, log.append}
    }
    print(combo:itemData(3))

    tab = QToolBox()
    ports = QSerialPort.enumPort()

    port = QSerialPort{
        baudRate = QSerialPort["BAUD38400"],
        flowControl = QSerialPort.FLOW_HARDWARE
    }
    log:append(port.settingString)
    combo = QComboBox()
    table.foreach(ports, function (k,v) combo:addItem(v.portName, v)  end)
    combo.currentIndexChanged =
    function (i)
        log:append(combo:itemData(i).physName)
        log:append(combo:itemData(i).enumName)
        log:append(combo:itemData(i).friendName)
        log:append(string.format("PID:%x",combo:itemData(i).productID))
        log:append(string.format("VID:%x",combo:itemData(i).vendorID))
    end


    tab:addItem(combo,QIcon("xx.png"),"test1")

    mainwindow{
        x = 200, y = 200, w = 800, h = 600,
        QDockWidget("123"){
            QFrame{
                layout = QVBoxLayout(){
                    combo,
                    --[[QToolButton{
                        QIcon("xx.png"),
                        clicked = {combo, combo.clear}
                    },--]]
                    tab
                }
            }
        },

        QDockWidget("456"){
            QHexEdit{
            {1,2,3,4,5}
            }
        }
    }
    --state = mainwindow.state
    --print( toString( toBase64(state) ) )

    sb = mainwindow.statusBar

    log:append("Initialize done")
--]==]
--end
