ftpdlg = QDialog(mainWindow)
ftpdlg.windowTitle = "Lite FTP Viewer"
ftpdlg.ftpAddr = QLineEdit("ftp.21ic.com", ftpdlg)
ftpdlg.ftpPort = QLineEdit("21", ftpdlg){ inputMask = "99999", maxw = 40, minw = 40}
ftpdlg.ftpUser = QLineEdit("hotuser", ftpdlg)
ftpdlg.ftpPwd = QLineEdit("250", ftpdlg){echoMode = 2}
ftpdlg.connectBtn = QPushButton("connect", ftpdlg)
ftpdlg.downloadBtn = QPushButton("download ..", ftpdlg)
ftpdlg.uploadBtn = QPushButton("upload ..", ftpdlg)
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
ftpdlg.list,
QHBoxLayout{ftpdlg.downloadBtn,ftpdlg.uploadBtn,QLabel(), strech="0,0,1"}
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
    local str = codec:toUnicode(info.rawName)
    --log( str .. "     " .. info.owner)
    local content = {
        str,
        info.owner,
        info.lastModified:toString(),
        tostring(info.size) .. "bytes",
    }
    local item = QTreeItem(content)
    item:setData(0,30, info.isDir)
    item:setData(0,31, info.rawName)
    ftpdlg.list:addTopLevelItem(item)
end

function split(s,ch)
    local p = 1
    local p1,p2 = string.find(s,ch,p)
    local len = string.len(s)
    local res = {}
    while p1 and p2 do
        --log(p1)
        --log(p2)
        local str = string.sub(s,p,p1-1)
        --log(str)
        res[#res+1] = str
        p2 = p2 + 1
        p = p2
        p1,p2 = string.find(s,ch,p)
    end
    local str = string.sub(s,p,len)
    --log(str)
    res[#res+1] = str
    return res
end

function solve_path(s)
    local t = split(s,"/")
    local t2 = {}
    for i = 1, #t do
        if t[i] == ".." then
            if #t2 >= 1 then
                t2[#t2] = nil
            end
        elseif t[i] == "." then
        else
            t2[#t2+1] = t[i]
        end
    end
    local s = ""
    for i = 1,#t2 do
        s = s .. t2[i]
        s = s .. (i < #t2 and "/" or "")
    end
    return s
end

function download(item)
    local s = "";
    local dir = item:data(0,30)
    local name = item:data(0,31)
    s = s .. tostring(dir)
    log(s)
    if dir then
        codec = QTextCodec.codecForName("GBK")
        ftpdlg.curPath = ftpdlg.curPath .. "/" .. item:text(0)
        ftpdlg.curPath = solve_path(ftpdlg.curPath)
        log(ftpdlg.curPath)
        ftpdlg.ftp:cd( codec:fromUnicode(ftpdlg.curPath) )
        ftpdlg.list:clear()
        ftpdlg.ftp:list()
    else
        local path = QCommonDlg.getSaveFileName("",item:text(0))
        --if res then
            --log(path)
            ftpdlg.file = QFile(path, ftpdlg)
            if ftpdlg.file:open(2) then
                ftpdlg.ftp:get(name, ftpdlg.file)
                log("Downloading data to \"" .. path .. "\" ...")
                ftpdlg.progress.labelText = "downloading " .. item:text(0)
                ftpdlg.progress:exec();
            else
                log("open file \"" .. path .. "\" fail")
            end
        --end
    end
end

ftpdlg.downloadBtn.clicked = function()
    --log("download click")
    local item = ftpdlg.list.currentItem
    if item then download(item) end
end

function rfind(str, ch)
    for i = string.len(str),1,-1 do
        if string.sub(str,i,i) == ch then return i end
    end
    return nil
end

ftpdlg.uploadBtn.clicked = function()
    log("upload click")
    local path = QCommonDlg.getOpenFileName("")
    ftpdlg.file = QFile(path)
    codec = QTextCodec.codecForName("GBK")
    path = string.sub(path, rfind(path,"/")+1)
    local name = codec:fromUnicode(path)
---[[
    if ftpdlg.file:open(1) then -- open readonly
        ftpdlg.ftp:put(ftpdlg.file, name)
        log("Uploading data to \"" .. path .. "\" ...")
        ftpdlg.progress.labelText = "uploading " .. path
        ftpdlg.progress:exec();
    else
        log("open file \"" .. path .. "\" fail")
    end
--]]
end

ftpdlg.list.itemDoubleClicked = function(item, col)
    download(item)
end

ftpdlg.ftp.dataTransferProgress = function(done, total)
    --log("progress")
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
            --ftpdlg.file = nil
        else
            log("download success!")
            log(ftpdlg.file.errorString)
            ftpdlg.file:close()
            --ftpdlg.file = nil
        end
    elseif ftpdlg.ftp:currentCommand() == 9 then
        ftpdlg.progress:hide()
        if error then
            log("upload error!")
            ftpdlg.file:close()
            ftpdlg.file:remove()
            --ftpdlg.file = nil
        else
            log("upload success!")
            ftpdlg.file:close()
            --ftpdlg.file = nil
        end
    end
end

ftpdlg:exec()
