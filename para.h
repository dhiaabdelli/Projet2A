#ifndef PARA_H
#define PARA_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Para
{
public:
    Para();
    Para(QString,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(QString,QString);
    bool rech(QString);
    bool supprimer(QString);
    QSqlQueryModel * trier(int);
    QSqlQueryModel * rechercher(QString);
private:
    QString Ref,Type;
};

#endif // PARA_H
