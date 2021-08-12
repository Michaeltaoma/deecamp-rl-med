#ifndef DASHBORAD_H
#define DASHBORAD_H

#include "mainwindow.h"
#include "maindash.h"
#include "drugdose.h"
#include "medicalrecord.h"
#include "patient.h"
#include <QMainWindow>

namespace Ui {
class dashborad;
}

class dashborad : public QMainWindow
{
    Q_OBJECT

public:
    explicit dashborad(QWidget *parent = nullptr);
    ~dashborad();
    void openctpage();
    patient* getpatient();
    void openrlpage();
    void openmecrecpage();
    void reset();

private slots:
    void on_ctgen_clicked();

    void on_drugdose_clicked();

    void on_mrg_clicked();

    void on_newp_clicked();

    void on_newp_2_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::dashborad *ui;
    MainWindow *ctpage;
    drugdose* drug;
    medicalrecord* medicalrec;
    patient* pat;
};

#endif // DASHBORAD_H
