#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator_Qt.h"
#include <QLabel>
#include <QLineEdit>

class Calculator_Qt : public QMainWindow
{
    Q_OBJECT

public:
    Calculator_Qt(QWidget *parent = nullptr);
    ~Calculator_Qt();

private:
    Ui::Calculator_QtClass ui;
public:
    double ans = 0;

private slots:
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();

    void on_dot_btn_clicked();
    void on_ans_btn_clicked();

    void on_equal_btn_clicked();
    void on_plus_btn_clicked();
    void on_minus_btn_clicked();
    void on_mult_btn_clicked();
    void on_divide_btn_clicked();

    void on_rightBracket_btn_clicked();
    void on_leftBracket_btn_clicked();
    void on_modulas_btn_clicked();
    void on_power_btn_clicked();

    void on_AC_btn_clicked();
    void on_Del_btn_clicked();

    int Solve();
};
