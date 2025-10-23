#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>
#include <QStack>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;
    QString opcode;
    QString expression;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int,QPushButton*> digitBTNs;

    QString calculation(bool* = NULL);

private slots:

    // void calculation(bool *ok);

    void btnBinaryOperatorclicked();
    void btnUnaryOperatorClicked();

    void btnNumclicked();

    void on_btnperiod_clicked();

    void on_btnclear_clicked();

    void on_btnEqual_clicked();

    void on_btnDel_clicked();

    virtual void keyPressEvent(QKeyEvent *event);
    void on_btnclearALL_clicked();

    void on_btnplusminus_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
