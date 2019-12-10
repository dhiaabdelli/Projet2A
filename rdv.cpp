#include "rdv.h"
#include <QDebug>
#include <QString>

RDV::RDV()
{
    id="";
    cin="";
    date="";
}

RDV::RDV(QString id,QString cin,QString date)
{
    this->id=id;
    this->cin=cin;
    this->date=date;
}

bool RDV::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Rendezvous (id, cin, date_rdv) "
                        "VALUES (:id, :cin, :date_rdv)");
    query.bindValue(":id", id);
    query.bindValue(":cin", cin);
    query.bindValue(":date_rdv", date);

    return    query.exec();
}

QSqlQueryModel * RDV::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id,cin,date_rdv from Rendezvous order by date_rdv DESC;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    return model;
}

bool RDV::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("Delete from Rendezvous where ID = :id ");
    query.bindValue(":id", id);
    return query.exec();
}

bool RDV::rech(QString id){
    QSqlQuery query;
    query.prepare("select * from Rendezvous where id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool RDV::modifier(QString a,QString b,QString c){
    QSqlQuery query;
    query.prepare("update Rendezvous set date_rdv=:date_rdv  where id = :id and cin = :cin;");
    query.bindValue(":id", a);
    query.bindValue(":cin", b);
    query.bindValue(":date_rdv", c);

    return query.exec();
}

QSqlQueryModel * RDV::recherche(QString data)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select id,cin,date_rdv from Rendezvous where id LIKE '"+data+"%' OR cin LIKE '"+data+"%' OR date_rdv LIKE '"+data+"%';");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    return  model;
}

QSqlQueryModel * RDV::trie(int num){
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
            model->setQuery("select id,cin,date_rdv from Rendezvous order by id DESC;");
            break;
        }
        case 2:{
            model->setQuery("select id,cin,date_rdv from Rendezvous order by cin DESC;");
            break;
        }
        case 3:{
            model->setQuery("select id,cin,date_rdv from Rendezvous order by date_rdv DESC;");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    return model;
}


QString RDV::total() {
    QSqlQuery query;
    query.prepare("select count(*) from Rendezvous");
    query.exec();

    if(query.first())
        return query.value(0).toString();
    else
        return "0";
}
