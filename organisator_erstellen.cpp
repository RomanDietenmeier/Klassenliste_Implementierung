#include "organisator_erstellen.h"
#include "ui_organisator_erstellen.h"

/**
 * @brief Organisator_erstellen::Organisator_erstellen
 * @param parent
 * @param dao
 * @param mw
 * @param ds
 */
Organisator_erstellen::Organisator_erstellen(QWidget *parent, KlassenkameradDAO *dao, MainWindow *mw, KlassenkameradDatensatz *ds) :
    QMainWindow(parent),
    ui(new Ui::Organisator_erstellen)
{
    ui->setupUi(this);
    this->dao= dao;
    this->mw= mw;
    this->ds= ds;

    QRandomGenerator rngGenerator;
    QTime time = QTime::currentTime();
    rngGenerator.seed(time.msec());
    qint64 rngPW = rngGenerator.generate() & std::numeric_limits<qint64>::max();
    qDebug() << rngPW;
    ui->initialpasswortVergabe->setText(QString::number(rngPW));
    ui->emailOrga->setText(ds->eMail.c_str());

}

/**
 * @brief Organisator_erstellen::~Organisator_erstellen
 */
Organisator_erstellen::~Organisator_erstellen()
{
    delete ui;
}

/**
 * @brief Organisator_erstellen::on_organisator_verteilen_clicked
 */
void Organisator_erstellen::on_organisator_verteilen_clicked()
{
    //Wohin wird das PW gespeichert?
    if (dao->setOrganisator(ds->klassenkameradID, ui->initialpasswortVergabe->text().toStdString())){
        ds->typ = Oragnisator;
        mw->printDatensatze();
    }

    this->close();
    mw->show();
}



