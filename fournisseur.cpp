#include "fournisseur.h"
#include <QDebug>
Fournisseur::Fournisseur()
{
    id="";
    nom="";
    tel=0;
    address = "";
    ville = "";
    code_p = "";
}
Fournisseur::Fournisseur(QString id,QString nom,QString address,long tel,QString ville,QString code_p)
{
  this->id=id;
  this->nom=nom;
  this->address=address;
  this->tel = tel;
  this->ville = ville;
  this->code_p = code_p;
}

QString Fournisseur::get_id(){return  id;}

bool Fournisseur::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO fournisseur (id,nom,address,tel,ville,code_p) VALUES (:id, :nom, :address, :tel, :ville, :code_p)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":address",address);
    query.bindValue(":tel",QString::number(tel));
    query.bindValue(":ville",ville);
    query.bindValue(":code_p",code_p);
    return query.exec();
}

QSqlQueryModel * Fournisseur::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select id,nom,address,tel,ville,code_p from fournisseur");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Ville "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Code Postal"));
    return model;
}

bool Fournisseur::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("Delete from fournisseur where ID = :id ");
    query.bindValue(":id", id);
    return  query.exec();
}
bool Fournisseur::rech(QString id){
    QSqlQuery query;

    query.prepare("select * from fournisseur where ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}
bool Fournisseur::modifier(QString id,QString nom,QString address,long tel,QString ville,QString code_p){
    QSqlQuery query;
    query.prepare("update fournisseur set nom=:nom ,prenom=:prenom   where id = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":tel", QString::number(tel));

    return query.exec();
}
QSqlQueryModel * Fournisseur::recherche(QString data)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select id,nom,address,tel,ville,code_p from fournisseur where id LIKE '"+data+"%' OR nom LIKE '"+data+"%' OR address LIKE '"+data+"%' OR tel LIKE '"+data+"%' OR ville LIKE '"+data+"%' OR code_p LIKE '"+data+"%';");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Ville "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Code Postal"));
    return model;
}
