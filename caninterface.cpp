#include <QDebug>
#include "caninterface.h"

CanInterface::CanInterface()
{

}

void CanInterface::run()
{

    if(connectCan()) {
        qDebug() << "connected";
        connect(globaldevice, SIGNAL(errorOccurred(QCanBusDevice::CanBusError)), this, SLOT(canError(QCanBusDevice::CanBusError)));
        connect(globaldevice, SIGNAL(framesReceived()), this, SLOT(readCanData()));
    }

}

CanInterface::~CanInterface()
{
    globaldevice->disconnectDevice();
}

// CAN Availability
bool CanInterface::checkCanAvailable()
{
    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
    {
        // plugin available
        qDebug() << "[+] can plugin available";
        return true;
    }
    return false;
}

// Connect CAN and set "globaldevice"
bool CanInterface::connectCan()
{

    if(!checkCanAvailable())
        return false;

    QCanBusDevice *device = QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), QStringLiteral("can0"));

    device->connectDevice();

    globaldevice = device;

    qDebug() << "[+] connection made";
    return true;

}

// CAN Error method
void CanInterface::canError(QCanBusDevice::CanBusError error)
{
    qWarning("ReadCanData::canError - code: %d, error: %s", static_cast<int>(error), qPrintable(globaldevice->errorString()));
    globaldevice->disconnectDevice();
}


void CanInterface::readCanData()
{
    while(globaldevice->framesAvailable()){
        frame = globaldevice->readFrame();
        QString data;
        data=frame.toString();
        signalmapping.mapSignals(data);
    }
}
