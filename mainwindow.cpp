#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QSqlQuery>
#include "login.h"
#include <QRegExpValidator>
#include "administrateur.h"
#include "personnel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    QPixmap pix(":/conference-128.png");
    int w = ui->login->width();
    int h = ui->login->height();
    ui->login->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->lineEdit_password->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_]{6,32}"), this ));
    ui->lineEdit_utilisateur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
        QString utilisateur = ui->lineEdit_utilisateur->text();
        QString password = ui->lineEdit_password->text();
        login login(utilisateur,password);
        bool test=login.seconnect();
        if(test){

            this->hide();
            switch(login.getType()){
            case 0:{
                personnel personnel;
                personnel.setModal(true);
                personnel.exec();
                break;
            }
            case 1:{
                administrateur administrateur;
                administrateur.setModal(true);
                administrateur.exec();
                break;
                }
            }
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
