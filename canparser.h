#ifndef CanParser_H
#define CanParser_H

#include <iostream>
#include <map>
#include <QObject>
#include <QVariantMap>

using namespace std;

class CanParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap retData READ retData NOTIFY emitChanges)

    QString rawCanData = nullptr;
    QString wholeCanData = nullptr;
    QString parsedData = nullptr;
    QVariantMap lastData;
    QString mapKey = nullptr;
    double inScale, inBias;

public:
    explicit CanParser(QObject *parent = nullptr);
    void receiveCan(const QString &data,
                    const QString &key,
                    QString const signalId,
                    int const &startBit,
                    int const &length,
                    double const &scale,
                    double const &bias);
    void mapToHex(QString signalId,
                  int startBit,
                  int length);
    void grabSpecificPartOfCan(QString data,
                               int startBit,
                               int length);
    void hexToBin(QString const &str);
    void parseCan(int startBit, int length);

    QVariantMap retData() const;

signals:
    void emitChanges();

public slots:

private:

};

#endif // CanParser_H
