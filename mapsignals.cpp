#include "mapsignals.h"

MapSignals::MapSignals(QObject *parent) : QObject(parent)
{

}

void MapSignals::mapSignals(QString const &data)
{
    // speed -> (hexadecimal raw can data), (id), (start bit), (bit length), (scale), (bias)
    canparser.receiveCan(data, "speed", "280", 48, 10, 0.5, 0.0);
    // Gear
    // canparser.receiveCan(data, "gear", "333", 7, 2, 0.0, 0.0);
    canparser.receiveCan(data, "gear", "280", 43, 2, 0.0, 0.0);
    // remaining range
    canparser.receiveCan(data, "remaining", "280", 16, 8, 2.0, 0.0);
    // kwh
    canparser.receiveCan(data, "kwh", "280", 24, 8, 0.0, -100.0);
    // epb
    canparser.receiveCan(data, "epb", "280", 60, 1, 0.0, 0.0);

    // STAT_TurnLightLeft
    canparser.receiveCan(data, "turnLeft", "511", 8, 2, 0.0, 0.0);
    // STAT_TurnLightRight
    canparser.receiveCan(data, "turnRight", "511", 10, 2, 0.0, 0.0);
    // STAT_HazardLight
    canparser.receiveCan(data, "hazardLight", "511", 22, 2, 0.0, 0.0);
    // STAT_LowBeam_Act
    canparser.receiveCan(data, "lowBeam", "511", 20, 2, 0.0, 0.0);
    // STAT_HighBeam_Act
    canparser.receiveCan(data, "highBeam", "511", 18, 2, 0.0, 0.0);
    // STAT_ParkLightLeft
    canparser.receiveCan(data, "parkLightLeft", "511", 26, 2, 0.0, 0.0);
    // STAT_ParkLightRight
    canparser.receiveCan(data, "parkLightRight", "511", 28, 2, 0.0, 0.0);
    // STAT_FogFront
    canparser.receiveCan(data, "frontFog", "511", 30, 2, 0.0, 0.0);
    // STAT_FogRear
    canparser.receiveCan(data, "rearFog", "511", 16, 2, 0.0, 0.0);
}
