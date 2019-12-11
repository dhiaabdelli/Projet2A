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
    QSqlQueryModel * trie(int num);
    QSqlQueryModel * recherche(QString);
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,int,int);
    QString getId(QString);
};

#endif // SERVICE_H
