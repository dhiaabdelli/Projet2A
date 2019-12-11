#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Medicament
{
public:
    Medicament();
    Medicament(QString,QString,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(QString,QString,QString);
    bool rech(QString);
    bool supprimer(QString);
    QSqlQueryModel * trie(int);
    QSqlQueryModel * recherche(QString data);
    void file();
private:
    QString ref,nom,idfour;
};


#endif // MEDICAMENT_H
