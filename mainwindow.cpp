#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dashborad.h"

size_t write_data(void *buffer,size_t size,size_t nmemb,void *userp)
{
    char *d = (char *)buffer;
    std::string *str = (std::string *)userp;

    if (str != nullptr)
    {
        str->append(d, size *nmemb);

        return size *nmemb;
    }
    return 0;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ImageViwer->setScaledContents(true);
    ui->ImpressionText->setPlaceholderText("Doctors can type in their impressions here");
    mparent = static_cast<dashborad*>(parent);
    ui->stackedWidget->setCurrentWidget(ui->choosepage);
}

MainWindow::~MainWindow()
{
    curl_global_cleanup();
    delete ui;
}

void MainWindow::on_choosect_clicked()
{
    sendfilename = QFileDialog::getOpenFileName(this,"请选择CT图片",QDir::currentPath(),"JPG files (*.jpg);;All files (*.*)");
    if(!sendfilename.isEmpty())
    {
        try {
            QPixmap* newpixmap = new QPixmap(sendfilename);
            if(!newpixmap->isNull()){
                // qDebug() << newpixmap->width() << "\t" << newpixmap->height();
                ui->ImageViwer->setPixmap(*newpixmap);
                ui->stackedWidget->setCurrentWidget(ui->viewpage);
            }
            else{
                QMessageBox::warning(this,tr("Invalid Image"),tr("Invalid image format"));
            }
        } catch (QException &e) {
            QMessageBox::warning(this,tr("Invalid Image"),tr("An error occured when opening the image."));
        }
    }
    else{
        QMessageBox::warning(this,tr("Error"),tr("Invalid file name"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(!sendfilename.isEmpty() && !ui->ImageViwer->pixmap()->isNull()){
        ui->pushButton->setText("Processing...");
        ui->pushButton->setEnabled(false);
        ui->pushButton->setStyleSheet("color:rgb(117,117,117);border:1px solid rgb(229,229,229);border-radius:5px;");
        ui->pushButton->repaint();
        FILE *fd;
        struct stat file_info;
        char *ch;
        QByteArray ba = sendfilename.toLocal8Bit();
        ch=ba.data();
        fd = fopen(ch,"rb");

        if(!fd){
             QMessageBox::warning(this,tr("Error"),tr("File Not Found Error"));
        }
        if(fstat(fileno(fd),&file_info) != 0){
             QMessageBox::warning(this,tr("Error"),tr("Invalid File size"));
        }
        curl_off_t speed_upload, total_time;
        CURLcode res;


        curl = curl_easy_init();
        if(curl){
            struct curl_httppost* post = NULL;
            struct curl_httppost* last = NULL;
            const char * remoteNewFileKey = "data";
            const char * remoteNewFileName = ch;
            curl_formadd(&post, &last, CURLFORM_COPYNAME, remoteNewFileKey,  CURLFORM_FILECONTENT, remoteNewFileName, CURLFORM_END);
            curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
            curl_easy_setopt(curl,CURLOPT_URL,"http://1.117.203.198:8080/predictions/radio2report");
            curl_easy_setopt(curl,CURLOPT_INFILESIZE_LARGE,(curl_off_t)file_info.st_size);
            curl_easy_setopt(curl,CURLOPT_VERBOSE, 1L);
            /* get response from server */
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
            else {
                 curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
                 curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);
                 //qDebug();
                 //qDebug("Speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
                 //             CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
                 //             speed_upload,
                 //             (total_time / 1000000), (long)(total_time % 1000000));
                 QString hh = QString::fromStdString(header);
                 QString res = QString::fromStdString(result);
                 ui->FindingsText->setText(res);
                 ui->FindingsText->setStyleSheet("background-color:rgb(251,252,253);\
                                                 border-top:1px solid rgb(234,234,234);\
                                                 border-left:1px solid rgb(234,234,234);\
                                                 border-right:1px solid rgb(234,234,234);\
                                                 border-bottom:0px solid rgb(234,234,234);\
                                                 border-top-left-radius:15px;\
                                                 border-top-right-radius:15px;"
                 );
                 ui->pushButton->setText("Completed");
                 ui->pushButton->setStyleSheet("color:rgb(96,177,88);border:1px solid rgb(229,229,229);border-radius:5px;");
                 ui->pushButton->setEnabled(false);
               }
             curl_easy_cleanup(curl);
        }
        else{
            QMessageBox::warning(this,tr("Error"),tr("curl init failed"));
        }
        fclose(fd);
    }
    else{
        QMessageBox::warning(this,tr("Error"),tr("Invalid file name or format"));
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    sendfilename = QFileDialog::getOpenFileName(this,"请选择CT图片",QDir::currentPath(),"JPG files (*.jpg);;All files (*.*)");
    if(!sendfilename.isEmpty())
    {
        try {
            qDebug() << sendfilename;
            QPixmap* newpixmap = new QPixmap(sendfilename);
            if(!newpixmap->isNull()){
                // qDebug() << newpixmap->width() << "\t" << newpixmap->height();
                ui->ImageViwer->setPixmap(*newpixmap);
                ui->stackedWidget->setCurrentWidget(ui->viewpage);
                ui->pushButton->setText("Start");
                ui->pushButton->setEnabled(true);
                ui->pushButton->setStyleSheet("color:rgb(33,150,243);border:1px solid rgb(229,229,229);border-radius:5px;");
            }
            else{
                QMessageBox::warning(this,tr("Invalid Image"),tr("Invalid image format"));
            }
        } catch (QException &e) {
            QMessageBox::warning(this,tr("Invalid Image"),tr("An error occured when opening the image."));
        }
    }
    else{
        QMessageBox::warning(this,tr("Error"),tr("Invalid file name"));
    }
}

void MainWindow::on_next_clicked()
{
    if(!mparent->getpatient()){
        QMessageBox::warning(this,tr("Error"),tr("There is no patient selectd, add a patient first"));
    }
    else if(sendfilename.isEmpty() || ui->FindingsText->toPlainText().isEmpty()){
        QMessageBox::warning(this,tr("Error"),tr("No CT image selected or CT image has not been processed yet"));
    }
    else{
        QString findings = ui->FindingsText->toPlainText();
        QString impression = ui->ImpressionText->toPlainText();
        mparent->getpatient()->setCTinfo(sendfilename,findings,impression);
        mparent->openrlpage();
    }
}

void MainWindow::reset(){
    ui->stackedWidget->setCurrentWidget(ui->choosepage);
    ui->pushButton->setText("Start");
    ui->pushButton->setEnabled(true);
    ui->pushButton->setStyleSheet("color:rgb(33,150,243);\
                                  border:1px solid rgb(229,229,229);\
                                  border-radius:5px;");
    ui->FindingsText->clear();
    ui->FindingsText->setStyleSheet("background-color:rgb(251,252,253);\
                                    border-top:1px solid rgb(234,234,234);\
                                    border-left:1px solid rgb(234,234,234);\
                                    border-right:1px solid rgb(234,234,234);\
                                    border-bottom:0px solid rgb(234,234,234);\
                                    border-top-left-radius:15px;\
                                    border-top-right-radius:15px;\
                                    background-image: url(:/image/nodata.png);\
                                    background-position:center;");
    ui->ImpressionText->clear();
}
