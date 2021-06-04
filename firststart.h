#ifndef FIRSTSTART_H
#define FIRSTSTART_H

#include <QMainWindow>

namespace Ui {
class firstStart;
}

class firstStart : public QMainWindow
{
    Q_OBJECT

public:
    explicit firstStart(QWidget *parent = nullptr);
    ~firstStart();

private:
    Ui::firstStart *ui;
};

#endif // FIRSTSTART_H
