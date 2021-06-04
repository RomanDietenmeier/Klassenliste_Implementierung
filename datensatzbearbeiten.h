#ifndef DATENSATZBEARBEITEN_H
#define DATENSATZBEARBEITEN_H

#include <QMainWindow>

namespace Ui {
class DatensatzBearbeiten;
}

class DatensatzBearbeiten : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatensatzBearbeiten(QWidget *parent = nullptr);
    ~DatensatzBearbeiten();

private:
    Ui::DatensatzBearbeiten *ui;
};

#endif // DATENSATZBEARBEITEN_H
