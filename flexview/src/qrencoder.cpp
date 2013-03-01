#include "qrencoder.h"


QImage QREncoder::toImage() const
{
    QRcode *code = 0;
    QImage image;
    if(m_8bit){
        code = QRcode_encodeData(m_content.length(), (const unsigned char*)m_content.data(),0 , (QRecLevel)m_level);
    }else{
        code = QRcode_encodeString(m_content.data(), 0, (QRecLevel)m_level, (QRencodeMode)m_mode, m_casesensitive ? 1 : 0);
    }
    if(code){
        int len = code->width*code->width;
        for(int i=0;i<len;i++){
            code->data[i] = code->data[i] & 1;
        }
        image = QImage((const uchar*)code->data, code->width, code->width, code->width, QImage::Format_Indexed8);
        image.setColor(0, m_bkColor.rgb() );
        image.setColor(1, m_color.rgb() );
        int w = code->width+m_margin*2;
        image = image.copy(-m_margin,-m_margin,w,w);
        image = image.scaled(w*m_size, w*m_size);
        QRcode_free(code);
    }
    return image;
}
