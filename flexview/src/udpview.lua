class "UdpView"(QFrame)

function UdpView:__init()
    QFrame.__init(self)
    self.windowTitle = "UDP Socket"
    self.udp = QUdpSocket(self)

    self.bindIP = QLineEdit(self){
        text = "0.0.0.0",
        inputMask = "999.999.999.999",
    }
    self.bindPort = QLineEdit(self){
        text = "7777",
        inputMask = "999999",
    }
    self.bindBtn = QPushButton("Bind", self)
    self.clearBtn = QPushButton("Clear", self)
    self.sendBtn = QPushButton("Send", self)
    self.recvEdit = QHexEdit{
        overwriteMode = false,
        readOnly = true,
    }
    self.sendEdit = QHexEdit{
        overwriteMode = false,
        readOnly = false,
    }

    self.sSettings = QGroupBox("Bind Setting",self){
        layout = QHBoxLayout{
            QLabel("IP:"), self.bindIP,
            QLabel("Port:"), self.bindPort,
            self.bindBtn,
        }
    }

    self.sendIP = QLineEdit(self){
        text = "255.255.255.255",
        inputMask = "999.999.999.999",
    }
    self.sendPort = QLineEdit(self){
        text = "7777",
        inputMask = "999999",
    }

    self.layout = QVBoxLayout{
            self.sSettings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.clearBtn, QLabel(""), strech = "0,0,1" },
                self.recvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sendBtn, self.sendIP, self.sendPort, QLabel(""), strech = "0,0,0,0,1" },
                self.sendEdit,
            },
            strech = "0,1",
        }


    self.bindBtn.clicked = function()
        if self.udp.state == 0 then
            res = self.udp:bind( QHostAddress(self.bindIP.text), tonumber(self.bindPort.text),1)
            if res then
                log("bind " .. self.bindIP.text .. ":" .. self.bindPort.text .. "  success")
            else
                log("bind " .. self.bindIP.text .. ":" .. self.bindPort.text .. "  fail")
            end
        else
            self.udp:close()
        end
    end

    self.clearBtn.clicked = function()
        self.recvEdit:clear()
    end

    self.sendBtn.clicked = function()
        addr = QHostAddress(self.sendIP.text)
        port = tonumber(self.sendPort.text)
        self.udp:writeDatagram(self.sendEdit.data,addr,port)
    end

    self.udp.readyRead = function()
        while self.udp.hasPendingDatagrams do
            size = self.udp.pendingDatagramSize
            data,fromAddr,fromPort = self.udp:readDatagram(size)
            self.recvEdit:append(data)
            self.recvEdit:scrollToEnd()
            --log(fromAddr)
            log("get" .. #data .. "bytes from:" .. tostring(fromAddr) .. ":" .. fromPort)
        end
    end

    self.udp.stateChanged = function(state)
        if state == 0 then
            self.bindBtn.text = "Bind"
            self.bindBtn.enabled = true
        elseif state == 4 then
            self.bindBtn.text = "Close"
            self.bindBtn.enabled = true
        else
            self.bindBtn.enabled = false
        end
        log(state)
    end

end







