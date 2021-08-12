#ifndef MAINDASH_H
#define MAINDASH_H

#include <QWidget>

class dashborad;

namespace Ui {
class maindash;
}

class maindash : public QWidget
{
    Q_OBJECT

public:
    explicit maindash(QWidget *parent = nullptr);
    ~maindash();

private slots:
    void on_ctgen_clicked();

private:
    Ui::maindash *ui;
    dashborad* mparent;
};

#endif // MAINDASH_H
