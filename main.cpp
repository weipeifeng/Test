#include "MainWindow.h"
#include <QApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QPoint>
#include <QSize>
#include <QDebug>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <string.h>
using namespace std;

struct WindowLocation{
    QSize windowSize;
    QPoint windowPosition;
    QMutex mutex;
};
struct WindowLocation2{
    QSize windowSize;
    QPoint windowPosition;
    QMutex mutex;
};

std::string HexToBin(const std::string &strHex)
 {
    //hex conversion to bin
     if (strHex.size() % 2 != 0)
     {
         return "";
     }

     string binTable[16] = {
         "0000", "0001", "0010", "0011",
         "0100", "0101", "0110", "0111",
         "1000", "1001", "1010", "1011",
         "1100", "1101", "1110", "1111"
     };

     string strBin;
     int n = 16;
     int abc = strHex.size();
     for (size_t i = 0; i < strHex.size(); i++)
     {
         char c = strHex[i];
         if (c >= 'a' && c <= 'f') n = c - 'a' + 10;
         if (c >= 'A' && c <= 'F') n = c - 'A' + 10;
         if (c >= '0' && c <= '9') n = c - '0';
         string sTmp = binTable[n];
         strBin.append(sTmp);
     }
    return strBin;
}

bool decodeInfoOfPower(QByteArray& info)
{
    //Input format:0x7E...E7
    QByteArray info1 = "7E0000A1A2B3B4C5C6D7D8E9E0F1F2131415161718192021222324E7";
    QVector<double> voltageVector;
    QVector<double> currentVector;
    QVector<int> voltageFaultCodeVector;
    QVector<int> currentFaultCodeVector;

    QString input(info1);
    int infoLength = input.length();
    if(input.startsWith("7E") && input.endsWith("E7") && infoLength == 56) {

        for (int i=6;i<42;i+=4) {
            QString str_v = input.mid(i,2);
            QString str_c = input.mid(i+2,2);

            bool ok_v;
            int v = str_v.toInt(&ok_v,16);
            if (ok_v){
                voltageVector.append(v*1.0);
            }else {
                return false;
            }

            bool ok_c;
            int c = str_c.toInt(&ok_c,16);
            if (ok_c){
                currentVector.append(c*0.5);
            }else {
                return false;
            }
        }

        //resolve the voltage fault code
        QVector<int> index;
        index << 8<<7<<6<<5<<4<<3<<2<<1<<9;

        QString strCode;
        std::string strHex;
        std::string strBin;
        //voltage 1-8 fault code
        for (int in = 42;in<46;in+=2)
        {
            strCode = input.mid(in,2);
            strHex = strCode.toStdString();
            strBin = HexToBin(strHex);
            if (strBin.size() !=0 && strBin.size()%2 ==0){
                for (int i = 0;i<strBin.size();i+=2) {
                    char  ctmp[2];
                    strBin.copy(ctmp,2,i);
                    //QString status = QString::fromLocal8Bit(ctmp);
                    QString status = QString(QLatin1String(ctmp));
                    bool ok;
                    int faultCode = status.toInt(&ok,2);
                    int bb = 0;
                    if (ok) {
                        switch (faultCode) {
                        case 0:
                            voltageFaultCodeVector.append(0);
                            break;
                        case 1:
                            voltageFaultCodeVector.append(1);
                            break;
                        case 2:
                            voltageFaultCodeVector.append(2);
                            break;
                        case 3:
                            voltageFaultCodeVector.append(3);
                            break;
                        default:
                            break;
                        }
                    }
                    }
                }
        }
        //voltage 9 fault code
        strCode = input.mid(46,2);
        strHex = strCode.toStdString();
        strBin = HexToBin(strHex);
        if (strBin.size() !=0 && strBin.size()%2 ==0) {
                char  ctmp[2];
                strBin.copy(ctmp,2,strBin.size()-2);
                //QString status = QString::fromLocal8Bit(ctmp);
                QString status = QString(QLatin1String(ctmp));
                bool ok;
                int faultCode = status.toInt(&ok,2);
                if (ok) {
                    switch (faultCode) {
                        case 0:
                            voltageFaultCodeVector.append(0);
                            break;
                        case 1:
                            voltageFaultCodeVector.append(1);
                            break;
                        case 2:
                            voltageFaultCodeVector.append(2);
                            break;
                        case 3:
                            voltageFaultCodeVector.append(3);
                            break;
                        default:
                            break;
                        }
                  }

         }
        //resolve the current fault code
        //current 1-8 fault code
        for (int in = 48;in<52;in+=2){
            strCode = input.mid(in,2);
            strHex = strCode.toStdString();
            strBin = HexToBin(strHex);
            if (strBin.size() !=0 && strBin.size()%2 ==0){
                    for (int i = 0;i<strBin.size();i+=2) {
                        char  ctmp[2];
                        strBin.copy(ctmp,2,i);
                        //QString status = QString::fromLocal8Bit(ctmp);
                        QString status = QString(QLatin1String(ctmp));
                        //QString status(ctmp);
                        bool ok;
                        int faultCode = status.toInt(&ok,2);
                        int bb = 0;
                        if (ok) {
                            switch (faultCode) {
                            case 0:
                                currentFaultCodeVector.append(0);
                                break;
                            case 1:
                                currentFaultCodeVector.append(1);
                                break;
                            case 2:
                                currentFaultCodeVector.append(2);
                                break;
                            case 3:
                                currentFaultCodeVector.append(3);
                                break;
                            default:
                                break;
                            }
                        }
                        }
                    }
        }
        //current 9 fault code
        strCode = input.mid(52,2);
        strHex = strCode.toStdString();
        strBin = HexToBin(strHex);
        if (strBin.size() !=0 && strBin.size()%2 ==0) {
                    char  ctmp[2];
                    strBin.copy(ctmp,2,strBin.size()-2);
                    //QString status = QString::fromLocal8Bit(ctmp);
                    QString status = QString(QLatin1String(ctmp));
                    bool ok;
                    int faultCode = status.toInt(&ok,2);
                    if (ok) {
                        switch (faultCode) {
                            case 0:
                                currentFaultCodeVector.append(0);
                                break;
                            case 1:
                                currentFaultCodeVector.append(1);
                                break;
                            case 2:
                                currentFaultCodeVector.append(2);
                                break;
                            case 3:
                                currentFaultCodeVector.append(3);
                                break;
                            default:
                                break;
                            }
                      }

        }

        //swap the currentCodeVector and voltageCodeVector according to the protocol
        QVector<int> tmpVector1(9),tmpVector2(9);
        for (int i = 0;i<index.size();i++) {
            int b1 = index.value(i);
            //tmpVector1[b1]= 11;
            //tmpVector2[b1]= 12;

            //tmpVector1[b1]= voltageFaultCodeVector.value(i);
            //tmpVector2[b1]= currentFaultCodeVector.value(i);
            tmpVector1[index.value(i)-1]= voltageFaultCodeVector.at(i);
            tmpVector2[index.value(i)-1]= currentFaultCodeVector.at(i);

        }
        voltageFaultCodeVector.clear();
        voltageFaultCodeVector = tmpVector1;
        currentFaultCodeVector.clear();
        currentFaultCodeVector = tmpVector2;


    }else {
        qDebug()<<"resolve voltage failed"<<endl;
    }
    return true;
}
double QString2Voltage(const QString &strVol)
{
    return 1.0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    char ctmp[3] = "01";
    QString status1 = QString(QLatin1String(ctmp));
    QString status2 = QString::fromLocal8Bit(ctmp);
    QString status3 = QString(QLatin1String(ctmp));
    //isDecodeSuccessful = decodeInfoOfPower(info);



    return a.exec();
}
