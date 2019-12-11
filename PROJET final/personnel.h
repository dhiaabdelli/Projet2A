#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <QDialog>

namespace Ui {
class personnel;
}

class personnel : public QDialog
{
    Q_OBJECT

public:
    explicit personnel(QWidget *parent = nullptr, QString username = "" );
    ~personnel();

private:
    Ui::personnel *ui;
};

#endif // PERSONNEL_H
