class "SerialView"(QFrame)

function SerialView:__init()
    QFrame.__init(self)
    self.windowTitle = "Serial Port Viewer"
    self.portList = QComboBox();
    ports = QSerialPort.enumPort()
    table.foreach(ports, function (k,v) self.portList:addItem(v.portName, v)  end)
    self.serial = QSerialPort(self)

    self.baudList = QComboBox{ QSerialPort.ValidBaudRate(), editable = true }
    self.baudList.lineEdit.inputMask = "00000000"
    self.parityList = QComboBox{ QSerialPort.ValidParity() }
    self.dataBitsList = QComboBox{ QSerialPort.ValidDataBits() }
    self.stopBitsList = QComboBox{ QSerialPort.ValidStopBits() }
    self.flowList = QComboBox{ QSerialPort.ValidFlow() }
    self.settingString = QLineEdit(self.serial.settingString){
        readonly = true,
        minw = 100,
    }
    self.serial.flowControl = QSerialPort.FLOW_OFF
    self.baudList.currentIndex = self.serial.baudRate
    self.parityList.currentIndex = self.serial.parity
    self.dataBitsList.currentIndex = self.serial.dataBits
    self.stopBitsList.currentIndex = self.serial.stopBits
    self.flowList.currentIndex = self.serial.flowControl

    --self.baudList.currentIndexChanged = {self.serial,self.serial.setBaudRate}
    self.baudList.editTextChanged = function(text)
        idx = self.baudList:findText(text)
        if idx > 0 and idx < QSerialPort.BAUDLAST then
            self.serial:setBaudRate(idx)
        else
            bd = tonumber(text)
            if bd then
                self.serial:setBaudRate(bd)
            end
        end
        logEdit:append(self.serial.settingString)
    end

    self.parityList.currentIndexChanged = {self.serial,self.serial.setParity}
    self.dataBitsList.currentIndexChanged = {self.serial,self.serial.setDataBits}
    self.stopBitsList.currentIndexChanged = {self.serial,self.serial.setStopBits}
    self.flowList.currentIndexChanged = {self.serial,self.serial.setFlowControl}
    self.serial.settingChange = {self.settingString, self.settingString.setText}
    self.btnOpen = QPushButton("Open")
    self.btnRefresh = QPushButton("Refresh")

    self.lsdtr = QCheckBox("DTR"){toggled = {self.serial,self.serial.setDtr }}
    self.lsrts = QCheckBox("RTS"){toggled = {self.serial,self.serial.setRts }}
    self.lsdcd = QCheckBox("DCD"){enabled = false}
    self.lsdsr = QCheckBox("DSR"){enabled = false}
    self.lscts = QCheckBox("CTS"){enabled = false}
    self.lsri = QCheckBox("RI"){enabled = false}


    self.settingGroup = QGroupBox("Port Settings"){
        layout =
            QHBoxLayout{
                QFormLayout{
                    {"Port:", self.portList},
                    {"Baud:", self.baudList},
                    {"Parity:", self.parityList},
                    {"Data Bits:", self.dataBitsList},
                    {"Stop Bits:", self.stopBitsList},
                    {"Flow:", self.flowList},
                },
                QVBoxLayout{
                    --QLabel("Setting:"),
                    --self.settingString,
                    self.btnOpen,
                    self.btnRefresh,
                    self.lsdtr,
                    self.lsrts,
                    self.lsdcd,
                    self.lsdsr,
                    self.lscts,
                    self.lsri,
                    QLabel(),
                    strech = "0,0,0,0,0,0,0,0,1",
                }
            }
    }

    function update_ls()
        self.lsdcd.checked = self.serial.DCD
        self.lsdsr.checked = self.serial.DSR
        self.lscts.checked = self.serial.CTS
        self.lsri.checked = self.serial.RI
    end


    self.btnOpen.clicked =
    function ()
        if self.serial.isOpen then
            self.serial:close()
            self.btnOpen.text = "Open"
        else
            i = self.portList.currentIndex
            portInfo = self.portList:itemData(i)
            local name = portInfo.portName
            logEdit:append("open: " .. name .. " with setting: " .. self.serial.settingString)
            self.serial.portName = name
            res = self.serial:open()
            if res then
                self.btnOpen.text = "Close"
                update_ls()
                logEdit:append("Success ...")
            else
                logEdit:append("Fail:  " .. self.serial.errorString)
            end
        end
    end

    self.btnSend = QPushButton("Send")
    self.btnClearRecv = QPushButton("Clear")
    self.btnSend.clicked = function ()
        self.serial:write(self.sendText.data)
    end

    self.btnRefresh.clicked = function()
        self.portList:clear()
        ports = QSerialPort.enumPort()
        table.foreach(ports, function (k,v) self.portList:addItem(v.portName, v)  end)
    end

    self.serial.readyRead = function()
        len = self.serial:bytesAvailable()
        x = self.serial:readAll()
        self.recvText:append(x)
        self.recvText:scrollToEnd()
        --ls = self.serial.lineStatus
        --logEdit:append(string.format("%x",ls))
        update_ls()
    end

    self.sendText = QHexEdit{
        overwriteMode = false,
        readOnly = false,
    }
    self.recvText = QHexEdit()
    self.recvText.overwriteMode = false
    self.recvText.readOnly = true

    self.btnClearRecv.clicked = function ()
        self.recvText:clear()
    end

    self.layout = QHBoxLayout{
        self.settingGroup,
        QVBoxLayout{
            QHBoxLayout{
                QLabel("Send Buffer"),
                self.btnSend,
                QLabel(),
                strech = "0,0,1",
            },
            self.sendText,
            QHBoxLayout{
                QLabel("Recv Buffer"),
                self.btnClearRecv,
                QLabel(),
                strech = "0,0,1",
            },
            self.recvText,
        },
        strech = "0,1"
    }
    self.serial.connected = function(info)
        logEdit:append(info.portName .. "   connected")
    end

    self.serial.disconnected = function(info)
        logEdit:append(info.portName .. "   disconnected")
    end
end
