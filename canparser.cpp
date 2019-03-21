#include "canparser.h"
#include <QDebug>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>

using ull = unsigned long long;

// binary string'i decimal'e dönüştürme
ull binaryToDecimal(QString const &data)
{
    const std::string s = data.toStdString();
    unsigned long long value = std::bitset<64>(s).to_ullong();
    return value;
}


CanParser::CanParser(QObject *parent) : QObject(parent)
{
}

// caninterface'den verileri burada alıyoruz.
void CanParser::receiveCan(const QString &data,
                           const QString &key,
                           QString const signalId,
                           int const &startBit,
                           int const &length,
                           double const &scale,
                           double const &bias)
{
    QString str = data.simplified();
    rawCanData=str;
    mapKey=key;

    inScale = scale != 0.0 ? scale : 0.0;
    inBias  = bias  != 0.0 ? bias  : 0.0;

    mapToHex(signalId, startBit, length);
}

// ******************
// burası can alıcı nokta
// burada neyi istediğimizi belirtiyoruz.
// "280.id den speed değişkeninin bitini al, bunu decimal'e çevir" komutu bu kadar basit.
// ******************
void CanParser::mapToHex(QString signalId,
                         int startBit,
                         int length)
{
    grabSpecificPartOfCan(signalId, startBit, length);
}

// bütün hex'leri 64 bitlik binarylere çeviriyoruz.
void CanParser::grabSpecificPartOfCan(QString data,
                                      int startBit,
                                      int length)
{
    QStringList list = rawCanData.split(" ", QString::SkipEmptyParts);

    int core = 0;
    wholeCanData = nullptr;
    if(list[0] == data){
        for(QStringList::iterator it = list.begin(); it != list.end(); it++) {
            core++;
            if(core > 2) {
                QString current = *it;
                hexToBin("0x"+current);
            }
        }
        parseCan(startBit, length);
    }
}

// 64 bit. içerisinden istenilen bit aralığını alıyoruz.
void CanParser::parseCan(int startBit, int length)
{
    parsedData="";
    for(int i = startBit; i < startBit+length; i++)
    {
        if(length > 7) {
            parsedData.push_back(wholeCanData[i]);
        } else {
            parsedData.push_front(wholeCanData[i]);
        }
    }
    // qDebug() << parsedData;

    /*for(int i = startBit; i < stop; i++)
    {
        if(core > 8){
            if (core == 9) {
                stop = stop + 8 - remain;
                i = i+remainStart;
            }

            parsedData.push_front(wholeCanData[i]);
            core++;
        } else {
            qDebug() << i;
            parsedData.push_front(wholeCanData[i]);
        }
        core++;

    }*/

    int val = static_cast<int>(binaryToDecimal(parsedData));
    val = inScale != 0.0 ? static_cast<int>(val * inScale) : val;
    val = inBias != 0.0 ? static_cast<int>(val + inBias) : val;

    lastData.insert(mapKey, val);
    emitChanges();
}

QVariantMap CanParser::retData() const
{
    return lastData;
}


// her bir hexadecimal veriyi bite dönüştürüyoruz.
void CanParser::hexToBin(QString const &str)
{
    stringstream ss;
    ss << hex << str.toStdString();
    unsigned n;
    ss >> n;
    bitset<8> b(n);
    // outputs "00010100"
    // qDebug() << QString::fromStdString(b.to_string())<< endl;
    wholeCanData += QString::fromStdString(b.to_string());
}
















