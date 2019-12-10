#include "convention.h"

#include <QDebug>
convention::convention()
{
    id="";
    idfour="";
    date_d="";
    date_f="";
    des="";
}
convention::convention(QString id,QString idfour,QString date_d,QString date_f,QString des)
{
  this->id=id;
  this->idfour=idfour;
  this->date_d=date_d;
  this->date_f=date_f;
  this->des=des;
}

bool convention::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO convention (id, idfour, date_d, date_f, des) "
                        "VALUES (:id, :idfour, :date_d, :date_f, :des);");
    query.bindValue(":id", id);
    query.bindValue(":idfour", idfour);
    query.bindValue(":date_d", date_d);
    query.bindValue(":date_f", date_f);
    query.bindValue(":des", des);

    return query.exec();
}

QSqlQueryModel * convention::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id,idfour,date_d,date_f,des from convention");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID Fournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date de fin "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
    return model;
}

bool convention::supprimer(QString ref)
{
QSqlQuery query;
query.prepare("Delete from convention where ref = :ref ");
query.bindValue(":ref", ref);
return    query.exec();
}
bool convention::rech(QString ref){
    QSqlQuery query;
    query.prepare("select * from convention where ref = :ref");
    query.bindValue(":ref", ref);
    return query.exec();
}
bool convention::modifier(QString id,QString idfour,QString date_d,QString date_f,QString des){
    QSqlQuery query;
    query.prepare("update convention set date_d=:date_d ,date_d=:date_d, des=:des   where id = :id and idfour = :idfour;");
    query.bindValue(":id", id);
    query.bindValue(":idfour", idfour);
    query.bindValue(":date_d", date_d);
    query.bindValue(":date_f", date_f);
    query.bindValue(":des", des);
    return query.exec();
}
QSqlQueryModel * convention::recherche(QString data)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select id,idfour,date_d,date_f,des from convention where id LIKE '"+data+"%' OR idfour LIKE '"+data+"%' OR date_d LIKE '"+data+"%' OR date_f LIKE '"+data+"%' OR des LIKE '"+data+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID Fournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date de fin "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
    return  model;
}

QSqlQueryModel * convention::trie(int num){
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
            model->setQuery("select id,idfour,date_d,date_f,des from convention order by id DESC;");
            break;
        }
        case 2:{
            model->setQuery("select id,idfour,date_d,date_f,des from convention order by idfour DESC;");
            break;
        }
        case 3:{
            model->setQuery("select id,idfour,date_d,date_f,des from convention order by date_d DESC;");
            break;
        }
        case 4:{
            model->setQuery("select id,idfour,date_d,date_f,des from convention order by date_f DESC;");
            break;
        }
        case 5:{
            model->setQuery("select id,idfour,date_d,date_f,des from convention order by des DESC;");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID Fournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date de fin "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
    return model;
}

QString convention::total() {
    QSqlQuery query;
    query.prepare("select count(*) from convention");
    query.exec();

    if(query.first())
        return query.value(0).toString();
    else
        return "0";
}
