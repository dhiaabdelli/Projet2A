#include "convention.h"
#include<QSqlQuery>
#include<QString>
#include<QDate>
#include<QVariant>


convention::convention()
{
    code=0;

}


convention::convention(int code,int cin,QDate date_creation)
{
    this->code=code;
    this->cin=cin;
    this->date_creation=date_creation;
}

bool convention::ajouter_convention()
{
    QSqlQuery query;
    QString res=QString::number(code);
    QString res1=QString::number(cin);

          query.prepare("INSERT INTO convention (code,cin,date_creation) "
                        "VALUES (:code,:cin, :date_creation)");
          query.bindValue(":code", res);
          query.bindValue(":cin", res1);
          query.bindValue(":date_creation", date_creation);


          return  query.exec();
}

QSqlQueryModel * convention::afficher_convention()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from convention");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Cin "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date_Creation "));
    return model;
}

bool convention::supprimer_convention(int code1)
{
QSqlQuery query;
QString res= QString::number(code1);
query.prepare("Delete from convention where code = :code ");
query.bindValue(":code", res);
return    query.exec();
}

bool convention::rech(int code){
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("select * from convention where code = :code");
    query.bindValue(":code", res);
    return query.exec();
}

bool convention::modifier(int code,QDate date_creation){
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("update convention set date_creation=:date_creation where code = :code");
    query.bindValue(":code", res);
    query.bindValue(":date_creation", date_creation);
    return query.exec();
}


QSqlQueryModel * convention::trierconvention_code()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from convention ORDER BY Code");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_Creation"));
        return model;
}



QSqlQueryModel * convention::afficher_convention_ch(int code)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString res=QString::number(code);
    model->setQuery("select Code,Cin,Date_Creation from convention WHERE regexp_like(Code,:code)");
    query.bindValue(":code", res);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_Creation"));
        return model;
}

/*bool convention::rech_convention(int code){
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("select * from convention where regexp_like(Code,:code)");
    query.bindValue(":code", res);

    return query.exec();
}*/
QSqlQueryModel * convention::Rechercher(long code)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString res=QString::number(code);
    model->setQuery("select * from convention where (code LIKE '"+res+"%' ) ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date de convetion"));

            return  model;


}

