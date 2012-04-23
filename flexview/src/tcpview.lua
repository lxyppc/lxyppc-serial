class "TcpView"(QTabWidget)

function TcpView:__init()
end


class "TcpServerView"(QFrame)
function TcpServerView:__init()
    QFrame.__init(self)
    self.windowTitle = "TCP Server"
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
    self.layout = QHBoxLayout{
            self.sSettings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.sClearBtn, QLabel(""), strech = "0,0,1" },
                self.sRecvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sSendBtn, QLabel(""), strech = "0,0,1" },
                self.sSendEdit,
            },
            strech = "0,1",
        }

    self.tcpServer = QTcpServer(self)
    self.tcpList = {}

    self.listenBtn.clicked = function()
        if self.tcpServer.isListening then
            self.tcpServer:close()
            logEdit:append("Closed")
        else
            res = self.tcpServer:listen(QHostAddress(self.bindIP.text), tonumber(self.bindPort.text))
            if res then
                logEdit:append("listen" .. self.bindIP.text .. ":" .. self.bindPort.text .. "success")
            else
                logEdit:append("listen" .. self.bindIP.text .. ":" .. self.bindPort.text .. "fail")
            end
        end

        if self.tcpServer.isListening then
            self.listenBtn.text = "Close"
        else
            self.listenBtn.text = "Listen"
        end
    end

    self.tcpServer.newConnection = function()
        if self.tcpServer.hasPendingConnections then
            tcpsocket = self.tcpServer.nextPendingConnection
            logEdit:append("New connection: " .. tostring(tcpsocket.peerAddress))
        end
    end
end

class "TcpClientView"(QFrame)
function TcpClientView:__init()
    QFrame.__init(self)
    self.windowTitle = "TCP Client"
    self.serverIP = QLineEdit(self){
        text = "127.0.0.1",
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
    self.layout = QHBoxLayout{
            self.settings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.clearBtn, QLabel(""), strech = "0,0,1" },
                self.recvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sendBtn, QLabel(""), strech = "0,0,1" },
                self.sendEdit,
            },
            strech = "0,1",
        }

    self.tcpClient = QTcpSocket(self)
    self.connectBtn.clicked = function()
        if self.tcpClient.state == 0 then
            self.tcpClient:connectToHost(self.serverIP.text, tonumber(self.serverPort.text))
        elseif self.tcpClient.state == 3 then
            self.tcpClient:disconnectFromHost()
        end
    end

    self.clearBtn.clicked = function()
        self.recvEdit:clear()
    end

    self.sendBtn.clicked = function()
        self.tcpClient:write(self.sendEdit.data)
    end

    self.tcpClient.error = function(err)
        self.connectBtn.enabled = true
        logEdit:append("TCP client error, reason:" .. err)
    end

    self.tcpClient.readyRead = function()
        self.recvEdit:append(self.tcpClient:readAll())
        self.recvText:scrollToEnd()
    end
    self.tcpClient.disconnected = function()
        logEdit:append("disconnected")
    end

    self.tcpClient.stateChanged = function(state)
        logEdit:append("TCP client state changed, state:" .. state)
        if state == 0 then
            self.connectBtn.enabled = true
            self.connectBtn.text = "Connect"
        elseif state == 3 then
            self.connectBtn.text = "Disconnect"
            self.connectBtn.enabled = true
        elseif state == 2 then
            self.connectBtn.enabled = false
        elseif state == 3 then
            self.connectBtn.enabled = false
        elseif state == 6 then
            self.connectBtn.enabled = false
        end
    end
end
