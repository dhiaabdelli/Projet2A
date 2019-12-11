#include "medicament.h"
#include <QDebug>
#include<QFile>
#include<QTextDocument>
#include<QTextStream>
Medicament::Medicament()
{
id=0;
nom="";
reference="";
}
Medicament::Medicament(int id,QString nom,QString reference)
{
  this->id=id;
  this->nom=nom;
  this->reference=reference;
}
QString Medicament::get_nom(){return  nom;}
QString Medicament::get_reference(){return reference;}
int Medicament::get_id(){return  id;}

bool Medicament::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO medicament (ID, NOM, REFERENCE) "
                    "VALUES (:id, :nom, :reference)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":reference", reference);

return    query.exec();
}

QSqlQueryModel * Medicament::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from medicament");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
    return model;
}

bool Medicament::supprimer(int idd)
{
QSqlQuery query;
query.prepare("Delete from medicament where ID = :id ");
query.bindValue(":id", idd);
return    query.exec();
}
bool Medicament::rech(int x){
    QSqlQuery query;
    QString res= QString::number(x);
    query.prepare("select * from medicament where id = :id");
    query.bindValue(":id", res);
    query.exec();
    return query.first();
}

bool Medicament::modifier(int a,QString b,QString c)
{
QSqlQuery query;
query.prepare("update Medicament set nom=:nom, reference=:reference where id=:id");
query.bindValue(":id", a);
query.bindValue(":nom", b);
query.bindValue(":reference", c);

return    query.exec();
}

QSqlQueryModel * Medicament::trier()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from medicament order by id");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
    return model;
}
QSqlQueryModel * Medicament ::rechercher(int id)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString res = QString :: number(id);
    model->setQuery("select * from medicament where id='"+res+"'");
    return model;
}
void Medicament::file()
{
    QSqlQuery query;
    QFile myfile("mydata.txt");
    myfile.open(QIODevice::WriteOnly);
    query.prepare("select * from medicament");
    query.exec();
    QString line="";
    QTextStream out(&myfile);
    while (query.next()) {
       line+=query.value(0).toString()+":";
       line+=query.value(1).toString()+":";
       line+=query.value(2).toString()+":";
       qDebug()<<line;
       out<<line;
       line="";
    }
    myfile.close();
}
