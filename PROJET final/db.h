#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class DB
{
    QSqlDatabase db;
public:
    DB();
    bool ConnectDB();
    void CloseDB();
};

#endif // DB_H
