#include "personnel.h"
#include "ui_personnel.h"

personnel::personnel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personnel)
{
    ui->setupUi(this);
}

personnel::~personnel()
{
    delete ui;
}
