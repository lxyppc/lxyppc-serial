width = QLineEdit("185")
ratio = QLineEdit("65")
radius = QLineEdit("15")
diameter = QLineEdit()
kmh40 = QLineEdit()
kmh80 = QLineEdit()
kmh120 = QLineEdit()
kmh200 = QLineEdit()
dlg = QDialog{
    layout = QFormLayout{
        {"Width:", width},
        {"ratio:", ratio},
        {"Radius:", radius},
        {"Diameter:", diameter},
        {"40KMh -> RPM:", kmh40},
        {"80KMh -> RPM:", kmh80},
        {"120KMh -> RPM:", kmh120},
        {"200KMh -> RPM:", kmh200},
    }
}

function khmtoRPM(kmh,d)
    return kmh*1000*1000/(d*3.1415926)/60/60;
end

function changed(str)
w = tonumber(width.text)
ra = tonumber(ratio.text)
r = tonumber(radius.text)
d = w*ra/100*2 + r*25.4
diameter.text = tostring(d)
kmh40.text = tostring(khmtoRPM(40,d))
kmh80.text = tostring(khmtoRPM(80,d))
kmh120.text = tostring(khmtoRPM(120,d))
kmh200.text = tostring(khmtoRPM(200,d))
end
width.textChanged = changed
ratio.textChanged = changed
radius.textChanged = changed
changed("")

dlg:exec()