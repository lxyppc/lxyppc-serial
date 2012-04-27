clockTree = QDialog(mainWindow){minw = 800, minh=600}
function add_source(parent,name,px,py)
  btn = QCheckBox(name,parent){
         x=px,y=py,w=80,h=40,flat = false,
         styleSheet = "QCheckBox {background-color:lightgray}"
     }
  return {
     action = btn,
  }
end
clockTree.Int_221184 = add_source(clockTree, "22.1184\r\nMHz", 10, 10)
clockTree.Ext_12M = add_source(clockTree, "4~12\r\nMHz", 10, 60)
clockTree.Ext_32768 = add_source(clockTree, "32.768\r\nKHz", 10, 110)
clockTree.Int_10K = add_source(clockTree, "10\r\nKHz", 10, 160)
clockTree.PLL = add_source(clockTree, "PLL", 10, 210);


clockTree:exec()
log(clockTree.Int_221184.action.checked)