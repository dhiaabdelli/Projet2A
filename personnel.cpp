#include "personnel.h"
#include "ui_personnel.h"

personnel::personnel(QWidget *parent, QString username) :
    QDialog(parent),
    ui(new Ui::personnel)
{
    ui->setupUi(this);
    ui->username->setText(username);


    QPixmap pixmap(":/list-ingredients-24.png");
    QIcon ButtonIcon(pixmap);
    ui->btnRDV->setIcon(ButtonIcon);
    ui->btnRDV->setIconSize(QSize(24, 24));
    ui->btnRDV->setFixedSize(81,81);



    QPixmap pixmap2(":/contacts-128.png");
    QIcon ButtonIcon2(pixmap2);
    ui->btnPAT->setIcon(ButtonIcon2);
    ui->btnPAT->setIconSize(QSize(24, 24));
    ui->btnPAT->setFixedSize(81,81);


    QPixmap pixmap3(":/clinic-128.png");
    QIcon ButtonIcon3(pixmap3);
    ui->btnBloc->setIcon(ButtonIcon3);
    ui->btnBloc->setIconSize(QSize(24, 24));
    ui->btnBloc->setFixedSize(81,81);
}

personnel::~personnel()
{
    delete ui;
}
