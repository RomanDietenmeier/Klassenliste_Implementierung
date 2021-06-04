#include "firststart.h"
#include "ui_firststart.h"

firstStart::firstStart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::firstStart)
{
    ui->setupUi(this);
}

firstStart::~firstStart()
{
    delete ui;
}
