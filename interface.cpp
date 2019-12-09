#include "interface.h"
#include "ui_interface.h"
#include "adminpersonnel.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QTcpSocket>

Interface::Interface(QWidget* parent,int type,QString nom) :
    QDialog(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    this->parent = parent;
    if(type != 1){
        ui->btnAdmin->hide();
        ui->btnService->setEnabled(false);
    }
    ui->username->setText("Hi, "+nom);
    btncurrent = nullptr;
    this->setbtnEnable(ui->btnHome,btncurrent,"Home");
    ui->tabpersonnel->setModel(tmppersonnel.afficher());
    ui->tabservice->setModel(tmpservice.afficher());
    ui->tabFournisseur->setModel(tmpfournisseur.afficher());
    ui->tabMaterial->setModel(tmpMaterial.afficher());

    ui->tabpersonnel->verticalHeader()->setVisible(false);
    ui->tabpersonnel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabpersonnel->setAlternatingRowColors(true);
    ui->tabpersonnel->setShowGrid(false);
    ui->tabpersonnel->verticalHeader()->setSectionsClickable(true);
    ui->tabpersonnel->horizontalHeader()->setSectionsClickable(true);

    ui->tabservice->verticalHeader()->setVisible(false);
    ui->tabservice->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabservice->setAlternatingRowColors(true);
    ui->tabservice->setShowGrid(false);
    ui->tabservice->verticalHeader()->setSectionsClickable(true);
    ui->tabservice->horizontalHeader()->setSectionsClickable(true);

    ui->tabFournisseur->verticalHeader()->setVisible(false);
    ui->tabFournisseur->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabFournisseur->setAlternatingRowColors(true);
    ui->tabFournisseur->setShowGrid(false);
    ui->tabFournisseur->verticalHeader()->setSectionsClickable(true);
    ui->tabFournisseur->horizontalHeader()->setSectionsClickable(true);


    ui->tabMaterial->verticalHeader()->setVisible(false);
    ui->tabMaterial->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabMaterial->setAlternatingRowColors(true);
    ui->tabMaterial->setShowGrid(false);
    ui->tabMaterial->verticalHeader()->setSectionsClickable(true);
    ui->tabMaterial->horizontalHeader()->setSectionsClickable(true);

    adminpersonnel p;
    ui->personnelTotal->setText(p.total());
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

    ui->lineEdit_id_3->setValidator(new QRegExpValidator( QRegExp("[0-9]{8,8}"), this ));
    ui->lineEdit_nom_3->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_heure_2->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));
    ui->lineEdit_salaire_3->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));


    ui->lineEdit_nomser->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]{0,32}"), this ));
    ui->lineEdit_nbH->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));
    ui->lineEdit_salaire->setValidator( new QRegExpValidator( QRegExp("[0-9]{8,8}"),  this));




    QPixmap pixmap(":/icons/menu/admin/plus.png");
    QIcon ButtonIcon(pixmap);
    ui->btnAddService->setIcon(ButtonIcon);
    ui->btnAddService->setIconSize(QSize(16, 16));

    connect(ui->tabpersonnel->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clicked(int)));
    connect(ui->tabpersonnel->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clicked(int)));

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected(nom)), this, SLOT(connected(nom)));
    socket->connectToHost("127.0.0.1", 4200);
    this->load();
}

// This function gets called when our socket has successfully connected to the chat
// server. (see the connect() call in the MainWindow constructor).
void Interface::connected(QString nom)
{
    // And send our username to the chat server.
    socket->write(QString("/me:" + nom + "\n").toUtf8());
}

