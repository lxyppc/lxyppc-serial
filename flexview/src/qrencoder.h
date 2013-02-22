#ifndef QRENCODER_H
#define QRENCODER_H

#include <QImage>
#include <QColor>
#include "qrencode.h"

class QREncoder
{
public:
    QREncoder()
        :m_margin(3),m_size(5),m_mode(QR_MODE_8),m_level(QR_ECLEVEL_L),m_color(QColor(0,0,0)),m_bkColor(QColor(255,255,255))
        ,m_casesensitive(true),m_8bit(0)
    {
    }
    QREncoder(const QString& content, int margin = 3, int size = 5, int mode = QR_MODE_8, int level = QR_ECLEVEL_L, const QColor& color = QColor(0,0,0), const QColor& bkColor = QColor(255,255,255))
        :m_content(content.toAscii()),m_margin(margin),m_size(size),m_mode(mode),m_level(level),m_color(color),m_bkColor(bkColor)
        ,m_casesensitive(true),m_8bit(0)
    {
    }
    QREncoder(const QByteArray& content, int margin = 3, int size =5, int mode = QR_MODE_8, int level = QR_ECLEVEL_L, const QColor& color = QColor(0,0,0), const QColor& bkColor = QColor(255,255,255))
        :m_content(content),m_margin(margin),m_size(size),m_mode(mode),m_level(level),m_color(color),m_bkColor(bkColor)
        ,m_casesensitive(true),m_8bit(1)
    {
    }

    int margin() const{ return m_margin;}
    void setMargin(int margin) { m_margin = margin; }

    QByteArray content()const { return m_content;}
    void setContent(const QByteArray& content) { m_content = content; m_8bit = 1;}

    QString string()const { return QString(m_content); }
    void setString(const QString& string) { m_content = string.toAscii(); m_8bit = 0;}

    int mode() const { return m_mode;}
    void setMode(int mode) { m_mode = mode;}

    int level() const { return m_level;}
    void setLevel(int level) { m_level = level;}

    bool casesensitive() const { return m_casesensitive; }
    void setCasesensitive(bool casesensitive) { m_casesensitive = casesensitive; }

    QColor color()const{ return m_color;}
    void setColor(const QColor& color){ m_color = color;}

    QColor foregroundColor()const{ return m_color;}
    void setForegroundColor(const QColor& color){ m_color = color;}

    QColor backgroundColor()const{ return m_bkColor;}
    void setBackgroundColor(const QColor& color){ m_bkColor = color;}

    QImage toImage() const;

    static QImage toImage(const QString& string, int margin = 3, int size = 5, int mode = QR_MODE_8, 
        int level = QR_ECLEVEL_L, const QColor& color = QColor(0,0,0), const QColor& bkColor = QColor(255,255,255)){ return toImage52(string,margin,size,mode,level,color,bkColor);}
    static QImage toImage(const QByteArray& string, int margin = 3, int size = 5, int mode = QR_MODE_8, 
        int level = QR_ECLEVEL_L, const QColor& color = QColor(0,0,0), const QColor& bkColor = QColor(255,255,255)){ return toImage12(string,margin,size,mode,level,color,bkColor);}

    static QImage toImage1(const QString& string){ QREncoder qr(string); return qr.toImage();}
    static QImage toImage2(const QString& string, int margin){ QREncoder qr(string,margin); return qr.toImage();}
    static QImage toImage3(const QString& string, int margin, int size){ QREncoder qr(string,margin,size); return qr.toImage();}
    static QImage toImage4(const QString& string, int margin, int size, int mode){ QREncoder qr(string,margin,size,mode); return qr.toImage();}
    static QImage toImage5(const QString& string, int margin, int size, int mode, int level){ QREncoder qr(string,margin,size,mode,level); return qr.toImage();}
    static QImage toImage51(const QString& string, int margin, int size, int mode, int level, const QColor& color){ QREncoder qr(string,margin,size,mode,level,color); return qr.toImage();}
    static QImage toImage52(const QString& string, int margin, int size, int mode, int level, const QColor& color, const QColor& bkColor){ QREncoder qr(string,margin,size,mode,level,color,bkColor); return qr.toImage();}

    static QImage toImage6(const QByteArray& string){ QREncoder qr(string); return qr.toImage();}
    static QImage toImage7(const QByteArray& string, int margin){ QREncoder qr(string,margin); return qr.toImage();}
    static QImage toImage8(const QByteArray& string, int margin, int size){ QREncoder qr(string,margin,size); return qr.toImage();}
    static QImage toImage9(const QByteArray& string, int margin, int size, int mode){ QREncoder qr(string,margin,size,mode); return qr.toImage();}
    static QImage toImage10(const QByteArray& string, int margin, int size, int mode, int level){ QREncoder qr(string,margin,size,mode,level); return qr.toImage();}
    static QImage toImage11(const QByteArray& string, int margin, int size, int mode, int level, const QColor& color){ QREncoder qr(string,margin,size,mode,level,color); return qr.toImage();}
    static QImage toImage12(const QByteArray& string, int margin, int size, int mode, int level, const QColor& color, const QColor& bkColor){ QREncoder qr(string,margin,size,mode,level,color,bkColor); return qr.toImage();}

private:
    QByteArray m_content;
    int m_margin;
    int m_size;
    int m_mode;
    int m_level;
    QColor m_color;
    QColor m_bkColor;
    bool m_casesensitive;
    int m_8bit;
};

#endif // QRENCODER_H
