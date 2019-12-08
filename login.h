#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class login
{
    QString utilisateur,password,nom;
    int type;

public:
    login(QString,QString,QString);
    login();
    login(QString,QString);
    int getType(){
        return type;
    }
    QString getNom(){
        return nom;
    }
    void setType(int type){
        this->type = type;
    }
    void setNom(QString nom){
        this->nom = nom;
    }
    bool seconnect();
    bool checkuser();
};

#endif // LOGIN_H
