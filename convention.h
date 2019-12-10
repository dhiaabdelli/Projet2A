#ifndef CONVENTION_H
#define CONVENTION_H
#include<QString>
#include<QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class convention
{
    int code,cin;
     QDate date_creation;
public:
    convention();
    convention(int,int,QDate);
    int getcode(){return code;}
    void setcode(int code){this->code=code;}
    void setdate_creation(QDate date_creation){this->date_creation=date_creation;}
    bool ajouter_convention();
    QSqlQueryModel * afficher_convention();
    bool supprimer_convention(int);
 bool rech(int);
        bool modifier(int,QDate);
        QSqlQueryModel * afficher_convention_ch(int);
        QSqlQueryModel * trierconvention_code();
        QSqlQueryModel * Rechercher(long);

       // bool  rech_convention(int code);


    ~convention(){}

};

#endif // CCONVENTION_H
