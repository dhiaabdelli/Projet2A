#ifndef PATIENT_H
#define PATIENT_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class patient
{
    QString cin,tel,nom,prenom,email;

public:
    patient();
    patient(QString,QString,QString,QString,QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * trie(int num);
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,QString,QString,QString);
    QString total();
    ~patient(){}


};

#endif // PATIENT_H
