#include "para.h"
#include <QDebug>
Para::Para()
{
Ref="";
Type="";
}
Para::Para(QString Ref,QString Type)
{
  this->Ref=Ref;
  this->Type=Type;
}
bool Para::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO para (REF,TYPE) VALUES (:Ref,:Type)");
    query.bindValue(":Ref",Ref );
    query.bindValue(":Type", Type);
    return    query.exec();
}

QSqlQueryModel * Para::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select ref,type from para");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    return model;
}

bool Para::modifier(QString e, QString f)
{
QSqlQuery query;
query.prepare("update para set Type=:Type where Ref=:Ref");
query.bindValue(":Ref", e);
query.bindValue(":Type", f);

return    query.exec();
}
bool Para::supprimer(QString Ref)
{
QSqlQuery query;
query.prepare("Delete from para where Ref = :Ref ");
query.bindValue(":Ref", Ref);
return    query.exec();
}
bool Para::rech(QString Ref){
    QSqlQuery query;
    query.prepare("select * from para where Ref = :Ref");
    query.bindValue(":Ref", Ref);
    query.exec();
    return query.first();
}
QSqlQueryModel * Para::trier(int num)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
            model->setQuery("select ref,type from para order by ref DESC;");
            break;
        }
        case 2:{
            model->setQuery("select ref,type from para order by type DESC;");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    return model;
}
QSqlQueryModel * Para ::rechercher(QString data)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select ref,type from para where ref LIKE '"+data+"%' OR type LIKE '"+data+"%';");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type "));
    return model;
}
