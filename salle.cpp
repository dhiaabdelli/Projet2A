#include "salle.h"
#include <QDebug>
#include <QString>

salle::salle()
{
   num=0;
   bloc="";
}
salle::salle(int num,QString bloc)
{
    this->num=num;
    this->bloc=bloc;
}
int salle::get_num(){return  num;}
QString salle::get_bloc(){return bloc;}

bool salle::ajouter()
{
QSqlQuery query;
QString res= QString::number(num);
query.prepare("INSERT INTO salle (num,bloc) "
                    "VALUES (:num, :bloc)");
query.bindValue(":num", res);
query.bindValue(":bloc", bloc);

return    query.exec();
}

QSqlQueryModel * salle::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select num,bloc from salle");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Bloc"));
    return model;
}

bool salle::supprimer(int numm)
{
QSqlQuery query;
QString res= QString::number(numm);
query.prepare("Delete from salle where NUM = :num ");
query.bindValue(":num", res);
return    query.exec();
}

bool salle::rech(int x){
    QSqlQuery query;
    QString res= QString::number(x);

    query.prepare("select * from salle where num = :num");
    query.bindValue(":num", res);
    return query.exec();
}

bool salle::modifier(int a,QString b)
{
    QSqlQuery query;
    query.prepare("update salle set bloc=:bloc  where num = :num");
    query.bindValue(":num", a);
    query.bindValue(":bloc", b);
    return query.exec();
}

QSqlQueryModel * salle::Rechercher(long num)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString res=QString::number(num);
    model->setQuery("select num,bloc from salle where num LIKE '"+res+"%' or bloc LIKE '"+res+"%'");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Bloc"));

            return  model;
}

QSqlQueryModel * salle::trie(int num)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    switch(num){
        case 1:{
        model->setQuery("select num,bloc from salle order by num DESC;");
            break;
        }
        case 2:{
        model->setQuery("select num,bloc from salle order by bloc DESC");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Bloc"));
    return model;
}
