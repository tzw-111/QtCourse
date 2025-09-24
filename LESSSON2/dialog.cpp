#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // connect(ui->btuClear,)
    // connect(ui->);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnClear_clicked(){
    ui->textEdit->clear();
    qDebug()<<"I am clicked";
    // printf("I am clicked");
}

void Dialog::on_btnExit_clicked(){
    QApplication::quit();
};
