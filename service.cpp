#include "service.h"

service::service()
{

}
service::service(QString id,QString nom,int nbH,int salaire)
{
    this->id = id;
    this->nom = nom;
    this->nbH = nbH;
    this->salaire = salaire;
}

bool service::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO service (SERVICEID,NOM,NOMBREH,SALAIRE) VALUES (:SERVICEID, :NOM, :NOMBREH, :SALAIRE)");
    query.bindValue(":SERVICEID",id);
    query.bindValue(":NOM",nom);
    query.bindValue(":NOMBREH",nbH);
    query.bindValue(":SALAIRE",salaire);
    return query.exec();
}

QSqlQueryModel * service::trie(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select SERVICEID,NOM,NOMBREH,SALAIRE from service order by SALAIRE DESC;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id "));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nombre de heures "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Salaire "));
    return model;
}

QSqlQueryModel * service::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select SERVICEID,NOM,NOMBREH,SALAIRE from service;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id "));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nombre de heures "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Salaire "));
    return model;
}

QSqlQueryModel * service::recherche(QString id){
  QSqlQueryModel * model = new QSqlQueryModel();
  model->setQuery("select SERVICEID,NOM,NOMBREH,SALAIRE from service where SERVICEID = '"+id+"';");;
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id "));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom "));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nombre de heures "));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Salaire "));
  return model;
}

bool service::supprimer(QString x){
    QSqlQuery query;
    query.prepare("Delete from service where SERVICEID = :SERVICEID;");
    query.bindValue(":SERVICEID",x);
    query.exec();
    return query.exec();
}

bool service::rech(QString x){
    QSqlQuery query;
    query.prepare("select * from service where SERVICEID = :SERVICEID;");
    query.bindValue(":SERVICEID", x);
    query.exec();
    return query.first();
}

bool service::modifier(QString a,QString b,int c,int d){
    QSqlQuery query;
    query.prepare("update service set NOM=:NOM ,NOMBREH=:NOMBREH ,SALAIRE=:SALAIRE where SERVICEID = :SERVICEID;");
    query.bindValue(":SERVICEID", a);
    query.bindValue(":NOM", b);
    query.bindValue(":NOMBREH", c);
    query.bindValue(":SALAIRE", d);
    return query.exec();
}
