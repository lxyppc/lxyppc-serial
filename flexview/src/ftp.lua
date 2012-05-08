ftpdlg = QDialog(mainWindow)
ftpdlg.windowTitle = "Lite FTP Viewer"
ftpdlg.ftpAddr = QLineEdit("ftp.21ic.com", ftpdlg)
ftpdlg.ftpPort = QLineEdit("21", ftpdlg){ inputMask = "99999", maxw = 40, minw = 40}
ftpdlg.ftpUser = QLineEdit("hotuser", ftpdlg)
ftpdlg.ftpPwd = QLineEdit("250", ftpdlg){echoMode = 2}
ftpdlg.connectBtn = QPushButton("connect", ftpdlg)
ftpdlg.list = QTreeWidget(ftpdlg)
ftpdlg.list.header = {"Dir","owner", "lastModified", "size"}
ftpdlg.ftp = QFtp(ftpdlg)
ftpdlg.curPath = ""
ftpdlg.progress = QProgressDialog(ftpdlg)
ftpdlg.layout = QVBoxLayout{
QHBoxLayout{
    QLabel("Ftp:"),ftpdlg.ftpAddr,QLabel("Port:"),ftpdlg.ftpPort,
    QLabel("Username:"),ftpdlg.ftpUser,QLabel("Password:"),ftpdlg.ftpPwd,
    ftpdlg.connectBtn
},
ftpdlg.list
}
QFtp.Unconnected = 0
QFtp.HostLookup = 1
QFtp.Connecting = 2
QFtp.Connected = 3
QFtp.LoggedIn = 4
QFtp.Closing = 5
ftpdlg.connectBtn.clicked = function ()
    log("ftp state:" .. ftpdlg.ftp.state)
    if ftpdlg.ftp.state == 0 then
        ftpdlg.ftp:connectToHost(ftpdlg.ftpAddr.text, tonumber(ftpdlg.ftpPort.text) )
        ftpdlg.ftp:login(ftpdlg.ftpUser.text, ftpdlg.ftpPwd.text)
        ftpdlg.curPath = ""
        ftpdlg.list:clear()
        ftpdlg.ftp:list()
        ftpdlg.connectBtn.enabled = false
    elseif ftpdlg.ftp.state == 4 then
        ftpdlg.ftp:close()
        ftpdlg.connectBtn.enabled = false
    end
end

statestr = {
    [0] = "Unconnected",
    [1] = "HostLookup",
    [2] = "Connecting",
    [3] = "Connected",
    [4] = "LoggedIn",
    [5] = "Closing",
}

ftpdlg.ftp.stateChanged = function (state)
    log(statestr[state])
    if ftpdlg.ftp.state == QFtp.Unconnected then
        ftpdlg.connectBtn.text = "Connect"
        ftpdlg.connectBtn.enabled = true
        ftpdlg.list.enabled = false
    elseif ftpdlg.ftp.state == QFtp.LoggedIn then
        ftpdlg.connectBtn.text = "Disconnect"
        ftpdlg.connectBtn.enabled = true
        ftpdlg.list.enabled = true
    end
end

ftpdlg.ftp.listInfo = function (info)
    codec = QTextCodec.codecForName("GBK")
    local str = codec:toUnicode(info.name)
    --log( str .. "     " .. info.owner)
    local content = {
        str,
        info.owner,
        info.lastModified:toString(),
        tostring(info.size) .. "bytes",
    }
    local item = QTreeItem(content)
    item:setData(0,30, info.isDir)
    item:setData(0,31, info.name)
    ftpdlg.list:addTopLevelItem(item)
end

ftpdlg.list.itemDoubleClicked = function(item, col)
    local s = "";
    local dir = item:data(0,30)
    local name = item:data(0,31)
    s = s .. tostring(dir)
    s = s .. ":" .. col
    log(s)
    if dir then
        ftpdlg.curPath = ftpdlg.curPath .. "/" .. name
        log(ftpdlg.curPath)
        ftpdlg.ftp:cd(ftpdlg.curPath)
        ftpdlg.list:clear()
        ftpdlg.ftp:list()
    else
        local path = QCommonDlg.getSaveFileName("",item:text(0))
        --if res then
            --log(path)
            ftpdlg.file = QFile(path)
            if ftpdlg.file:open(2) then
                ftpdlg.ftp:get(name, ftpdlg.file)
                log("Downloading data to \"" .. item:text(0) .. "\" ...")
                ftpdlg.progress.labelText = "downloading " .. item:text(0)
                ftpdlg.progress:exec();
            else
                log("open file \"" .. item:text(0) .. "\" fail")
            end
        --end
    end
end

ftpdlg.ftp.dataTransferProgress = function(done, total)
    ftpdlg.progress.max = total
    ftpdlg.progress.value = done
end

ftpdlg.progress.canceled = function ()
    log("cancel donwload")
    ftpdlg.ftp:abort()
end

ftpdlg.ftp.commandFinished = function(id, error)
    log(string.format("CMD: %d, Error:", ftpdlg.ftp:currentCommand()) .. tostring(error))
    if ftpdlg.ftp:currentCommand() == 8 then
        ftpdlg.progress:hide()
        if error then
            log("download error!")
            ftpdlg.file:close()
            ftpdlg.file:remove()
        else
            log("download success!")
            ftpdlg.file:close()
            ftpdlg.file = nil
        end
    end
end

ftpdlg:exec()