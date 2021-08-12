#include "medicalrecord.h"
#include "ui_medicalrecord.h"

medicalrecord::medicalrecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicalrecord)
{
    ui->setupUi(this);
}

medicalrecord::~medicalrecord()
{
    delete ui;
}

void medicalrecord::setinfomation(const patient *pat){
    ui->nameshow->setText(pat->getname());
    //ui->gendershow->setText(pat->getgender());
    if(pat->getgender()=="M"){
        ui->gendershow->setStyleSheet("background-image:url(:/image/M.png);\
          background-repeat:no-repeat;\
          background-position:center");
    }
    else{
        qDebug()<<"here";
        ui->gendershow->setStyleSheet("background-image:url(:/image/F.png);\
          background-repeat:no-repeat;\
          background-position:center");
    }
    ui->ageshow->setText(QString::number(pat->getage()));
    ui->hisshow->setText(pat->getpre_medhis());
    QPixmap* newpixmap = new QPixmap(pat->getct_file());
    if(!newpixmap->isNull()){
        ui->ImageViwer->setPixmap(*newpixmap);
    }
    if(!pat->getfindings().isEmpty()){
        ui->FindingsText->setText(pat->getfindings());
    }
    if(!pat->getdocrec().isEmpty()){
        ui->rectext->setText(pat->getdocrec());
    }
    ui->painshow->setText(QString::number(pat->getpainlevel()));
    ui->resshow->setText(QString::number(pat->getbreathrate()));
    ui->heartshow->setText(QString::number(pat->getheartbeat()));
    ui->drugoutshow->setCurrentIndex(pat->getdrugindex());
}
