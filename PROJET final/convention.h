#ifndef CONVENTION_H
#define CONVENTION_H
#include<QString>
#include<QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class convention
{
     QString id,idfour,date_d,date_f,des;
public:
     convention();
     convention(QString,QString,QString,QString,QString);
     bool ajouter();
     QSqlQueryModel * afficher();
     bool supprimer(QString);
     bool rech(QString);
     bool modifier(QString,QString,QString,QString,QString);
     QSqlQueryModel *recherche(QString);
     QSqlQueryModel * trie(int num);
     QString total();


    ~convention(){}

};

#endif // CCONVENTION_H
