#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class login
{
    QString utilisateur,password;
    int type;

public:
    login(QString,QString);
    int getType(){
        return type;
    }
    void setType(int type){
        this->type = type;
    }
    bool seconnect();
    bool checkuser();
};

#endif // LOGIN_H
