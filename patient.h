#ifndef PATIENT_H
#define PATIENT_H

#include <QWidget>

class patient
{
public:
    patient(QString gname,QString ggender,QString gpre_medhis, QString birtime, int gage);
    patient();

    void setbasicinfo(QString &gname, QString &ggender, QString &gpre_medhis, int &gage);
    void setCTinfo(QString& gCT_file, QString& gfindings, QString& gDocrec);
    void setRLinfo(int& gpainlevel,int& gbreathrate,int &gheatbeat, int& gdrugindex);

    QString getname() const;
    QString getgender() const;
    QString getpre_medhis() const;

    QString getct_file() const;
    QString getfindings() const;
    QString getdocrec() const;
    QString getbirthtime() const;

    int getage() const;
    int getpainlevel() const;
    int getbreathrate() const;
    int getdrugindex() const;
    int getheartbeat() const;

private:
    QString birthtime;
    QString name;
    QString gender;
    QString pre_medhis;

    QString CT_file;
    QString findings;
    QString Docrec;

    int age;
    int painlevel;
    int breathrate;
    int heatbeat;
    int drugindex;
};

#endif // PATIENT_H