// This function gets called whenever the chat server has sent us some text:
void Interface::readyRead()
{
    // We'll loop over every (complete) line of text that the server has sent us:
    while(socket->canReadLine())
    {
        // Here's the line the of text the server sent us (we use UTF-8 so
        // that non-English speakers can chat in their native language)
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        // These two regular expressions describe the kinds of messages
        // the server can send us:

        //  Normal messges look like this: "username:The message"
        QRegExp messageRegex("^([^:]+):(.*)$");

        // Any message that starts with "/users:" is the server sending us a
        // list of users so we can show that list in our GUI:
        QRegExp usersRegex("^/users:(.*)$");

        // Is this a users message:
        if(usersRegex.indexIn(line) != -1)
        {
            // If so, udpate our users list on the right:
            QStringList users = usersRegex.cap(1).split(",");
            ui->listWidget->clear();
            foreach(QString user, users)
                new QListWidgetItem(QPixmap(":/user.png"), user, ui->listWidget);
        }
        // Is this a normal chat message:
        else if(messageRegex.indexIn(line) != -1)
        {
            // If so, append this message to our chat box:
            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);

            //roomTextEdit->append("<b>" + user + "</b>: " + message);
        }
    }
}

void Interface::slot_table_clicked(int num){
    switch(num){
        case 0:{
            ui->tabpersonnel->setModel(tmppersonnel.trie(1));
            break;
        }
        case 1:{
            ui->tabpersonnel->setModel(tmppersonnel.trie(2));
            break;
        }
        case 2:{
            ui->tabpersonnel->setModel(tmppersonnel.trie(3));
            break;
        }
        case 3:{
            ui->tabpersonnel->setModel(tmppersonnel.trie(4));
            break;
        }
        case 4:{
            ui->tabpersonnel->setModel(tmppersonnel.trie(5));
            break;
        }
        case 5:{
            ui->tabpersonnel->setModel(tmppersonnel.trie(6));
            break;
        }
    }
}

Interface::~Interface()
{
    delete ui;
}

void Interface::setbtnEnable(QPushButton* btn,QPushButton* &btnnew,QString title){
    if(btnnew != nullptr){
       btnnew->setStyleSheet("");
    }
    ui->PageTitle->setText(title);
    btnnew = btn;
    btnnew->setStyleSheet("QPushButton{border-right: 3px solid #1395ff;background-color: #2e3657;}");
}



