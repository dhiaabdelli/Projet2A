#ifndef ADMINPERSONNEL_H
#define ADMINPERSONNEL_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class adminpersonnel
{
    QString nom,prenom,email,date_nass,type,utilisateur,password,serviceid;
    int tel;
public:
    adminpersonnel();
    adminpersonnel(QString,QString,int,QString,QString,QString,QString,QString);
    QString get_nom(){
        return nom;
    }
    QString get_prenom(){
        return prenom;
    }
    QString get_utilisateur(){
        return utilisateur;
    }
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * trie();
    QSqlQueryModel * recherche(QString);
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,QString,QString,QString,int);


};
#endif // ADMINPERSONNEL_H
