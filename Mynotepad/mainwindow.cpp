#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "repalcedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui->statusbar;
    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length:" + QString::number(0) + "    lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Ln:" + QString::number(0) + "    col:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("谭中文"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    SearchDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionRepalce_triggered()
{
    RepalceDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));
}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionSaveAs_triggered()
{

}


void MainWindow::on_actionOpen_triggered()
{

}