void Interface::on_pushButton_2_clicked()
{
    QString id = ui->lineEdit_id_3->text();
    QString nom = ui->lineEdit_nom_3->text();
    int heure = ui->lineEdit_heure_2->text().toInt();
    int salaire = ui->lineEdit_salaire_3->text().toInt();
    service s(id,nom,heure,salaire);
    bool test=s.ajouter();
    if(test){
       this->load();
       ui->tabservice->setModel(tmpservice.afficher());
       QMessageBox::information(nullptr,QObject::tr("Service ajouter"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
    }else{
       QMessageBox::information(nullptr,QObject::tr("Service ajouter"),QObject::tr("Error!"),QMessageBox::Cancel);
    }
}



void Interface::on_pushButton_13_clicked()
{
    QString id = ui->InfoServ->text();
    QString nom = ui->lineEdit_nomser->text();
    int nbH = ui->lineEdit_nbH->text().toInt();
    int salaire = ui->lineEdit_salaire->text().toInt();
    service s;
    if(s.rech(id)){
        bool test = s.modifier(id,nom,nbH,salaire);
        if(test){
            ui->tabservice->setModel(tmpservice.afficher());
            QMessageBox::information(nullptr,QObject::tr("Service modifier"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }
     }else{
            QMessageBox::information(nullptr,QObject::tr("Service modifier"),QObject::tr("Error!"),QMessageBox::Cancel);
     }
}


void Interface::load(){
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





void Interface::on_btnAdmin_clicked()
{
    this->setbtnEnable(ui->btnAdmin,btncurrent,"Administration");
    ui->NavigationW->setCurrentIndex(2);
}

void Interface::on_btnHome_clicked()
{
    this->setbtnEnable(ui->btnHome,btncurrent,"Home");
    ui->NavigationW->setCurrentIndex(0);
    ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_btnChat_clicked()
{
    this->setbtnEnable(ui->btnChat,btncurrent,"Chat");
    ui->NavigationW->setCurrentIndex(1);
}

void Interface::on_btnPersonnel_2_clicked()
{
    this->hide();
    parent->show();
}

void Interface::on_lineEdit_2_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabpersonnel->setModel(tmppersonnel.afficher());
    }else{
        ui->tabpersonnel->setModel(tmppersonnel.recherche(arg1));
    }
}

void Interface::on_pushButton_14_clicked()
{
    ui->personneltabs->setCurrentIndex(1);
}


void Interface::on_pushButton_clicked()
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
        adminpersonnel p;
        ui->personnelTotal->setText(p.total());
        ui->personneltabs->setCurrentIndex(0);
    }
}


void Interface::on_pushButton_15_clicked()
{
    ui->personneltabs->setCurrentIndex(0);
}

void Interface::on_tabpersonnel_activated(const QModelIndex &index)
{
    QString val=ui->tabpersonnel->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select nom,prenom,email,date_nass,tel,password from personnel where utilisateur= :utilisateur");
    query.bindValue(":utilisateur",val);

    if(query.exec())
    {
        if(query.first())
        {
            ui->lineEdit_nom_2->setText(query.value(0).toString());
            ui->lineEdit_prenom_2->setText(query.value(1).toString());
            ui->lineEdit_Email->setText(query.value(2).toString());
            ui->lineEdit_DateN2->setText(query.value(3).toString());
            ui->lineEdit_tel_2->setText(query.value(4).toString());
            ui->lineEdit_passwordD->setText(query.value(5).toString());
            ui->InfoPerso->setText(val);
            ui->personneltabs->setCurrentIndex(2);
         }

     }
}

void Interface::on_backBtn_clicked()
{
    ui->personneltabs->setCurrentIndex(0);
}

void Interface::on_pushButton_19_clicked()
{
    QString id = ui->InfoPerso->text();
    QString nom = ui->lineEdit_nom_2->text();
    QString prenom = ui->lineEdit_prenom_2->text();
    QString email = ui->lineEdit_Email->text();
    QString date = ui->lineEdit_DateN2->text();
    QString password = ui->lineEdit_passwordD->text();
    int tel = ui->lineEdit_tel_2->text().toInt();

    adminpersonnel p;
    if(p.rech(id)){
        bool test = p.modifier(id,nom,prenom,email,date,tel,password);
        if(test){
            ui->tabpersonnel->setModel(tmppersonnel.afficher());
            QMessageBox::information(nullptr,QObject::tr("Personnel modifier"),QObject::tr("click cancel to exit!"),QMessageBox::Cancel);
        }
     }else{
            QMessageBox::information(nullptr,QObject::tr("Personnel modifier"),QObject::tr("Error!"),QMessageBox::Cancel);
     }
}

void Interface::on_btnAddService_clicked()
{
    ui->ServicesTabs->setCurrentIndex(1);
}

void Interface::on_btnBackAddService_clicked()
{
    ui->ServicesTabs->setCurrentIndex(0);
}

void Interface::on_tabservice_activated(const QModelIndex &index)
{
    QString val=ui->tabservice->model()->data(index).toString();

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
            ui->InfoServ->setText(val);
            ui->ServicesTabs->setCurrentIndex(2);
         }
     }
}

void Interface::on_btnBackEditService_clicked()
{
    ui->ServicesTabs->setCurrentIndex(0);
}

void Interface::on_MaterialBtnG_clicked()
{
   ui->Hometabs->setCurrentIndex(4);
}

void Interface::on_FournisseurBtnG_clicked()
{
    ui->Hometabs->setCurrentIndex(1);
}

void Interface::on_lineEdit_4_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabFournisseur->setModel(tmpfournisseur.afficher());
    }else{
        ui->tabFournisseur->setModel(tmpfournisseur.recherche(arg1));
    }
}

