#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(QString,QString,QString,long,QString,QString);
    QString get_nom();
    QString get_prenom();
    QString get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,QString,long,QString,QString);
    QSqlQueryModel * recherche(QString id);
    QString total();

private:
    QString id,nom,address,ville,code_p;
    long tel;
};



#endif // FOURNISSEUR_H
