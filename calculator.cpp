#include "calculator.h"
#include "./ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++){
        QString buttonName = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()),this,SLOT(NumPressed()));
    }
    connect(ui->buttonAddition, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->buttonSubtratction, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->buttonMultiply, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->buttonDivide, SIGNAL(released()),this,SLOT(MathButtonPressed()));

    connect(ui->buttonEquals, SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    connect(ui->buttonSign, SIGNAL(released()),this,SLOT(ChangeNumberSignPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(buttonVal);
    } else{
        QString newVal = displayVal + buttonVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton*)sender();
    QString buttonVal = button->text();
    if(QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(buttonVal, "*", Qt::CaseInsensitive) == 0){
        mulTrigger = true;
    }else if(QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else{
        subTrigger = true;
    }
    ui->Display->setText("");
}


void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dbDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || mulTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dbDisplayVal;
        }else if(subTrigger){
            solution = calcVal - dbDisplayVal;
        }else if(mulTrigger){
            solution = calcVal * dbDisplayVal;
        }else{
            solution = calcVal / dbDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSignPressed(){
     QString displayVal = ui->Display->text();
     QRegularExpression reg("[-]?[0-9.]*");
     if(reg.match(displayVal).hasMatch()){
         double dblDisplayVal = displayVal.toDouble();
         double dblDisplayValSign = -1 * dblDisplayVal;
         ui->Display->setText(QString::number(dblDisplayValSign));
     }
}
