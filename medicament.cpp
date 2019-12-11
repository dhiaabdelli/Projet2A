#include "medicament.h"
#include <QDebug>
#include<QFile>
#include<QTextDocument>
#include<QTextStream>
Medicament::Medicament()
{
    ref="";
    nom="";
    idfour="";
}
Medicament::Medicament(QString ref,QString nom,QString idfour)
{
  this->ref=ref;
  this->nom=nom;
  this->idfour=idfour;
}

bool Medicament::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO medicament (ref, NOM, idfour) "
                        "VALUES (:ref, :nom, :idfour)");
    query.bindValue(":ref", ref);
    query.bindValue(":nom", nom);
    query.bindValue(":idfour", idfour);

    return    query.exec();
}

QSqlQueryModel * Medicament::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select ref,nom,idfour from medicament;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID Fournisseur"));
    return model;
}

bool Medicament::supprimer(QString ref)
{
    QSqlQuery query;
    query.prepare("Delete from medicament where ref = :ref ");
    query.bindValue(":ref", ref);
    return    query.exec();
}
bool Medicament::rech(QString ref){
    QSqlQuery query;
    query.prepare("select * from medicament where ref = :ref");
    query.bindValue(":ref", ref);
    query.exec();
    return query.first();
}

bool Medicament::modifier(QString a,QString b,QString c)
{
QSqlQuery query;
query.prepare("update Medicament set nom=:nom, idfour=:idfour where ref=:ref");
query.bindValue(":ref", a);
query.bindValue(":nom", b);
query.bindValue(":idfour", c);

return    query.exec();
}

QSqlQueryModel * Medicament::trie(int num){
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
        model->setQuery("select ref,nom,ifour from materiel order by ref DESC;");
            break;
        }
        case 2:{
            model->setQuery("select ref,nom,ifour from materiel order by nom DESC;");
            break;
        }
        case 3:{
            model->setQuery("select ref,nom,ifour from materiel order by ifour DESC;");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID Fournisseur"));
    return model;
}


QSqlQueryModel * Medicament::recherche(QString data)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select ref,nom,idfour from medicament where ref LIKE '"+data+"%' OR nom LIKE '"+data+"%' OR idfour LIKE '"+data+"%';");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID Fournisseur"));
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
