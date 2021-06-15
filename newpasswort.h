#ifndef NEWPASSWORT_H
#define NEWPASSWORT_H

#include <QMainWindow>
#include "KlassenkameradDAO.h"
#include "mainwindow.h"

namespace Ui {
class NewPasswort;
}

class NewPasswort : public QMainWindow
{
    Q_OBJECT
    Verwaltung *v;
    MainWindow *mw;
    std::string id;

public:
    /**
     * @brief NewPasswort::NewPasswort
     * @param parent
     * @param v
     * @param mw
     * @param pw
     * @param mail
     */
    explicit NewPasswort(QWidget *parent = nullptr, Verwaltung* v=NULL, MainWindow *mw=NULL,string pw="-", string mail="-");
    /**
     * @brief NewPasswort::~NewPasswort
     */
    ~NewPasswort();

private slots:
    /**
     * @brief NewPasswort::on_np_speichernButton_clicked
     * speichert geändertes PW bzw gibt fehler bei der änderung aus
     */
    void on_np_speichernButton_clicked();
    /**
     * @brief NewPasswort::on_np_neuespasswort_textChanged
     * aktiviert speichern Button
     * @param arg1
     */
    void on_np_neuespasswort_textChanged(const QString &arg1);

private:
    Ui::NewPasswort *ui;
};

#endif // NEWPASSWORT_H
