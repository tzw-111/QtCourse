#include "idatabase.h"

void IDatabase::ininDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");//添加 SQL LITE数据库驱动
    QString aFile="E:/QT/project/Lab4/Lab4a_aql/Lab4a.db";
    database.setDatabaseName(aFile);//设置数据库名称

    if(!database.open()){//打开数据库
        qDebug()<<"failed to open database";
    } else
        qDebug()<<"open database is ok";
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式,0nManualsubmit ,0nRowchange
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder); //排序
    if(!(patientTabModel->select()))//查询数据
        return false;
    thePatientSelection =new QItemSelectionModel(patientTabModel);
    return true;
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    // return "ok";

    QSqlQuery query;//查询出当前记录的所有字般
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    qDebug()<< query.lastQuery()<< query.first();

    if(query.first()&& query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        if(passwd == password)
        {
            qDebug() << "login ok";
            return "ok";
        } else {
            qDebug() << "wrong password";
            return "wrongPassword";
        }
    }
    else{
        qDebug() << "no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
