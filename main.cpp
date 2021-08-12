#include "mainwindow.h"
#include "dashborad.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    dashborad w;
    w.setWindowTitle("Intelligent Doctor");
    w.show();
    return a.exec();
}
