class "TcpView"(QTabWidget)

function TcpView:__init()
    QTabWidget.__init(self)
    self.windowTitle = "TCP Viewer"
    self.serverIP = QLineEdit(self){
        text = "192.168.0.195",
        inputMask = "999.999.999.999",
    }
    self.serverPort = QLineEdit(self){
        text = "7777",
        inputMask = "999999",
    }

    self.connectBtn = QPushButton("Connect", self)
    self.clearBtn = QPushButton("Clear", self)
    self.sendBtn = QPushButton("Send", self)
    self.recvEdit = QHexEdit()
    self.sendEdit = QHexEdit()
    self.settings = QGroupBox("Client Setting",self){
        layout = QFormLayout{
            {"Server IP:", self.serverIP},
            {"Server Port:", self.serverPort},
            self.connectBtn,
        }
    }
    self.clientFrm = QFrame(){
        layout = QHBoxLayout{
            self.settings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.clearBtn, QLabel(""), strech = "0,0,1" },
                self.recvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sendBtn, QLabel(""), strech = "0,0,1" },
                self.sendEdit,
            },
            strech = "0,1",
        }
    }

    self.bindIP = QLineEdit(self){
        text = "0.0.0.0",
        inputMask = "999.999.999.999",
    }
    self.bindPort = QLineEdit(self){
        text = "7777",
        inputMask = "999999",
    }
    self.listenBtn = QPushButton("Listen", self)
    self.sClearBtn = QPushButton("Clear", self)
    self.sSendBtn = QPushButton("Send", self)
    self.sRecvEdit = QHexEdit()
    self.sSendEdit = QHexEdit()
    self.sSettings = QGroupBox("Server Setting",self){
        layout = QFormLayout{
            {"IP:", self.bindIP},
            {"Port:", self.bindPort},
            self.listenBtn,
        }
    }
    self.serverFrm = QFrame(){
        layout = QHBoxLayout{
            self.sSettings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.sClearBtn, QLabel(""), strech = "0,0,1" },
                self.sRecvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sSendBtn, QLabel(""), strech = "0,0,1" },
                self.sSendEdit,
            },
            strech = "0,1",
        }
    }

    self.tcpServer = QTcpServer(self)
    self.tcpList = {}

    self.listenBtn.clicked = function()
        res = self.tcpServer:listen(QHostAddress(self.bindIP.text), tonumber(self.bindPort.text))
        if res then
            logEdit:append("listen" .. self.bindIP.text .. ":" .. self.bindPort.text .. "success")
        else
            logEdit:append("listen" .. self.bindIP.text .. ":" .. self.bindPort.text .. "fail")
        end
    end

    self.tcpClient = QTcpSocket(self)

    self:addTab(self.clientFrm, "TCP Client")
    self:addTab(self.serverFrm, "TCP Server")
end

