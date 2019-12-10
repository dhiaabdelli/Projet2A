#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class RDV
{
public:
    RDV();
    RDV(QString,QString,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,QString);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * trie(int);
    QString total();

private:
    QString id,cin,date;
};

#endif // RDV_H


