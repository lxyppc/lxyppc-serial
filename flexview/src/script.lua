function EditScript()
    dofile("../src/editor.lua")
    dlg = LuaEditDlg()
    dlg:load("../src/script.lua")
    dlg:show()
end

class "MQListItem"(QListItem)

function MQListItem:__init()
    QListItem.__init(self)
end

function MQListItem:__init(v)
    QListItem.__init(self,v)
end

function MQListItem:data(role)
---[[
    if role == 8 then
        return QBrush(QColor("red"));
    elseif role == 9 then
        return QBrush(QColor("blue"));
    end
--]]
    return QListItem.data(self,role)
end

function MQListItem:setData(role, v)
    return QListItem.setData(self,role,v)
end

function MQListItem:__lt(v)
    return QListItem.__lt(self,v) == false
end

function filter(mw, obj,evt)
    if evt.type == 19 then
        evt:ignore()
        return true
    end
    mw.logEdit:append(string.format("type:%d",evt.type))
    return false
end

function init_mainwindow(mainwindow)
    mdi = mainwindow.mdiArea
    log = mainwindow.logEdit
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
            log:append("open: " .. portInfo.physName)
            serial.portName = portInfo.physName
            res = serial:open()
            log:append(serial.errorString)
            if res then
                btnOpen.text = "close"
            end
        end
    end

    frm = QFrame{
        windowtitle = "Serial Port Viewer",
        layout = QHBoxLayout{
            settingGroup,
            QPushButton("Refresh"),
            btnOpen,
        }
    }


    mdi:addSubWindow(frm)

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
end
