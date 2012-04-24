class "ServerClientView"(QFrame)
function ServerClientView:__init(socket)
    QFrame.__init(self)
    socket.parent = self
    self.closeBtn = QPushButton("Close")
    self.clearBtn = QPushButton("Clear")
    self.sendBtn = QPushButton("Send")
    self.recvEdit = QHexEdit{
        overwriteMode = false,
        readOnly = true,
    }
    self.sendEdit = QHexEdit{
        overwriteMode = false,
        readOnly = false,
    }
    self.clientIP = QLineEdit(self){
        text = tostring(socket.peerAddress),
        inputMask = "999.999.999.999",
        readOnly = true,
    }
    self.clientPort = QLineEdit(self){
        text = string.format("%d",socket.peerPort),
        inputMask = "999999",
        readOnly = true,
    }

    self.settings = QGroupBox("Client Info",self){
        layout = QHBoxLayout{
            QLabel("Client IP:"), self.clientIP,
            QLabel("Client Port:"), self.clientPort,
            self.closeBtn,
        }
    }
    self.socket = socket
    self.layout = QVBoxLayout{
            self.settings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.clearBtn, QLabel(""), strech = "0,0,1" },
                self.recvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sendBtn, QLabel(""), strech = "0,0,1" },
                self.sendEdit,
            },
            strech = "0,1",
        }

    self.closeBtn.clicked = function()
        if self.socket.state == 3 then
            self.socket:close()
        end
    end

    self.clearBtn.clicked = function()
        self.recvEdit:clear()
    end

    self.sendBtn.clicked = function()
        self.socket:write(self.sendEdit.data)
    end

    self.socket.error = function(err)
        logEdit:append("TCP server socket error, reason:" .. err)
    end

    self.socket.readyRead = function()
        --logEdit:append("Server socket ready read")
        self.recvEdit:append(self.socket:readAll())
        self.recvEdit:scrollToEnd()
    end

    self.socket.stateChanged = function(state)
        --logEdit:append("TCP server socket state changed, state:" .. state)
        if state == 0 then
            self.closeBtn.enabled = false
        end
    end


    self.eventFilter = QCloseEvent.filter( function(obj,evt)
        if self.socket.isValid then
            self.socket:close()
        end
        return true
    end)

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
    self.sSettings = QGroupBox("Server Setting",self){
        layout = QHBoxLayout{
            QLabel("IP:"), self.bindIP,
            QLabel("Port:"), self.bindPort,
            self.listenBtn,
        }
    }
    self.tab = QTabWidget(self){
        tabsClosable = true,
        movable = true,
    }
    self.layout = QVBoxLayout{
            self.sSettings,
            QLabel("Clients:"),
            self.tab,
            strech = "0,0,1",
        }

    self.tcpServer = QTcpServer(self)

    self.listenBtn.clicked = function()
        if self.tcpServer.isListening then
            self.tcpServer:close()
        else
            res = self.tcpServer:listen(QHostAddress(self.bindIP.text), tonumber(self.bindPort.text))
            if res then
                logEdit:append("listen " .. self.bindIP.text .. ":" .. self.bindPort.text .. "  success")
            else
                logEdit:append("listen " .. self.bindIP.text .. ":" .. self.bindPort.text .. "  fail")
            end
        end

        if self.tcpServer.isListening then
            self.listenBtn.text = "Close"
        else
            self.listenBtn.text = "Listen"
        end
    end

    self.tab.tabCloseRequested = function(index)
        self.tab:widget(index):close()
        self.tab:removeTab(index)
    end

    self.tcpServer.newConnection = function()
        if self.tcpServer.hasPendingConnections then
            tcpsocket = self.tcpServer.nextPendingConnection
            logEdit:append("New connection: " .. tostring(tcpsocket.peerAddress))
            client = ServerClientView(tcpsocket)
            self.tab:addTab(client, tostring(tcpsocket.peerAddress))
            self.tab:setCurrentWidget(client)
        end
    end
end

class "TcpClientView"(QFrame)
function TcpClientView:__init()
    QFrame.__init(self)
    self.tcpClient = QTcpSocket(self)

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
    self.recvEdit = QHexEdit{
        overwriteMode = false,
        readOnly = true,
    }
    self.sendEdit = QHexEdit{
        overwriteMode = false,
        readOnly = false,
    }
    self.settings = QGroupBox("Client Setting",self){
        layout = QHBoxLayout{
            QLabel("Server IP:"), self.serverIP,
            QLabel("Server Port:"), self.serverPort,
            self.connectBtn,
        }
    }
    self.layout = QVBoxLayout{
            self.settings,
            QVBoxLayout{
                QHBoxLayout{ QLabel("Recv buf:"), self.clearBtn, QLabel(""), strech = "0,0,1" },
                self.recvEdit,
                QHBoxLayout{ QLabel("Send buf:"), self.sendBtn, QLabel(""), strech = "0,0,1" },
                self.sendEdit,
            },
            strech = "0,1",
        }


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
        logEdit:append("TCP Client ready read")
        self.recvEdit:append(self.tcpClient:readAll())
        self.recvEdit:scrollToEnd()
    end

    self.tcpClient.stateChanged = function(state)
        --logEdit:append("TCP client state changed, state:" .. state)
        if state == 0 then
            self.connectBtn.text = "Connect"
            self.connectBtn.enabled = true
        elseif state == 3 then
            self.connectBtn.text = "Disconnect"
            self.connectBtn.enabled = true
        elseif state == 1 then
            self.connectBtn.enabled = false
        elseif state == 2 then
            self.connectBtn.enabled = false
        elseif state == 6 then
            self.connectBtn.enabled = false
        end
    end
end
