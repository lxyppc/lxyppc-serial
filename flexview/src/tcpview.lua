class "TcpView"(QFrame)

function TcpView:__init()
    QFrame.__init(self)
    self.windowTitle = "TCP Viewer"
    self.ipaddr = QLineEdit(self){
        text = "192.168.0.195",
        inputMask = "999.999.999.999",
    }
    self.port = QLineEdit(self){
        text = "9999",
        inputMask = "999999",
    }
    self.layout = QFormLayout{
        {"IP Address:", self.ipaddr},
        {"Port:", self.port},
    }
end

