#include "mastarview.h"
#include "ui_mastarview.h"
#include <QDebug>

MastarView::MastarView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MastarView)
{
    ui->setupUi(this);

    goLoginView();
}

MastarView::~MastarView()
{
    delete ui;
}

void MastarView::goLoginView()
{
    qDebug()<<"goLoginView";
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);

    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomView()));
}

void MastarView::goWelcomView()
{
    qDebug()<<"goWelcomView";
    welcomeView = new WelcomeView(this);
    pushWidgetToStackView(welcomeView);
}

void MastarView::goDoctorView()
{
    qDebug()<<"goDoctorView";
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);
}

void MastarView::goDepartmentView()
{
    qDebug()<<"goDepartmentView";
    departmentView = new DepartmentView(this);
    pushWidgetToStackView(departmentView);
}

void MastarView::goPatientEditView()
{
    qDebug()<<"goPatientEditView";
    patientEditView = new PatientEditView(this);
    pushWidgetToStackView(patientEditView);
}

void MastarView::goPatientView()
{
    qDebug()<<"goPatientView";
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);
}

void MastarView::goPreviousView()
{
    int count=ui->stackedWidget->count();

    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget*widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MastarView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count -1);//总是显示最新加入的View
    ui->labelTitle->setText(widget->windowTitle());
}

void MastarView::on_btBack_clicked()
{
    goPreviousView();
}