void Interface::on_btnBackHomeFour_clicked()
{
   ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_btnAddHomeFour_clicked()
{
    ui->Hometabs->setCurrentIndex(2);
}

void Interface::on_btnBackHomeFourAdd_clicked()
{
    ui->Hometabs->setCurrentIndex(1);
}

void Interface::on_BtnFourAdd_clicked()
{
    QString id = ui->lineEdit_IDF->text();
    QString nom = ui->lineEdit_nomF->text();
    QString address = ui->lineEdit_AddressF->text();
    long Tel = ui->lineEdit_telF->text().toInt();
    QString ville = ui->lineEdit_VilleF->text();
    QString code_p = ui->lineEdit_CodeP->text();
    Fournisseur f(id,nom,address,Tel,ville,code_p);
    bool test=f.ajouter();
    if(test){
        ui->tabFournisseur->setModel(tmpfournisseur.afficher());
        ui->Hometabs->setCurrentIndex(1);
    }
}

void Interface::on_tabFournisseur_activated(const QModelIndex &index)
{
    QString val=ui->tabFournisseur->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select id,nom,address,tel,ville,code_p from fournisseur where ID = :id;");
    query.bindValue(":id",val);

    if(query.exec())
    {
        if(query.first())
        {
            ui->lineEdit_nomFe->setText(query.value(0).toString());
            ui->lineEdit_AddessFe->setText(query.value(1).toString());
            ui->lineEdit_TelFe->setText(query.value(2).toString());
            ui->lineEdit_VilleFe->setText(query.value(3).toString());
            ui->lineEdit_PostalFe->setText(query.value(4).toString());
            ui->InfoFour->setText(val);
            ui->Hometabs->setCurrentIndex(3);
         }

     }
}

void Interface::on_backBtn_2_clicked()
{
    ui->Hometabs->setCurrentIndex(1);
}

void Interface::on_FourbtnUpdate_clicked()
{
    QString nom = ui->lineEdit_nomFe->text();
    QString address = ui->lineEdit_AddessFe->text();
    long tel = ui->lineEdit_TelFe->text().toInt();
    QString ville = ui->lineEdit_VilleFe->text();
    QString postal = ui->lineEdit_PostalFe->text();
    QString id = ui->InfoFour->text();
    
    Fournisseur f;
    if(f.rech(id)){
        bool test = f.modifier(id,nom,address,tel,ville,postal);
        if(test){
            ui->tabFournisseur->setModel(tmpfournisseur.afficher());
            ui->Hometabs->setCurrentIndex(1);
        }
     }
}


void Interface::on_FourbtnDelete_clicked()
{
    Fournisseur f;
    if(f.rech(ui->InfoFour->text())){
      bool test=tmpfournisseur.supprimer(ui->InfoFour->text());
      if(test){
            ui->tabFournisseur->setModel(tmpfournisseur.afficher());
            ui->Hometabs->setCurrentIndex(1);
        }
     }else{
         ui->Hometabs->setCurrentIndex(1);
     }
}

void Interface::on_btnBackHomeMat_clicked()
{
    ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_lineEdit_5_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabMaterial->setModel(tmpMaterial.afficher());
    }else{
        ui->tabMaterial->setModel(tmpMaterial.recherche(arg1));
    }
}

void Interface::on_btnAddHomeMat_clicked()
{
    ui->Hometabs->setCurrentIndex(5);
}

void Interface::on_btnBackHomeMatAdd_clicked()
{
    ui->Hometabs->setCurrentIndex(4);
}

void Interface::on_BtnMatAdd_clicked()
{
    QString ref = ui->lineEdit_RefMat->text();
    QString nom = ui->lineEdit_nomMat->text();
    int quantite = ui->lineEdit_quantiteMat->text().toInt();
    Materiel m(ref,nom,quantite);
    bool test=m.ajouter();
    if(test){
        ui->tabMaterial->setModel(tmpMaterial.afficher());
        ui->Hometabs->setCurrentIndex(4);
    }
}

void Interface::on_tabMaterial_activated(const QModelIndex &index)
{
    QString val=ui->tabMaterial->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select nom,quantite from materiel where ref = :ref;");
    query.bindValue(":ref",val);

    if(query.exec())
    {
        if(query.first())
        {
            ui->lineEdit_nomMatE->setText(query.value(0).toString());
            ui->lineEdit_quantiteMatE->setText(query.value(1).toString());
            ui->InfoRefMat->setText(val);
            ui->Hometabs->setCurrentIndex(6);
         }

     }
}

void Interface::on_btnBackHomeMatAdd_2_clicked()
{
    ui->Hometabs->setCurrentIndex(5);
}
