#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBTNs ={{Qt::Key_0,ui->btnnum0},
               {Qt::Key_1,ui->btnnum1},
               {Qt::Key_2,ui->btnnum2},
               {Qt::Key_3,ui->btnnum3},
               {Qt::Key_4,ui->btnnum4},
               {Qt::Key_5,ui->btnnum5},
               {Qt::Key_6,ui->btnnum6},
               {Qt::Key_7,ui->btnnum7},
               {Qt::Key_8,ui->btnnum8},
               {Qt::Key_9,ui->btnnum9},
    };

    foreach(auto btn,digitBTNs)
        connect(btn,SIGNAL(clicked()),this, SLOT(btnNumclicked()));

    // connect(ui->btnnum0,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum1,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum2,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum3,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum4,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum5,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum6,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum7,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum8,SIGNAL(clicked()),this, SLOT(btnNumclicked()));
    // connect(ui->btnnum9,SIGNAL(clicked()),this, SLOT(btnNumclicked()));

    connect(ui->btnplus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorclicked()));
    connect(ui->btnminus,SIGNAL(clicked()),this, SLOT(btnBinaryOperatorclicked()));
    connect(ui->btnmultiple,SIGNAL(clicked()),this, SLOT(btnBinaryOperatorclicked()));
    connect(ui->btndivide,SIGNAL(clicked()),this, SLOT(btnBinaryOperatorclicked()));

    connect(ui->btnequal,SIGNAL(clicked()),this,SLOT(on_btnEqual_clicked()));

    connect(ui->btnpercentage,SIGNAL(clicked()),this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btninverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnsquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnsqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// QString MainWindow::calculation(bool *ok)
// {
//     double result=0;
//     if(operands.size()==2 && opcodes.size()>0){
//         //取操作数
//         double operand1 =operands.front().toDouble();
//         operands.pop_front();
//         double operand2 =operands.front().toDouble();
//         operands.pop_front();

//         //取操作符
//         QString op = opcodes.front();
//         opcodes.pop_front();
//         if(op == "+"){
//             result = operand1 + operand2;
//         }else if(op == "-") {
//             result = operand1 - operand2;
//         }else if(op == "×"){
//             result = operand1 * operand2;
//         }else if(op =="÷") {
//             if(operand2 == 0) {
//                 if(ok) *ok = false;
//                 ui->statusbar->showMessage("除数不能为0");
//                 return "错误";
//             }
//             result = operand1 / operand2;
//         }

//         operands.push_back(QString::number(result));

//         ui->statusbar->showMessage(QString("calcuation is in progress: operands is %1, opcode is %2").arg
//                                     (operands.size()).arg(opcodes.size()));
//     } else ui->statusbar->showMessage(QString("operands is %1, opcode is %2").arg
//                                     (operands.size()).arg(opcodes.size()));

//     return QString::number(result);
// }

// void MainWindow::btnBinaryOperatorclicked()
// {
//     if(operand.isEmpty()) {
//         ui->statusbar->showMessage("请先输入数字");
//         return;
//     }
//     ui->statusbar->showMessage("last operand "+ operand);
//     QString opcode = qobject_cast<QPushButton*>(sender())->text();
//     qDebug()<< opcode;
//     if(operand !=""){
//         operands.push_back(operand);
//         operand ="";
//         opcodes.push_back(opcode);
//         QString result = calculation();
//         ui->display->setText(result);
//         // operand ="";
//     }
// }


/*--------------------连续运算优化-----------------------------------------*/
QString MainWindow::calculation(bool *ok)
{
    if (ok) *ok = true; // 默认为成功状态

    // 边界条件：如果没有操作数，返回空
    if (operands.isEmpty()) {
        if (ok) *ok = false;
        return "";
    }

    // 从第一个操作数开始计算
    double result = operands.front().toDouble();
    operands.pop_front(); // 弹出第一个操作数

    // 循环处理所有运算符和剩余操作数
    while (!opcodes.isEmpty() && !operands.isEmpty()) {
        QString op = opcodes.front();
        opcodes.pop_front();

        double nextOperand = operands.front().toDouble();
        operands.pop_front();

        // 根据运算符计算
        if (op == "+") {
            result += nextOperand;
        } else if (op == "-") {
            result -= nextOperand;
        } else if (op == "×") { // 确保与按钮文本一致，建议统一为"*"
            result *= nextOperand;
        } else if (op == "÷") { // 确保与按钮文本一致，建议统一为"/"
            if (nextOperand == 0) { // 处理除数为0
                if (ok) *ok = false;
                return "错误";
            }
            result /= nextOperand;
        } else {
            if (ok) *ok = false;
            return "错误";
        }
    }

    // 计算完成后，将结果压回操作数栈（供后续运算使用，例如连续按等号）
    operands.push_back(QString::number(result));
    return QString::number(result);
}

void MainWindow::btnBinaryOperatorclicked()
{
    QString currentOpcode = qobject_cast<QPushButton*>(sender())->text();

    // 只有当当前有输入的操作数时，才保存到栈中
    if (!operand.isEmpty()) {
        operands.push_back(operand);
        operand.clear();
    }

    // 保存运算符到栈和表达式中
    if (!currentOpcode.isEmpty()) {
        opcodes.push_back(currentOpcode);
        expression += currentOpcode; // 运算符追加到表达式中
        ui->display->setText(expression);
    }
}

// void MainWindow::on_btnEqual_clicked()
// {
//     if  (operand !=""){
//         operands.push_back(operand);
//         operand ="";
//     }
//     QString result = calculation();
//     ui->display->setText(result);
// }

void MainWindow::on_btnEqual_clicked()
{
    if (!operand.isEmpty()) {
        operands.push_back(operand);
        operand.clear();
    }

    bool ok;
    QString result = calculation(&ok);
    if (ok) {
        ui->display->setText(result);
        expression = result; // 结果作为下一次计算的起始（如连续计算）
        operand = result;    // 结果作为下一次操作数的起始
    } else {
        ui->display->setText(result);
    }

    /*清空,为下次计算做准备*/
    operand.clear();
    expression.clear();
    operands.clear();
    opcodes.clear();
    /*-------------------*/
}

/*--------------------连续运算优化-----------------------------------------*/

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand.isEmpty()) {
        ui->statusbar->showMessage("请先输入数字");
        return;
    }

    if(operand !=" "){
        double result =operand.toDouble();
        operand =" ";
        QString op =qobject_cast<QPushButton *>(sender())->text();
        if(op =="%")
            result /=100.0;
        else if(op =="1/x")
            result = 1/result;
        else if(op =="x^2")
            result *=result;
        else if(op =="√")
            result =sqrt(result);

        ui->display->setText(QString::number(result));

        /*清空,为下次计算做准备*/
        operand.clear();
        expression.clear();
        operands.clear();
        opcodes.clear();
        /*-------------------*/
    }
}

