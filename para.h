#ifndef PARA_H
#define PARA_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Para
{public:
    Para();
    Para(int,QString,QString);
    QString get_Type();
    QString get_Ref();
    int get_Serial();
    bool ajouter_para();
    QSqlQueryModel * afficher_para();
    bool modifier_para(int,QString,QString);
    bool rech_para(int);
    bool supprimer_para(int);
    QSqlQueryModel * trier();
    QSqlQueryModel * rechercher(int Serial);
private:
    QString Ref,Type;
    int Serial;
};

#endif // PARA_H
