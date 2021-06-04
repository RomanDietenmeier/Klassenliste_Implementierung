#ifndef DATENSATZBEARBEITEN_H
#define DATENSATZBEARBEITEN_H

#include <QMainWindow>
#include"KlassenkameradDAO.h"
#include"KlassenkameradDatensatz.h"
#include <QColumnView>

namespace Ui {
class DatensatzBearbeiten;
}

class DatensatzBearbeiten : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* kDAO;
    KlassenkameradDatensatz* kd;
    std::vector<KlassenkameradDatensatz*> Datensatze;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

public:
    explicit DatensatzBearbeiten(QWidget *parent = nullptr);
    ~DatensatzBearbeiten();

private:
    Ui::DatensatzBearbeiten *ui;
};

#endif // DATENSATZBEARBEITEN_H
