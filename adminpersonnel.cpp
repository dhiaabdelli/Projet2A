#include "adminpersonnel.h"

adminpersonnel::adminpersonnel()
{

}
adminpersonnel::adminpersonnel(QString nom,QString prenom,int tel,QString email,QString date_nass,QString utilisateur,QString password,QString serviceid)
{
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->date_nass = date_nass;
    this->utilisateur = utilisateur;
    this->password = password;
    this->tel = tel;
    this->serviceid = serviceid;
}

bool adminpersonnel::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO personnel (utilisateur,password,nom,prenom,date_nass,tel,email,SERVICEID) VALUES (:utilisateur, :password, :nom, :prenom, :date_nass, :tel, :email, :SERVICEID);");
    query.bindValue(":utilisateur",utilisateur);
    query.bindValue(":password",password);
    query.bindValue(":date_nass",date_nass);
    query.bindValue(":tel",tel);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":SERVICEID",serviceid);
    return query.exec();
}

QSqlQueryModel * adminpersonnel::trie(int num){
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(num){
        case 1:{
            model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel order by utilisateur;");
            break;
        }
        case 2:{
            model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel order by nom;");
            break;
        }
        case 3:{
            model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel order by prenom;");
            break;
        }
        case 4:{
            model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel order by email;");
            break;
        }
        case 5:{
            model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel order by date_nass;");
            break;
        }
        case 6:{
            model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel order by tel;");
            break;
        }
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant "));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date de naissance "));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Tel "));
    return model;
}

QSqlQueryModel * adminpersonnel::afficher(){
  QSqlQueryModel * model = new QSqlQueryModel();
  model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant "));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom "));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom "));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email "));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date de naissance "));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Tel "));
  return model;
}

QSqlQueryModel * adminpersonnel::recherche(QString data){
  QSqlQueryModel * model = new QSqlQueryModel();
  model->setQuery("select utilisateur,nom,prenom,email,date_nass,tel from personnel where utilisateur LIKE '"+data+"%' OR nom LIKE '"+data+"%' OR prenom LIKE '"+data+"%' OR email LIKE '"+data+"%' OR date_nass LIKE '"+data+"%' OR tel LIKE '"+data+"%';");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant "));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom "));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom "));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email "));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date de naissance "));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Tel "));
  return model;
}

bool adminpersonnel::supprimer(QString x){
    QSqlQuery query;
    query.prepare("Delete from personnel where utilisateur = :utilisateur;");
    query.bindValue(":utilisateur",x);
    query.exec();
    return query.exec();
}

bool adminpersonnel::rech(QString x){
    QSqlQuery query;
    query.prepare("select * from personnel where utilisateur = :utilisateur;");
    query.bindValue(":utilisateur", x);
    query.exec();
    return query.first();
}

bool adminpersonnel::modifier(QString a,QString b,QString c,QString d,QString e,int f,QString g){
    QSqlQuery query;
    query.prepare("update personnel set nom=:nom ,prenom=:prenom ,email=:email ,date_nass=:date_nass ,tel=:tel,password=:password where utilisateur = :utilisateur;");
    query.bindValue(":utilisateur", a);
    query.bindValue(":nom", b);
    query.bindValue(":prenom", c);
    query.bindValue(":email", d);
    query.bindValue(":date_nass", e);
    query.bindValue(":tel", f);
    query.bindValue(":password", g);
    return query.exec();
}

QString adminpersonnel::total() {
    QSqlQuery query;
    query.prepare("select count(*) from personnel");
    query.exec();

    if(query.first())
        return query.value(0).toString();
    else
        return "0";
}
