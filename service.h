#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class service
{
    QString id,nom;
    int nbH,salaire;
public:
    service();
    service(QString,QString,int,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * trie();
    QSqlQueryModel * recherche(QString);
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,int,int);
};

#endif // SERVICE_H
