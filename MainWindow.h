#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

#include <QDialog>
#include <QFrame>

namespace Ui {
class MainWindow;
}

class MyWidget : public QWidget {
   Q_OBJECT
public:
    MyWidget(QWidget*parent = 0) : QWidget(parent) {
       this->setStyleSheet("QWidget{background:#ff0000;}QWidget:hover{background:#00ff00;}");
    }
};

class MyFrame : public QFrame {
    Q_OBJECT
public:
    MyFrame(QWidget*parent = 0) : QFrame(parent) {
       this->setStyleSheet("QWidget{background:#ff0000;}QWidget:hover{background:#00ff00;}");
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();

    void createConnections();

    bool openDatabase(const QString& database_name);

private:
    Ui::MainWindow *ui;

    QUdpSocket* udpSocket;
    QUdpSocket* localUdpSocket;

    QAbstractSocket::SocketState s1;
    QAbstractSocket::SocketState s2;

    QSqlDatabase db_;
    QSqlRelationalTableModel *faultModel_;
    //FaultInfoModel *faultModel_;
    QSqlTableModel *systemModel_;

signals:
    void signal_updateUI_UP1(int index,const QVector<double> &voltageVector,
                             const QVector<double> &currentVector);
    void signal_transform_QString_args(const QString str1, const QString &str2, QString str3, QString &str4);
    void signal_transform_int_args(const  int int1, const int &int2, int int3, int &int4);

public slots:
    void slot_updateUI_UP1(int index,const QVector<double> &voltageVector,
                           const QVector<double> &currentVector);
    void slot_process_btn3();
    //void slot_transform_args(const QString str1, const QString &str2, QString str3, QString &str4);
    void slot_transform_QString_args(QString str1, QString str2, QString str3, QString &str4);
    void slot_transform_int_args(int int1, int int2, int int3, int& int4);

    void slot_load_database();
    void slot_search();
    void slot_search2();
private:
    int b;

};

#endif // MAINWINDOW_H
