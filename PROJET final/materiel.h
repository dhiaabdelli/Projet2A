#ifndef MATERIEL_H
#define MATERIEL_H
#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Materiel
{public:
    Materiel();
    Materiel(QString,QString,int);
    QString get_nom();
    int get_quantite();
    QString get_ref();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool rech(QString);
    bool modifier(QString,QString,int);
    QSqlQueryModel *recherche(QString ref);
    QSqlQueryModel * trie(int num);
    QString total();
private:
    QString ref,nom;
    int quantite;
};

#endif // MATERIEL_H
