#ifndef DRUGDOSE_H
#define DRUGDOSE_H

#include <QWidget>
#include <curl/curl.h>
#include "mainwindow.h"
#include <QFile>

class dashborad;

namespace Ui {
class drugdose;
}

class drugdose : public QWidget
{
    Q_OBJECT

public:
    explicit drugdose(QWidget *parent = nullptr);
    ~drugdose();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::drugdose *ui;
    dashborad* mparent;
    CURL* curl;
};

#endif // DRUGDOSE_H
