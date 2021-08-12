#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QException>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <curl/curl.h>
#include <stdio.h>
#include <QTextCodec>


class dashborad;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void reset();

private slots:
    void on_choosect_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_next_clicked();


private:
    dashborad* mparent;
    Ui::MainWindow *ui;
    CURL *curl;
    QString sendfilename;
};

size_t write_data(void *buffer,size_t size,size_t nmemb,void *userp);

#endif // MAINWINDOW_H
