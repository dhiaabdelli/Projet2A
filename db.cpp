#include "db.h"

DB::DB()
{

}
bool DB::ConnectDB(){
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("dhia");//inserer nom de l'utilisateur
    db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;
    else
        throw QString("Unable to connect to db");

      return  test;
}
void DB::CloseDB(){
    db.close();
}
