#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <QWidget>
#include "patient.h"
#include "mainwindow.h"

namespace Ui {
class medicalrecord;
}

class medicalrecord : public QWidget
{
    Q_OBJECT

public:
    explicit medicalrecord(QWidget *parent = nullptr);
    ~medicalrecord();
    void setinfomation(const patient* pat);

private:
    Ui::medicalrecord *ui;
};

#endif // MEDICALRECORD_H
