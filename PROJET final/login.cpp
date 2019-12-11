#include "login.h"
#include <QSqlError>

login::login()
{
    this->utilisateur = "";
    this->password = "";
    this->nom = "";
}
login::login(QString utilisateur,QString password)
{
    this->utilisateur = utilisateur;
    this->password = password;
}
login::login(QString utilisateur,QString password,QString nom)
{
    this->utilisateur = utilisateur;
    this->password = password;
    this->nom = nom;
}


bool login::seconnect(){
    QSqlQuery query;
    query.prepare("SELECT type,nom FROM personnel WHERE utilisateur = :utilisateur AND password = :password;");
    query.bindValue(":utilisateur",utilisateur);
    query.bindValue(":password",password);
    query.exec();
    if(query.first()) {
        login::setType(query.value(0).toInt());
        login::setNom(query.value(1).toString());
        return true;
    }else{
        return false;
    }
}

bool login::checkuser(){
    QSqlQuery query;
    query.prepare("SELECT type FROM personnel WHERE utilisateur = :utilisateur;");
    query.bindValue(":utilisateur",utilisateur);
    query.exec();
    return query.first();
};
