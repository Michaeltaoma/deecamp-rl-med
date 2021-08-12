#include "patient.h"

patient::patient():age(-1),painlevel(-1),breathrate(-1),drugindex(-1)
{

}

patient::patient(QString gname,QString ggender,QString gpre_medhis, QString birtime, int gage):birthtime(birtime),name(gname),gender(ggender),pre_medhis(gpre_medhis),age(gage),painlevel(-1),breathrate(-1),drugindex(-1){

}

void patient::setbasicinfo(QString &gname, QString &ggender, QString &gpre_medhis, int &gage){
    name = gname;
    gender = ggender;
    pre_medhis=gpre_medhis;
    age = gage;
}

void patient::setCTinfo(QString& gCT_file, QString& gfindings, QString& gDocrec){
    CT_file = gCT_file;
    findings = gfindings;
    Docrec = gDocrec;
}

void patient::setRLinfo(int& gpainlevel,int& gbreathrate,int &gheatbeat, int& gdrugindex){
    painlevel = gpainlevel;
    breathrate = gbreathrate;
    drugindex = gdrugindex;
    heatbeat = gheatbeat;
}

QString patient::getname() const{
    return name;
}

QString patient::getgender() const{
    return gender;
}

QString patient::getpre_medhis() const{
    return pre_medhis;
}

QString patient::getct_file() const{
    return CT_file;
}

QString patient::getfindings() const{
    return findings;
}

QString patient::getdocrec() const{
    return Docrec;
}

QString patient::getbirthtime() const{
    return birthtime;
}

int patient::getage() const{
    return age;
}

int patient::getpainlevel() const{
    return painlevel;
}

int patient::getbreathrate() const{
    return breathrate;
}

int patient::getdrugindex() const{
    return drugindex;
}

int patient::getheartbeat() const{
    return heatbeat;
}
