#ifndef FINDDB_H
#define FINDDB_H

#include <QMainWindow>

namespace Ui {
class FindDB;
}

class FindDB : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindDB(QWidget *parent = nullptr);
    ~FindDB();

private slots:

    void on_pushButton_2_Datei_clicked();

private:
    Ui::FindDB *ui;
};

#endif // FINDDB_H
