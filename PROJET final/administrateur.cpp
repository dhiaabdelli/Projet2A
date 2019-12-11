#include "administrateur.h"
#include "ui_administrateur.h"
#include "adminpersonnel.h"
#include <QSqlQuery>
#include <QMessageBox>

administrateur::administrateur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administrateur)
{
    ui->setupUi(this);
    ui->tabpersonnel->setModel(tmppersonnel.afficher());
    ui->tabservice->setModel(tmpservice.afficher());
    ui->lineEdit_password->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_]{6,32}"), this ));
    ui->lineEdit_nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_utilisateur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_tel->setValidator( new QRegExpValidator( QRegExp("[0-9]{0,8}"),  this));
    QRegExp R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(19[0-9][0-9]|20[0-9][0-9])");
    QRegExpValidator *valida = new QRegExpValidator(R_date, this);
    ui->lineEdit_date->setValidator(valida);
    //ui->lineEdit_date->setPlaceholderText("Example : 21/05/2019");

    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(rx, this));

    QPixmap pixmap(":/conference-128.png");
    QIcon ButtonIcon(pixmap);
    ui->btnPersonnel->setIcon(ButtonIcon);
    ui->btnPersonnel->setIconSize(QSize(24, 24));
    ui->btnPersonnel->setFixedSize(81,81);

    QPixmap pixmap2(":/nurse-128.png");
    QIcon ButtonIcon2(pixmap2);
    ui->btnService->setIcon(ButtonIcon2);
    ui->btnService->setIconSize(QSize(24, 24));
    ui->btnService->setFixedSize(81,81);

    ui->lineEdit_id_3->setValidator(new QRegExpValidator( QRegExp("[0-9]{8,8}"), this ));
    ui->lineEdit_nom_3->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_heure_2->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));
    ui->lineEdit_salaire_3->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));


    ui->lineEdit_nomser->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_nbH->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));
    ui->lineEdit_salaire->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));

    this->load();
    this->stat();
}

administrateur::~administrateur()
{
    delete ui;
}

void administrateur::on_pushButton_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString utilisateur = ui->lineEdit_utilisateur->text();
    int Tel = ui->lineEdit_tel->text().toInt();
    QString email = ui->lineEdit_email->text();
    QString date_na = ui->lineEdit_date->text();
    QString password = ui->lineEdit_password->text();
    QString serviceid = ui->comboBoxserver->currentText();
    adminpersonnel p(nom,prenom,Tel,email,date_na,utilisateur,password,serviceid);
    bool test=p.ajouter();
    if(test){
       ui->tabpersonnel->setModel(tmppersonnel.afficher());
       QMessageBox::information(nullptr,QObject::tr("Personnel ajouter"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
    }else{
       QMessageBox::information(nullptr,QObject::tr("Personnel ajouter"),QObject::tr("Error"),QMessageBox::Cancel);
    }
}


void administrateur::on_lineEdit_nom_textChanged(const QString &arg1)
{

}


void administrateur::on_btnAddP_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void administrateur::on_btnPersonnel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void administrateur::on_btnListP_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void administrateur::on_tabpersonnel_activated(const QModelIndex &index)
{
    QString val=ui->tabpersonnel->model()->data(index).toString();
    ui->InfoPerso->setText(val);
    ui->stackedWidget->setCurrentIndex(3);

    QSqlQuery query;
    query.prepare("select nom,prenom,email,date_nass,tel from personnel where utilisateur= :utilisateur");
    query.bindValue(":utilisateur",val);

    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_nom_2->setText(query.value(0).toString());
            ui->lineEdit_prenom_2->setText(query.value(1).toString());
            ui->lineEdit_Email->setText(query.value(2).toString());
            ui->lineEdit_DateN2->setText(query.value(3).toString());
            ui->lineEdit_tel_2->setText(query.value(4).toString());
         }
     }
}

