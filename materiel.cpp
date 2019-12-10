#include "materiel.h"

#include <QDebug>
Materiel::Materiel()
{
    ref="";
    nom="";
    quantite=0;
}
Materiel::Materiel(QString ref,QString nom,int quantite)
{
  this->ref=ref;
  this->nom=nom;
  this->quantite=quantite;
}
QString Materiel::get_ref(){return  ref;}
QString Materiel::get_nom(){return  nom;}
int Materiel::get_quantite(){return quantite;}


bool Materiel::ajouter()
{
QSqlQuery query;
QString res1= QString::number(quantite);

query.prepare("INSERT INTO materiel (REF, NOM, QUANTITE) "
                    "VALUES (:ref, :nom, :quantite)");
query.bindValue(":ref", ref);
query.bindValue(":nom", nom);
query.bindValue(":quantite", res1);

return    query.exec();
}

QSqlQueryModel * Materiel::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ref,nom,quantite from materiel");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
    return model;
}

bool Materiel::supprimer(QString ref)
{
QSqlQuery query;
query.prepare("Delete from materiel where ref = :ref ");
query.bindValue(":ref", ref);
return    query.exec();
}
bool Materiel::rech(QString ref){
    QSqlQuery query;
    query.prepare("select * from materiel where ref = :ref");
    query.bindValue(":ref", ref);
    return query.exec();
}
bool Materiel::modifier(QString a1,QString b1,int c1){
    QSqlQuery query;
    query.prepare("update materiel set nom=:nom ,quantite=:quantite   where ref = :ref");
    query.bindValue(":ref", a1);
    query.bindValue(":nom", b1);
    query.bindValue(":quantite", c1);

    return query.exec();
}
QSqlQueryModel * Materiel::recherche(QString data)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select ref,nom,quantite from materiel where ref LIKE '"+data+"%' OR nom LIKE '"+data+"%' OR quantite LIKE '"+data+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
    return  model;
}

QSqlQueryModel * Materiel::trie(int num){
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
        model->setQuery("select ref,nom,quantite from materiel order by ref DESC;");
            break;
        }
        case 2:{
        model->setQuery("select ref,nom,quantite from materiel order by nom DESC;");
            break;
        }
        case 3:{
            model->setQuery("select ref,nom,quantite from materiel order by quantite DESC;");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
    return model;
}

QString Materiel::total() {
    QSqlQuery query;
    query.prepare("select count(*) from materiel");
    query.exec();

    if(query.first())
        return query.value(0).toString();
    else
        return "0";
}
