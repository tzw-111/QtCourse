#include "mastarview.h"
#include "ui_mastarview.h"

MastarView::MastarView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MastarView)
{
    ui->setupUi(this);
}

MastarView::~MastarView()
{
    delete ui;
}
