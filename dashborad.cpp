#include "dashborad.h"
#include "ui_dashborad.h"

dashborad::dashborad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dashborad)
{
    ui->setupUi(this);
    pat = NULL;
    ctpage = new MainWindow(this);
    drug = new drugdose(this);
    medicalrec = new medicalrecord(this);
    ui->stackedWidget->addWidget(ctpage);
    ui->stackedWidget->addWidget(drug);
    ui->stackedWidget->addWidget(medicalrec);
    ui->stackedWidget->setCurrentWidget(ctpage);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->search->setPlaceholderText("Search patients or record....");
}

patient* dashborad::getpatient(){
    return pat;
}

dashborad::~dashborad()
{
    delete ui;
}

void dashborad::on_ctgen_clicked()
{
    ui->stackedWidget->setCurrentWidget(ctpage);
}

void dashborad::openctpage(){
    ui->stackedWidget->setCurrentWidget(ctpage);
}

void dashborad::on_drugdose_clicked()
{
    ui->stackedWidget->setCurrentWidget(drug);
}

void dashborad::on_mrg_clicked()
{
    ui->stackedWidget->setCurrentWidget(medicalrec);
}

void dashborad::on_newp_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void dashborad::on_newp_2_clicked(){
    QDateTime currdate= QDateTime::currentDateTime();
    QString strdate = currdate.toString("yyyy-MM-dd hh:mm:ss");
    pat = new patient(
                ui->lineName->text(),
                ui->comboBox->currentText(),
                ui->history->toPlainText(),
                strdate,
                ui->age->value()
               );
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->nameshow->setText(pat->getname());
    //ui->ageshow->setText(pat->getage());
    ui->ageshow->setValue(pat->getage());
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
    ui->timeshow->setText(pat->getbirthtime());
    ui->hisshow->setText(pat->getpre_medhis());
}

void dashborad::openrlpage(){
    ui->stackedWidget->setCurrentWidget(drug);
}

void dashborad::openmecrecpage(){
    ui->stackedWidget->setCurrentWidget(medicalrec);
    medicalrec->setinfomation(pat);
}

void dashborad::reset(){
    if(!pat){
        delete pat;
    }
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->stackedWidget->setCurrentWidget(ctpage);
    ctpage->reset();
    ui->lineName->clear();
    ui->age->cleanText();
    ui->history->clear();
}

void dashborad::on_pushButton_6_clicked()
{
    reset();
}
