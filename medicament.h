#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Medicament
{public:
    Medicament();
    Medicament(int,QString,QString);
    QString get_nom();
    QString get_reference();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int,QString,QString);
    bool rech(int);
    bool supprimer(int);
    QSqlQueryModel * trier();
    QSqlQueryModel * rechercher(int id);
    void file();
private:
    QString nom,reference;
    int id;
};


#endif // MEDICAMENT_H