void administrateur::on_pushButton_6_clicked()
{
    QString id = ui->InfoPerso->text();
    QString nom = ui->lineEdit_nom_2->text();
    QString prenom = ui->lineEdit_prenom_2->text();
    QString email = ui->lineEdit_Email->text();
    QString date = ui->lineEdit_DateN2->text();
    int tel = ui->lineEdit_tel_2->text().toInt();

    adminpersonnel p;
    if(p.rech(id)){
        bool test = p.modifier(id,nom,prenom,email,date,tel);
        if(test){
            ui->tabpersonnel->setModel(tmppersonnel.afficher());
            QMessageBox::information(nullptr,QObject::tr("Personnel modifier"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }
     }else{
            QMessageBox::information(nullptr,QObject::tr("Personnel modifier"),QObject::tr("Error!"),QMessageBox::Cancel);
     }
}

void administrateur::on_pushButton_8_clicked()
{
    adminpersonnel p;
    if(p.rech(ui->InfoPerso->text())){
      bool test=tmppersonnel.supprimer(ui->InfoPerso->text());
      if(test){
            ui->tabpersonnel->setModel(tmppersonnel.afficher());
            ui->stackedWidget->setCurrentIndex(1);
            QMessageBox::critical(nullptr,QObject::tr("Personnel supprimer"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }
     }else{
         ui->stackedWidget->setCurrentIndex(1);
         QMessageBox::information(nullptr,QObject::tr("Personnel supprimer"),QObject::tr("Error!"),QMessageBox::Cancel);
     }
}

void administrateur::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void administrateur::on_btnTrie_clicked()
{
    ui->tabpersonnel->setModel(tmppersonnel.trie());
}

void administrateur::on_btnTriee_clicked()
{
    ui->tabpersonnel->setModel(tmppersonnel.trie());
}

void administrateur::on_pushButton_3_clicked()
{
    QString id = ui->rechId->text();
    ui->tabpersonnel->setModel(tmppersonnel.recherche(id));
}

void administrateur::on_btnreload_clicked()
{
    ui->tabpersonnel->setModel(tmppersonnel.afficher());
}

void administrateur::on_pushButton_7_clicked()
{
     ui->tabpersonnel->setModel(tmppersonnel.afficher());
}

void administrateur::on_pushButton_2_clicked()
{
    QString id = ui->lineEdit_id_3->text();
    QString nom = ui->lineEdit_nom_3->text();
    int heure = ui->lineEdit_heure_2->text().toInt();
    int salaire = ui->lineEdit_salaire_3->text().toInt();
    service s(id,nom,heure,salaire);
    bool test=s.ajouter();
    if(test){
       this->stat();
       this->load();
       ui->tabservice->setModel(tmpservice.afficher());
       QMessageBox::information(nullptr,QObject::tr("Service ajouter"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
    }else{
       QMessageBox::information(nullptr,QObject::tr("Service ajouter"),QObject::tr("Error!"),QMessageBox::Cancel);
    }
}

void administrateur::on_btnService_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void administrateur::on_btnAddP_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void administrateur::on_btnListP_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void administrateur::on_btnreload_2_clicked()
{
    ui->tabservice->setModel(tmpservice.afficher());
}

void administrateur::on_btnTriee_2_clicked()
{
    ui->tabservice->setModel(tmpservice.trie());
}

void administrateur::on_pushButton_4_clicked()
{
    QString id = ui->rechId_2->text();
    ui->tabservice->setModel(tmpservice.recherche(id));
}

void administrateur::on_tabservice_activated(const QModelIndex &index)
{
    QString val=ui->tabservice->model()->data(index).toString();
    ui->InfoServ->setText(val);
    ui->stackedWidget->setCurrentIndex(8);

    QSqlQuery query;
    query.prepare("select NOM,NOMBREH,SALAIRE from service where SERVICEID= :SERVICEID");
    query.bindValue(":SERVICEID",val);

    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_nomser->setText(query.value(0).toString());
            ui->lineEdit_nbH->setText(query.value(1).toString());
            ui->lineEdit_salaire->setText(query.value(2).toString());
         }
     }
}

void administrateur::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void administrateur::on_pushButton_13_clicked()
{
    QString id = ui->InfoServ->text();
    QString nom = ui->lineEdit_nomser->text();
    int nbH = ui->lineEdit_nbH->text().toInt();
    int salaire = ui->lineEdit_salaire->text().toInt();
    service s;
    if(s.rech(id)){
        this->stat();
        bool test = s.modifier(id,nom,nbH,salaire);
        if(test){
            ui->tabservice->setModel(tmpservice.afficher());
            QMessageBox::information(nullptr,QObject::tr("Service modifier"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }
     }else{
            QMessageBox::information(nullptr,QObject::tr("Service modifier"),QObject::tr("Error!"),QMessageBox::Cancel);
     }
}

void administrateur::on_pushButton_12_clicked()
{
    service s;
    if(s.rech(ui->InfoServ->text())){
      bool test=tmpservice.supprimer(ui->InfoServ->text());
      if(test){
            this->load();
            this->stat();
            ui->tabservice->setModel(tmpservice.afficher());
            ui->stackedWidget->setCurrentIndex(7);
            QMessageBox::critical(nullptr,QObject::tr("Service supprimer"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }
     }else{
         ui->stackedWidget->setCurrentIndex(1);
         QMessageBox::information(nullptr,QObject::tr("Service supprimer"),QObject::tr("Error!"),QMessageBox::Cancel);
     }
}

void administrateur::on_btnstat_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void administrateur::load(){
    ui->comboBoxserver->clear();
    QSqlQuery query;
    query.prepare("select SERVICEID,NOM from service");

    if(query.exec())
    {
        while(query.next())
        {
            ui->comboBoxserver->addItem(query.value(0).toString());
         }
     }
}

void administrateur::stat(){
    ui->listWidgetstat->clear();
    QSqlQuery query,query2,query3;
    query.prepare("select SERVICEID,NOM from service");

    if(query.exec())
    {
        query2.prepare("SELECT COUNT(*) FROM personnel");
        if(query2.exec()){
            query2.first();
            while(query.next())
            {
                query3.prepare("SELECT COUNT(*) FROM personnel where SERVICEID = :SERVICEID");
                query3.bindValue(":SERVICEID", query.value(0).toString());
                if(query3.exec()){
                    query3.first();
                    double som = ((query3.value(0).toInt()/(double)query2.value(0).toInt())*100);
                    QString per = QString::number(som);
                    QString num1 = QString::number(query2.value(0).toInt());
                    QString num2 = QString::number(query3.value(0).toInt());
                    ui->listWidgetstat->addItem(query.value(1).toString() + " = "+per+"%");
                }
             }
        }
     }
}
