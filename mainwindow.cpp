#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum;
bool user_secound_typing = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digitPressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digitPressed()));

    connect(ui->pushButton_plusMinus,SIGNAL(released()),this,SLOT(unary_operator_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operator_pressed()));

    connect(ui->pushButton_addition,SIGNAL(released()),this,SLOT(binary_operator_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),this,SLOT(binary_operator_pressed()));
    connect(ui->pushButton_devide,SIGNAL(released()),this,SLOT(binary_operator_pressed()));
    connect(ui->pushButton_multilple,SIGNAL(released()),this,SLOT(binary_operator_pressed()));

    ui->pushButton_addition->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multilple->setCheckable(true);
    ui->pushButton_devide->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digitPressed()
{
    QPushButton * button =(QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_addition->isChecked()  || ui->pushButton_subtract->isChecked() ||
         ui->pushButton_multilple->isChecked() || ui->pushButton_devide->isChecked()) && (!user_secound_typing))
    {
        labelNumber = button->text().toDouble();
        user_secound_typing = true;
        newLabel = QString::number(labelNumber,'g',15);
    }
    else{
        if(ui->label->text().contains('.') && button->text() == "0"){
            newLabel = ui->label->text() + button->text();
        }
        else{
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g',15);
        }

    }

    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_decimal_released()
{
    ui->label->setText(ui->label->text()+".");
}

void MainWindow::unary_operator_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if(button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    if(button->text() == "%"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

}


void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_addition->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multilple->setChecked(false);
    ui->pushButton_devide->setChecked(false);

    user_secound_typing = false;

    ui->label->setText("0");

}

void MainWindow::on_pushButton_equal_released()
{

    double lableNumber, secoundNumber;
    QString newlabel;

    secoundNumber = ui->label->text().toDouble();

    if(ui->pushButton_addition->isChecked()){
        lableNumber = firstNum + secoundNumber;
        newlabel = QString::number(lableNumber, 'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_addition->setChecked(false);
    }

    else if(ui->pushButton_subtract->isChecked()){
        lableNumber = firstNum - secoundNumber;
        newlabel = QString::number(lableNumber, 'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_subtract->setChecked(false);
    }

    else if(ui->pushButton_multilple->isChecked()){
        lableNumber = firstNum * secoundNumber;
        newlabel = QString::number(lableNumber, 'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_multilple->setChecked(false);
    }

    else if(ui->pushButton_devide->isChecked()){
        lableNumber = firstNum / secoundNumber;
        newlabel = QString::number(lableNumber, 'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_devide->setChecked(false);
    }

    user_secound_typing = false;
}

void MainWindow::binary_operator_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}

