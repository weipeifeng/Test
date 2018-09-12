#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QHostAddress>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    udpSocket=new QUdpSocket();

//    init();
//    createConnections();
//    slot_load_database();

    MyWidget*widget = new MyWidget(this);
   MyFrame *frame = new MyFrame(this);
   widget->setFixedSize(50, 50);
   frame->setFixedSize(50, 50);
   widget->move(0, 0);
   frame->move(0, 50);
}
void MainWindow::init()
{
    //faultModel_ = new QSqlRelationalTableModel(this);
    //ui->tableView->setModel(faultModel_);
}
void MainWindow::createConnections()
{
    connect(ui->btn3,SIGNAL(clicked(bool)),this,SLOT(slot_process_btn3()));
    connect(this, SIGNAL(signal_transform_QString_args(QString,QString,QString,QString&)),
            this, SLOT(slot_transform_QString_args(QString,QString,QString,QString&)));

    //
    connect(ui->btnLoadDatabase,SIGNAL(clicked(bool)),this,SLOT(slot_load_database()));
    connect(ui->btnSearch,SIGNAL(clicked(bool)),this,SLOT(slot_search()));
    connect(ui->btnSearch_2,SIGNAL(clicked(bool)),this,SLOT(slot_search2()));


}
void MainWindow::slot_search()
{
    //QString searchWords = ui->edtSearchWords->text();
//    QString filter1 = QString("code = '%1'").arg(searchWords);
//    faultModel_->setFilter(filter1);
//    int rowNum1 = faultModel_->rowCount();

    //QString filter2 = QString("id = '%1'").arg("200");
    //faultModel_->setFilter(QObject::tr("monitor = '%1'").arg("故障代码1"));

//    QString searchWords = "故障代码1";
//    faultModel_->setFilter(tr("monitor = '%1'").arg("456"));


//    faultModel_->setFilter(tr("id = %1").arg("13"));
//    faultModel_->setFilter(tr("highEvent = '%1'").arg("11"));
//    faultModel_->setFilter(tr("medEvent = '%1'").arg("12"));
//    faultModel_->setFilter(tr("code = '%1'").arg("BH007"));
//    faultModel_->setFilter(tr("monitor = '%1'").arg("123"));
//    faultModel_->setFilter(tr("measurement = '%1'").arg("456"));
//    faultModel_->setFilter(tr("content = '%1'").arg("789"));
//    faultModel_->setFilter(tr("class = '%1'").arg("10"));
//    faultModel_->setFilter(tr("subsystem = '%1'").arg("1"));
//    faultModel_->setFilter(tr("solution = '%1'").arg("12"));
//    faultModel_->setFilter(tr("confidence = '%1'").arg("13"));
//    faultModel_->setFilter(tr("lowEvent = '%1'").arg("13"));
//    faultModel_->setFilter(tr("lowEvent = '%1'").arg("相机控制无效"));
    faultModel_->setFilter(tr("lowEvent = '%1'").arg(QStringLiteral("相机控制无效")));

    faultModel_->select();
    int rowNum2 = faultModel_->rowCount();

    ui->tableView->setModel(faultModel_);

    int model_rows1 = faultModel_->rowCount();
    qDebug()<<model_rows1<<endl;
}

void MainWindow::slot_search2()
{
    QString searchWords = ui->edt2->text();

    QSqlQuery query;
    if (query.exec(QString("select * from Fault where code = '%1'").arg(searchWords))) {
//    if (query.exec(QString("select * from Fault where monitor = '%1'").arg(strSearch))) {
//    if (query.exec(QString("select * from Fault where id = %1").arg("110"))) {
        while(query.next()) {
            //method1:
            QSqlRecord rec = query.record();
            int fieldNum = rec.count();
            QStringList strList;
            QStringList infoList;
            for (int i = 0; i< rec.count();i++) {
                strList<<rec.fieldName(i);
                infoList<<rec.value(rec.fieldName(i)).toString();
            }

            for (int i = 0; i< rec.count();i++) {
                QString str_tmp = infoList[i];
                std::string ss = str_tmp.toStdString();
                qDebug()<<str_tmp<<endl;
            }



////            int rowIndex = query.at();
//            int columnNum = rec.count();
//            //获取"name"字段所在列的编号，列从左向右编号，最左边的编号为0
//            int fieldNo_id = rec.indexOf("id");
//            int fieldNo_confidence = rec.indexOf("confidence");
//            //获取id字段的值，并转换为int型
//            int id = rec.value(fieldNo_id).toInt();
//            int fieldNo_code = rec.indexOf("code");
//            QString str_code = rec.value(fieldNo_code).toString();
//            std::string str_code_std = str_code.toStdString();

//            qDebug()<<str_code<<endl;

//            QString ss = "apf";
            //qDebug()<<str_code_std<<endl;


            //获取"name"字段所在列的编号，列从左向右编号，最左边的编号为0


//            qDebug()<<QObject::tr("fault table 字段数")<<rec.count();
//            qDebug()<<strList<<endl;

            //method2:
            //获取query所指向的记录在结果集中的编号
//            int rowIndex = query.at();
//            int columnNum = query.record().count();
//            //获取"name"字段所在列的编号，列从左向右编号，最左边的编号为0
//            int fieldNo_id = query.record().indexOf("id");
//            //获取id字段的值，并转换为int型
//            int id = query.value(fieldNo_id).toInt();

//            //获取"name"字段所在列的编号，列从左向右编号，最左边的编号为0
//            int fieldNo_code = query.record().indexOf("code");
//            //获取id字段的值，并转换为int型


////            QString str_1 = rec.value(1).toString();
////            QString str_2 = rec.value(2).toString();
////            QString str_3 = rec.value(3).toString();

////            QVariant var_code = query.value(fieldNo_code);
////            QString str_code = query.value(fieldNo_code).toString();
////            std::string str_c = str_code.toStdString();
////            qDebug()<<var_code.toString()<<endl;
////            qDebug()<<str_code<<endl;

//            QString str_code2 = rec.value(fieldNo_code).toString();
//            std::string str_c2 = str_code2.toStdString();
//            qDebug()<<str_code2<<endl;
//            qDebug()<<str_c<<endl;
        }
    }
}

