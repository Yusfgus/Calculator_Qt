#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator_Qt.h"

class Calculator_Qt : public QMainWindow
{
    Q_OBJECT

public:
    Calculator_Qt(QWidget *parent = nullptr);
    ~Calculator_Qt();

private:
    Ui::Calculator_QtClass ui;
};
