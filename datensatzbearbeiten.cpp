#include "datensatzbearbeiten.h"
#include "ui_datensatzbearbeiten.h"

DatensatzBearbeiten::DatensatzBearbeiten(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatensatzBearbeiten)
{
    ui->setupUi(this);
}

DatensatzBearbeiten::~DatensatzBearbeiten()
{
    delete ui;
}
