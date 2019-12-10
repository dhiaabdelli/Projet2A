#include "patient.h"
#include<QSqlQuery>
#include<QString>
#include<QVariant>

patient::patient()
{
    cin="";
    tel="";
    nom="";
    prenom="";
    email="";
}

patient::patient(QString cin,QString tel,QString nom,QString prenom,QString email)
{
    this->cin=cin;
    this->tel=tel;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
}

bool patient::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO patient (cin,tel, nom, prenom, email) "
                        "VALUES (:cin, :tel, :nom, :prenom, :email)");
          query.bindValue(":cin", cin);
          query.bindValue(":tel", tel);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":email", email);
          return  query.exec();
}

QSqlQueryModel * patient::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select cin,nom,prenom,tel,email from patient");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    return model;
}

QSqlQueryModel * patient::recherche(QString data)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select cin,nom,prenom,tel,email from patient where cin LIKE '"+data+"%' OR nom LIKE '"+data+"%' OR prenom LIKE '"+data+"%' OR tel LIKE '"+data+"%' OR email LIKE '"+data+"%';");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    return model;
}

bool patient::supprimer(QString cin)
{

    QSqlQuery query;
    query.prepare("Delete from patient where cin = :cin ");
    query.bindValue(":cin", cin);
    return query.exec();
}

QSqlQueryModel * patient::trie(int num){
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
            model->setQuery("select cin,nom,prenom,tel,email from patient order by cin DESC;");
            break;
        }
        case 2:{
            model->setQuery("select cin,nom,prenom,tel,email from patient order by nom DESC;");
            break;
        }
        case 3:{
            model->setQuery("select cin,nom,prenom,tel,email from patient order by prenom DESC;");
            break;
        }
        case 4:{
            model->setQuery("select cin,nom,prenom,tel,email from patient order by tel DESC;");
            break;
        }
        case 5:{
            model->setQuery("select cin,nom,prenom,tel,email from patient order by email DESC;");
            break;
        }
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    return model;
}


bool patient::modifier(QString cin,QString nom,QString prenom,QString tel,QString email){
    QSqlQuery query;
    query.prepare("update patient set tel=:tel ,nom=:nom ,prenom=:prenom, email=:email  where cin = :cin");
    query.bindValue(":cin", cin);
    query.bindValue(":tel", tel);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    return query.exec();
}

bool patient::rech(QString cin){
    QSqlQuery query;
    query.prepare("select * from patient where cin = :cin");
    query.bindValue(":cin", cin);
    return query.exec();
}


QString patient::total() {
    QSqlQuery query;
    query.prepare("select count(*) from patient");
    query.exec();

    if(query.first())
        return query.value(0).toString();
    else
        return "0";
}
