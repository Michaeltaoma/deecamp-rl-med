#include "drugdose.h"
#include "dashborad.h"
#include "ui_drugdose.h"

drugdose::drugdose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drugdose)
{
    ui->setupUi(this);
    mparent = static_cast<dashborad*>(parent);
}

drugdose::~drugdose()
{
    delete ui;
}

void drugdose::on_pushButton_2_clicked()
{
    if(!mparent->getpatient()){
        QMessageBox::warning(this,tr("Error"),tr("There is no patient selectd, add a patient first"));
    }
    else{
        int painvalue = ui->painlevel->value();
        int resvalue = ui->resrate->value();
        int heartrate = ui->heartrate->value();
        int drugindex = ui->drugout->currentIndex();
        mparent->getpatient()->setRLinfo(painvalue,resvalue,heartrate,drugindex);
        mparent->openmecrecpage();
    }
}

void drugdose::on_pushButton_clicked()
{
    int painvalue = ui->painlevel->value();
    int resvalue = ui->resrate->value();
    int heartrate = ui->heartrate->value();

    QString senddata = "{\"hr\":"+QString::number(heartrate)+","+"\"rr\":"+QString::number(resvalue)+",\"pl\":"+QString::number(painvalue)+"}";

    QFile file;
    file.setFileName("temprldata.txt");
    if(file.open(QIODevice::WriteOnly)){
           file.write(senddata.toLatin1());
           file.close();
    }
    CURLcode res;
    curl = curl_easy_init();
    if(curl){
        struct curl_httppost* post = NULL;
        struct curl_httppost* last = NULL;
        const char * remoteNewFileKey = "data";
        const char * remoteNewFileName = "temprldata.txt";
        curl_formadd(&post, &last, CURLFORM_COPYNAME, remoteNewFileKey,  CURLFORM_FILECONTENT, remoteNewFileName, CURLFORM_END);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curl,CURLOPT_URL,"http://1.117.203.198:8080/predictions/morphine");
        curl_easy_setopt(curl,CURLOPT_VERBOSE, 1L);
        // get response from server
        std::string header,result;
        //header contents
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &write_data);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
        //result contents
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            QMessageBox::warning(this,tr("Error"),curl_easy_strerror(res));
            qDebug() << "curl_easy_perform() failed:" << curl_easy_strerror(res);
        }
        else{
            QString hh = QString::fromStdString(header);
            QString res = QString::fromStdString(result);
            qDebug()<<res.toInt();
            ui->drugout->setCurrentIndex(res.toInt());
        }
        curl_easy_cleanup(curl);
    }
    else{
        QMessageBox::warning(this,tr("Error"),tr("curl init failed"));
    }
}
