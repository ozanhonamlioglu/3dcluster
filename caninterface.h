#pragma once
#ifndef CANINTERFACE_H
#define CANINTERFACE_H

#include "mapsignals.h"

// CAN Bus libraries
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QObject>
#include <QtCore>

class CanInterface: public QThread
{
    Q_OBJECT

public:
    CanInterface();
    ~CanInterface();
    void run();
    bool checkCanAvailable();
    bool connectCan();
    MapSignals signalmapping;

public slots:
    void canError(QCanBusDevice::CanBusError error);
    void readCanData();

private:
    QCanBusFrame frame;
    QCanBusDevice *globaldevice;
    bool connected;


};



#endif // CANINTERFACE_H
