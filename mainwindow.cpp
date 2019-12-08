#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QSqlQuery>
#include "login.h"
#include <QRegExpValidator>
#include "interface.h"
#include "mailing/SmtpMime"
#include <QtWidgets>
#include <QtNetwork>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->lineEdit_password->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_]{6,32}"), this ));
    ui->lineEdit_utilisateur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if (reply->bytesAvailable())
        QMessageBox::information(this, "Info", "You are connected to the internet :)");
    else
        QMessageBox::critical(this, "Info", "You are not connected to the internet :(");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
        QString utilisateur = ui->lineEdit_utilisateur->text();
        QString password = ui->lineEdit_password->text();
        login login(utilisateur,password,"");
        bool test=login.seconnect();
        if(test){
            this->hide();
            Interface interface(this,login.getType(),login.getNom());
            interface.setModal(true);
            interface.exec();
            password = "";
            ui->lineEdit_password->setText("");
            //QMessageBox::information(nullptr,QObject::tr("Personnel ajouter"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }else{
            ui->info->setStyleSheet( "QLabel { font-size: 9pt; color : red; }" );
            if(login.checkuser()){
                ui->info->setText("Erreur : Vous avez entre un mot de passe incorrect");
                ui->lineEdit_utilisateur->setStyleSheet( "QLineEdit{ border: 1px solid #414561;}QLineEdit:focus { border: 1px solid #828dff;}QLineEdit:hover{ border: 1px solid #828dff;}" );
            }else{
                ui->info->setText("Erreur : Vous avez entre un nom d'utulisateur incorrect");
                ui->lineEdit_utilisateur->setStyleSheet( "QLineEdit{ border-width: 1px; border-style: solid; border-color: red; }QLineEdit:focus { border: 1px solid #828dff;}" );
            }
            ui->lineEdit_password->setStyleSheet( "QLineEdit{ border-width: 1px; border-style: solid; border-color: red; }QLineEdit:focus { border: 1px solid #828dff;}" );
            //QMessageBox::information(nullptr,QObject::tr("Personnel ajouter"),QObject::tr("Error!"),QMessageBox::Cancel);
        }
}