void MainWindow::btnNumclicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "0" && operand == "0")
        digit = "";
    if (operand == "0" && digit != "0")
        operand = "";

    operand += digit;
    expression += digit; // 数字追加到表达式中
    ui->display->setText(expression);
}

// void MainWindow::on_btnperiod_clicked()
// {
//     QString str=ui->display->text();
//     if(!str.contains("."))str +=qobject_cast<QPushButton*>(sender())->text();
//     ui->display->setText(str);
// }

void MainWindow::on_btnperiod_clicked()
{
    if (!operand.contains(".")) {
        operand += ".";
        expression += "."; // 小数点追加到表达式中
        ui->display->setText(expression);
    }
}


void MainWindow::on_btnclear_clicked()
{

    if (!operand.isEmpty()) {
        operand = operand.left(operand.length() - 1);
        // 同时删除表达式的最后一个字符（需确保删除的是操作数部分，而非运算符）
        if (!expression.isEmpty()) {
            expression = expression.left(expression.length() - 1);
        }
        ui->display->setText(expression);
    }
}

void MainWindow::on_btnclearALL_clicked()
{
    operand.clear();
    expression.clear();
    operands.clear();
    opcodes.clear();
    ui->display->clear();
}


void MainWindow::on_btnDel_clicked()
{
    operand =operand.left(operand.length()-1);
    ui->display->setText(operand);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey,digitBTNs.keys())
    {
        if(event->key() == btnKey)
            digitBTNs[btnKey]->animateClick();
    }

    if(event->key()== Qt::Key_Equal)
        ui->btnequal->animateClick();
    else if(event->key()== Qt::Key_Plus)
        ui->btnplus->animateClick();
    else if(event->key()== Qt::Key_Minus)
        ui->btnminus->animateClick();
    else if(event->key()== Qt::Key_Asterisk)
        ui->btnmultiple->animateClick();
    else if(event->key()== Qt::Key_Slash)
        ui->btndivide->animateClick();
    else if(event->key()== Qt::Key_Period)
        ui->btnperiod->animateClick();
    else if(event->key() == Qt::Key_Backspace) {
        on_btnDel_clicked();
    }
}



void MainWindow::on_btnplusminus_clicked()
{
    if (operand.isEmpty() || operand == "0") {
        // 无输入或输入为0时，不做处理
        return;
    }

    // 判断当前操作数是否已有负号
    if (operand.startsWith('-')) {
        // 移除负号（取从索引1开始的子串）
        operand = operand.mid(1);
    } else {
        // 添加负号
        operand = "-" + operand;
    }

    // 更新表达式（需替换表达式中最后一个操作数的正负号）
    // 找到表达式中最后一个运算符的位置（用于定位当前操作数的起始位置）
    int lastOpIndex = -1;
    QList<QString> ops = {"+", "-", "×", "÷"}; // 双目运算符列表
    foreach (const QString& op, ops) {
        int idx = expression.lastIndexOf(op);
        if (idx > lastOpIndex) {
            lastOpIndex = idx;
        }
    }

    // 更新表达式中的当前操作数（从最后一个运算符之后开始替换）
    if (lastOpIndex == -1) {
        // 表达式中没有运算符，说明整个表达式就是当前操作数
        expression = operand;
    } else {
        // 替换最后一个运算符之后的部分（当前操作数）
        QString prefix = expression.left(lastOpIndex + 1); // 保留运算符及之前的内容
        expression = prefix + operand;
    }

    // 更新显示
    ui->display->setText(expression);
}



