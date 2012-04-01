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

function init_mainwindow(mainwindow)
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
            where = "123",
        },
        editTextChanged = {log, log.append}
    }
    print(combo:itemData(3))

    list = QListWidget()
    list:addItem(MQListItem("123"))
    list:addItem(MQListItem("456"))
    list:addItem(MQListItem("789"))
    --list:addItem("987")
    --list:addItem("987")
    --list:addItem("987")
    --list:addItem("987")

---[[
    item1 = MQListItem("122")
    item2 = MQListItem("124")
    tt = {item1,item2}


    list:addItem(item1 )
    list:addItem(item2 )

    --list:sortItems(1)
--]]
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
                    list
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
end
