#include "para.h"
#include <QDebug>
Para::Para()
{
Serial=0;
Ref="";
Type="";
}
Para::Para(int Serial,QString Ref,QString Type)
{
  this->Serial=Serial;
  this->Ref=Ref;
  this->Type=Type;
}
QString Para::get_Ref(){return  Ref;}
QString Para::get_Type(){return Type;}
int Para::get_Serial(){return  Serial;}

bool Para::ajouter_para()
{
    QSqlQuery query;
    QString res= QString::number(Serial);
    query.prepare("INSERT INTO para (SERIAL,REF,TYPE) VALUES (:Serial,:Ref,:Type)");
    query.bindValue(":Serial", res);
    query.bindValue(":Ref",Ref );
    query.bindValue(":Type", Type);
    return    query.exec();
}

QSqlQueryModel * Para::afficher_para()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from para");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("SERIAL"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    return model;
}

bool Para::modifier_para(int d, QString e, QString f)
{
QSqlQuery query;
query.prepare("update para set Type=:Type, Ref=:Ref where Serial=:Serial");
query.bindValue(":Serial", d);
query.bindValue(":Ref", e);
query.bindValue(":Type", f);

return    query.exec();
}
bool Para::supprimer_para(int seriall)
{
QSqlQuery query;
query.prepare("Delete from para where SERIAL = :Serial ");
query.bindValue(":Serial", seriall);
return    query.exec();
}
bool Para::rech_para(int y){
    QSqlQuery query;
    QString res= QString::number(y);
    query.prepare("select * from para where Serial = :Serial");
    query.bindValue(":Serial", res);
    query.exec();
    return query.first();
}
QSqlQueryModel * Para::trier()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from para order by Serial");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Serial"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    return model;
}
QSqlQueryModel * Para ::rechercher(int Serial)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString res = QString :: number(Serial);
    model->setQuery("select * from medicament where Serial='"+res+"'");
    return model;
}