void MainWindow::slot_load_database()
{
    QString currentPath = QDir::currentPath();
    QString database_name = "./FaultEvent5.db";
    if (!openDatabase(database_name)){
        QMessageBox::information(0, tr("tip"), tr("open database file failed"));//"提示","数据库文件打开错误"
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_updateUI_UP1(int index,const QVector<double> &voltageVector,
                       const QVector<double> &currentVector)
{
   qDebug()<<"slot";
   QVector<double> v3;
   QVector<double> v4;
   v3 = voltageVector;
   v4 = currentVector;
}
void MainWindow::slot_process_btn3()
{
    QString str1("wpf1");
    QString str2("wpf2");
    QString str3("wpf3");
    QString str4("wpf4");
    emit signal_transform_QString_args(str1,str2,str3,str4);
    int i1,i2,i3,i4;
    i1 = 1;
    i2 = 11;
    i3 = 21;
    i4 = 31;
    emit signal_transform_int_args(i1,i2,i3,i4);
}

void MainWindow::slot_transform_QString_args(QString str1, QString str2, QString str3, QString &str4)
{
    qDebug()<<str1<<endl;
    qDebug()<<str2<<endl;
    qDebug()<<str3<<endl;
    qDebug()<<str4<<endl;
    str1 = "wrx1";
    str2 = "wrx2";
    str3 = "wrx3";
    str4 = "wrx4";
    qDebug()<<str1<<endl;
    qDebug()<<str2<<endl;
    qDebug()<<str3<<endl;
    qDebug()<<str4<<endl;
}

void MainWindow::slot_transform_int_args(int i1, int i2, int i3,int& i4)
{
    qDebug()<<i1<<endl;
    qDebug()<<i2<<endl;
    qDebug()<<i3<<endl;
    qDebug()<<i4<<endl;
    i1 = 11;
    i2 = 111;
    i3 = 211;
    i4 = 311;
    qDebug()<<i1<<endl;
    qDebug()<<i2<<endl;
    qDebug()<<i3<<endl;
    qDebug()<<i4<<endl;
}
bool MainWindow::openDatabase(const QString& database_name)
{
    //读取数据库文件
    if (QFile::exists("./FaultEvent5.db")) {
        db_ = QSqlDatabase::addDatabase("QSQLITE");
        db_.setDatabaseName("FaultEvent5.db");
    } else {
        return false;
    }

    if(!db_.open())
        return false;

    int nFaults = 0;
    int nSystems = 0;

    systemModel_ = new QSqlTableModel(this,db_);
    systemModel_->setTable("system");
    if (systemModel_->select()) {
        while (systemModel_->canFetchMore()) {
            systemModel_->fetchMore();
        }
        nSystems = systemModel_->rowCount();
    }
    //faultModel_ = nullptr;
    faultModel_ = new QSqlRelationalTableModel(this,db_);
    //faultModel_ = new FaultInfoModel(this,db_);
    faultModel_->setTable("Fault");
    faultModel_->setRelation(9,QSqlRelation("system","id","sysname"));
    faultModel_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if (faultModel_->select()) {
        while (faultModel_->canFetchMore()) {
            faultModel_->fetchMore();
        }
        nFaults = faultModel_->rowCount();
    }
    ui->tableView->setModel(faultModel_);

    if((nFaults >0) &&(nSystems>0))
        return true;
    else
        return false;
}
