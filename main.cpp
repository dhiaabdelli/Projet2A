#include "mainwindow.h"
#include <QApplication>
#include "db.h"
#include <QtDebug>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DB db;
    try {
        db.ConnectDB();
        w.show();
    } catch (QString s) {
        qDebug()<<s;
    }

    return a.exec();
}
