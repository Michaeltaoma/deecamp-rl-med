#include "choosefile.h"
#include "ui_choosefile.h"

choosefile::choosefile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choosefile)
{
    ui->setupUi(this);
}

choosefile::~choosefile()
{
    delete ui;
}
