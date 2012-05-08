clockTree = QDialog(mainWindow){minw = 800, minh=600}
CLK_BA = 0x50000200
clockTree.mem = {
    PWRCON =    { addr = CLK_BA + 0x00, reset = 0x00000010 },
    AHBCLK =    { addr = CLK_BA + 0x04, reset = 0x0000000D },
    APBCLK =    { addr = CLK_BA + 0x08, reset = 0x00000000 },
    CLKSTATUS = { addr = CLK_BA + 0x0c, reset = 0x00000000 },
    CLKSEL0 =   { addr = CLK_BA + 0x10, reset = 0x00000030 },
    CLKSEL1 =   { addr = CLK_BA + 0x14, reset = 0xFFFFFFFF },
    CLKSEL2 =   { addr = CLK_BA + 0x1C, reset = 0x000000F0 },
    CLKDIV =    { addr = CLK_BA + 0x18, reset = 0x00000000 },
    PLLCON =    { addr = CLK_BA + 0x20, reset = 0x0005C22E },
    FREQDIV =   { addr = CLK_BA + 0x24, reset = 0x00000000 },
}
for k,v in pairs(clockTree.mem) do
    v.cur = v.reset
    --log(string.format("%s@%08X reset:%08X", tostring(k), v.addr,v.cur))
end

BOOL_TYPE = 0
ENUM_TYPE = 1
RANGE_TYPE = 2

bgEnable = "background-color:#00FF00"
bgDisable = "background-color:lightgray"
function updataBgColor(widget,val)
    widget.styleSheet = val and bgEnable or bgDisable
end

function get_value(mem,reg,bstart,bend)
    local r = mem[reg]
    local vmask = (2 ^ (bend-bstart+1)) - 1
    vmask = vmask * (2 ^ bstart)
    if r then
        local res = bit_and(r.cur,vmask)
        res = res / (2^bstart);
        return res
    else
        return 0
    end
end

function set_value(mem,reg,bstart,bend,v)
    local r = mem[reg]
    local vmask = (2 ^ (bend-bstart+1)) - 1
    vmask = 0xffffffff - (vmask * (2 ^ bstart))
    v = v * (2 ^ bstart)
    if r then
        r.cur = bit_and( r.cur, vmask)
        r.cur = bit_or(r.cur, v)
    else
        return 0
    end
end

function get_item_value(item)
    return get_value(item.par.mem,item.reg,item.bitstart,item.bitend)
end

function set_item_value(item,v)
    return set_value(item.par.mem,item.reg,item.bitstart,item.bitend,v)
end

class "BoolItem"(QCheckBox)
function BoolItem:__init(parent,name,x,y,reg,bitpos,bitend,truevalue,falsevalue)
    QCheckBox.__init(self,name,parent)
    self.w = 80;
    self.h = 40;
    self.x = x
    self.y = y
    self.toggled = {self, self.toMem}
    self.reg = reg
    self.bitstart = bitpos
    if bitend then
        self.bitend = bitend
    else
        self.bitend = bitpos
    end
    if truevalue then
        self.truevalue = truevalue
    else
        self.truevalue = 1
    end
    if falsevalue then
        self.falsevalue = falsevalue
    else
        self.falsevalue = 0
    end
    self.par = parent
    self:fromMem()
end

function BoolItem:fromMem()
    if get_item_value(self) == self.truevalue then
        self.checked = true
    else
        self.checked = false
    end
    updataBgColor(self,self.checked)
end

function BoolItem:toMem(v)
    if v then
        set_item_value(self,self.truevalue)
    else
        set_item_value(self,self.falsevalue)
    end
    updataBgColor(self,v)
end

function BoolItem:value()
   return self.checked
end

function BoolItem:isValid()
   return self.checked
end

class "EnumItem"(QFrame)
function EnumItem:__init(parent,name,x,y,reg,bitpos,bitend,valus)
    QFrame.__init(self,parent)
    self.w = 100;
    self.h = 70;
    self.x = x
    self.y = y
    self.label = QLabel(name,self)
    self.combo = QComboBox{valus}
    self.layout = QVBoxLayout{
        self.label,
        self.combo,
    }
    self.combo.currentIndexChanged = {self, self.toMem}
    self.reg = reg
    self.bitstart = bitpos
    if bitend then
        self.bitend = bitend
    else
        self.bitend = bitpos
    end
    if truevalue then
        self.truevalue = truevalue
    else
        self.truevalue = 1
    end
    if falsevalue then
        self.falsevalue = falsevalue
    else
        self.falsevalue = 0
    end
    self.par = parent
    self:fromMem()
end

function EnumItem:fromMem()
    local v = get_item_value(self)
    for i = 0,self.combo.count-1 do
        if self.combo:itemData(i).val == v then
            self.combo:setCurrentIndex(i)
            updataBgColor(self.label,self.combo:itemData(i).con:isValid())
        end
    end
end

function EnumItem:toMem(v)
    local d = self.combo:itemData(v)
    if d then
        set_item_value(self,d.val)
    end
    updataBgColor(self.label,self.combo:itemData(v).con:isValid())
end

function EnumItem:isValid()
   local i = self.combo.currentIndex
   local d = self.combo:itemData(i)
   return d.con:isValid()
end

clockTree.Ext_12M = BoolItem(clockTree, "4~12\r\nMHz", 10, 10, "PWRCON", 0)
clockTree.Int_221184 = BoolItem(clockTree, "22.1184\r\nMHz", 10, 60, "PWRCON", 2)
clockTree.Ext_32768 = BoolItem(clockTree, "32.768\r\nKHz", 10, 110, "PWRCON", 1)
clockTree.Int_10K = BoolItem(clockTree, "10\r\nKHz", 10, 160, "PWRCON", 3)
clockTree.PLL = BoolItem(clockTree, "PLL", 10, 210, "PLLCON", 18);
tb = {
    ["4-24MHz"] = { val = 0, con = clockTree.Ext_12M },
    ["32.768KHz"] = { val = 1, con = clockTree.Ext_32768 },
    ["PLL"] = { val = 2, con = clockTree.PLL },
    ["Internal 10KHz"] = {val = 3, con = clockTree.Int_10K},
    ["Internal 22MHz"] = {val = 7, con = clockTree.Int_221184}}
clockTree.HCLK = EnumItem(clockTree, "HCLK", 100, 210, "CLKSEL0", 0, 2, tb);

clockTree:exec()
log(string.format("%08X",clockTree.mem.PWRCON.cur))








