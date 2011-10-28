#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include "qextserialport.h"


template<typename T>
QString settingString(T s);

QString  BaudRateString( BaudRateType baudRate);
QString  DataBitsString(DataBitsType dataBits);
QString  ParityString(ParityType parity);
QString  StopBitsString(StopBitsType stopBits);
QString  FlowString(FlowType flow);

typedef void(*pfnTranverse_t)(const QString& name, const QString& setting, bool groupName, void* context);

void tranverseSetting(pfnTranverse_t pfn, void* context);

QString  PortSettingString(const PortSettings& setting);
void  UpdatePortSettingString(PortSettings& setting, const QString& str);
#endif // SERIALHELPER_H