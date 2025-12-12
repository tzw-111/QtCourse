#ifndef MASTARVIEW_H
#define MASTARVIEW_H

#include <QWidget>
#include "departmentview.h"
#include "doctorview.h"
#include "loginview.h"
#include "patienteditview.h"
#include "patientview.h"
#include "welcomeview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MastarView;
}
QT_END_NAMESPACE

class MastarView : public QWidget
{
    Q_OBJECT

public:
    MastarView(QWidget *parent = nullptr);
    ~MastarView();

public slots:
    void goLoginView();
    void goWelcomView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView();
    void goPatientView();
    void goPreviousView();

private slots:
    void on_btBack_clicked();


    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);

    Ui::MastarView *ui;

    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientView *patientView;
    DepartmentView *departmentView;
    LoginView *loginView;
    PatientEditView *patientEditView;
};
#endif // MASTARVIEW_H
