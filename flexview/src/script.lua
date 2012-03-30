function EditScript()
    dofile("../src/editor.lua")
    dlg = LuaEditDlg()
    dlg:load("../src/script.lua")
    dlg:show()
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

    combo = QComboBox(){
        minw = 260
    }
    combo:addItems ({"123","456","789"})
    mainwindow{
        x = 200, y = 200, w = 800, h = 600,
        QDockWidget("123"){
            combo
        },

        QDockWidget("456"){
            QHexEdit{
            {1,2,3,4,5}
            }
        }
    }
    state = mainwindow.state
    print( toString( toBase64(state) ) )

    sb = mainwindow.statusBar

    log:append("Initialize done")
end
