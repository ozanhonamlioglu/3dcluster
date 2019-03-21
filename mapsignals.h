#ifndef MAPSIGNALS_H
#define MAPSIGNALS_H

#include "canparser.h"
#include <QObject>

class MapSignals : public QObject
{
    Q_OBJECT
public:
    explicit MapSignals(QObject *parent = nullptr);
    void mapSignals(QString const &data);
    CanParser canparser;

signals:

public slots:

private:

};

#endif // MAPSIGNALS_H
