#include "orga_entsperren.h"
#include "ui_orga_entsperren.h"

Orga_entsperren::Orga_entsperren(QWidget *parent, KlassenkameradDAO* dao, MainWindow *mw, KlassenkameradDatensatz *ds) :
    QMainWindow(parent),
    ui(new Ui::Orga_entsperren)
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

Orga_entsperren::~Orga_entsperren()
{
    delete ui;
}

void Orga_entsperren::on_organisator_verteilen_clicked()
{
    if(dao->organisatorEntSperren(ds->klassenkameradID,ui->initialpasswortVergabe->text().toStdString())){
        ds->gespert=false;
        mw->on_pushButton_clicked();
    }else{
        qDebug()<<"Konnte nicht entsperren!";
    }


    this->close();
    mw->show();
}

