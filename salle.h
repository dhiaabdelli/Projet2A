#ifndef SALLE_H
#define SALLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class salle
{
public:
    salle();
    salle(int,QString);
    QString get_bloc();
    int get_num();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool rech(int);
    bool modifier(int,QString);
    QSqlQueryModel * trie(int);
    QSqlQueryModel * Rechercher(long num);





private:
    int num;
    QString bloc;


};

#endif // SALLE_H
