#ifndef CHOOSEFILE_H
#define CHOOSEFILE_H

#include <QWidget>

namespace Ui {
class choosefile;
}

class choosefile : public QWidget
{
    Q_OBJECT

public:
    explicit choosefile(QWidget *parent = nullptr);
    ~choosefile();

private:
    Ui::choosefile *ui;
};

#endif // CHOOSEFILE_H
