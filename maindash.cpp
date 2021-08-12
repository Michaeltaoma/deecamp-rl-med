#include "maindash.h"
#include "dashborad.h"
#include "ui_maindash.h"

maindash::maindash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::maindash)
{
    ui->setupUi(this);
    mparent = static_cast<dashborad*>(parent);
}

maindash::~maindash()
{
    delete ui;
}

void maindash::on_ctgen_clicked()
{
    mparent->openctpage();
    return;
}
