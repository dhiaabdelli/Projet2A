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
    ui->tabRDV->setModel(tmpRDV.afficher());
    ui->tabPatient->setModel(tmpPatient.afficher());
    ui->tabConvention->setModel(tmpConvention.afficher());
    ui->tabsalle->setModel(tmpsalle.afficher());

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


    ui->tabRDV->verticalHeader()->setVisible(false);
    ui->tabRDV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabRDV->setAlternatingRowColors(true);
    ui->tabRDV->setShowGrid(false);
    ui->tabRDV->verticalHeader()->setSectionsClickable(true);
    ui->tabRDV->horizontalHeader()->setSectionsClickable(true);


    ui->tabPatient->verticalHeader()->setVisible(false);
    ui->tabPatient->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabPatient->setAlternatingRowColors(true);
    ui->tabPatient->setShowGrid(false);
    ui->tabPatient->verticalHeader()->setSectionsClickable(true);
    ui->tabPatient->horizontalHeader()->setSectionsClickable(true);

    ui->tabConvention->verticalHeader()->setVisible(false);
    ui->tabConvention->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabConvention->setAlternatingRowColors(true);
    ui->tabConvention->setShowGrid(false);
    ui->tabConvention->verticalHeader()->setSectionsClickable(true);
    ui->tabConvention->horizontalHeader()->setSectionsClickable(true);


    ui->tabsalle->verticalHeader()->setVisible(false);
    ui->tabsalle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabsalle->setAlternatingRowColors(true);
    ui->tabsalle->setShowGrid(false);
    ui->tabsalle->verticalHeader()->setSectionsClickable(true);
    ui->tabsalle->horizontalHeader()->setSectionsClickable(true);

    adminpersonnel p;
    Materiel m;
    Fournisseur f;
    RDV r;
    patient pa;
    convention c;
    ui->RDVTotal->setText(r.total());
    ui->personnelTotal->setText(p.total());
    ui->MaterialTotal->setText(m.total());
    ui->FournisseurTotal->setText(f.total());
    ui->PatientTotal->setText(pa.total());
    ui->ConventionTotal->setText(c.total());

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

    connect(ui->tabservice->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedservice(int)));
    connect(ui->tabservice->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedservice(int)));

    connect(ui->tabMaterial->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedMaterial(int)));
    connect(ui->tabMaterial->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedMaterial(int)));

    connect(ui->tabRDV->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedRDV(int)));
    connect(ui->tabRDV->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedRDV(int)));


    connect(ui->tabPatient->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedPatient(int)));
    connect(ui->tabPatient->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedPatient(int)));

    connect(ui->tabConvention->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedConvention(int)));
    connect(ui->tabConvention->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedConvention(int)));

    connect(ui->tabsalle->verticalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedsalle(int)));
    connect(ui->tabsalle->horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(slot_table_clickedsalle(int)));

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected(nom)), this, SLOT(connected(nom)));
    socket->connectToHost("127.0.0.1", 4200);
    this->load();
    this->load2();
    this->load3();
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

void Interface::slot_table_clickedservice(int num){
    switch(num){
        case 0:{
            ui->tabservice->setModel(tmpservice.trie(1));
            break;
        }
        case 1:{
            ui->tabservice->setModel(tmpservice.trie(2));
            break;
        }
        case 2:{
            ui->tabservice->setModel(tmpservice.trie(3));
            break;
        }
        case 3:{
            ui->tabservice->setModel(tmpservice.trie(4));
            break;
        }
    }
}

void Interface::slot_table_clickedMaterial(int num){
    switch(num){
        case 0:{
            ui->tabMaterial->setModel(tmpMaterial.trie(1));
            break;
        }
        case 1:{
            ui->tabMaterial->setModel(tmpMaterial.trie(2));
            break;
        }
        case 2:{
            ui->tabMaterial->setModel(tmpMaterial.trie(3));
            break;
        }
    }
}

void Interface::slot_table_clickedRDV(int num){
    switch(num){
        case 0:{
            ui->tabRDV->setModel(tmpRDV.trie(1));
            break;
        }
        case 1:{
            ui->tabRDV->setModel(tmpRDV.trie(2));
            break;
        }
        case 2:{
            ui->tabRDV->setModel(tmpRDV.trie(3));
            break;
        }
    }
}

void Interface::slot_table_clickedPatient(int num){
    switch(num){
        case 0:{
            ui->tabPatient->setModel(tmpPatient.trie(1));
            break;
        }
        case 1:{
            ui->tabPatient->setModel(tmpPatient.trie(2));
            break;
        }
        case 2:{
            ui->tabPatient->setModel(tmpPatient.trie(3));
            break;
        }
        case 3:{
            ui->tabPatient->setModel(tmpPatient.trie(4));
            break;
        }
        case 4:{
            ui->tabPatient->setModel(tmpPatient.trie(5));
            break;
        }
    }
}

void Interface::slot_table_clickedConvention(int num){
    switch(num){
        case 0:{
            ui->tabConvention->setModel(tmpConvention.trie(1));
            break;
        }
        case 1:{
            ui->tabConvention->setModel(tmpConvention.trie(2));
            break;
        }
        case 2:{
            ui->tabConvention->setModel(tmpConvention.trie(3));
            break;
        }
        case 3:{
            ui->tabConvention->setModel(tmpConvention.trie(4));
            break;
        }
        case 4:{
            ui->tabConvention->setModel(tmpConvention.trie(5));
            break;
        }
    }
}

void Interface::slot_table_clickedsalle(int num){
    switch(num){
        case 0:{
            ui->tabsalle->setModel(tmpsalle.trie(1));
            break;
        }
        case 1:{
            ui->tabsalle->setModel(tmpsalle.trie(2));
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
       ui->ServicesTabs->setCurrentIndex(0);
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
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("select NOM from service");
    ui->comboBoxserver->setModel(model);
}

void Interface::load2(){
    ui->combo_CinRDV->clear();
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("select cin from patient");
    ui->combo_CinRDV->setModel(model);
}

void Interface::load3(){
    ui->combo_IDFour->clear();
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select id from fournisseur");
    ui->combo_IDFour->setModel(model);
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
    service s;
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString utilisateur = ui->lineEdit_utilisateur->text();
    int Tel = ui->lineEdit_tel->text().toInt();
    QString email = ui->lineEdit_email->text();
    QString date_na = ui->lineEdit_date->text();
    QString password = ui->lineEdit_password->text();
    QString serviceid = s.getId(ui->comboBoxserver->currentText());
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
        ui->FournisseurTotal->setText(f.total());
        this->load3();
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
            ui->FournisseurTotal->setText(f.total());
            this->load3();
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
        ui->MaterialTotal->setText(m.total());
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
    ui->Hometabs->setCurrentIndex(4);
}

void Interface::on_BtnMatEdit_clicked()
{
    QString ref = ui->InfoRefMat->text();
    QString nom = ui->lineEdit_nomMatE->text();
    int quantite = ui->lineEdit_quantiteMatE->text().toInt();

    Materiel m;
    if(m.rech(ref)){
        bool test = m.modifier(ref,nom,quantite);
        if(test){
            ui->tabMaterial->setModel(tmpMaterial.afficher());
            ui->Hometabs->setCurrentIndex(4);
        }
     }
}

void Interface::on_BtnMatSup_clicked()
{
    Materiel m;
    if(m.rech(ui->InfoRefMat->text())){
      bool test=tmpMaterial.supprimer(ui->InfoRefMat->text());
      if(test){
            ui->tabMaterial->setModel(tmpMaterial.afficher());
            ui->MaterialTotal->setText(m.total());
            ui->Hometabs->setCurrentIndex(4);
        }
     }else{
         ui->Hometabs->setCurrentIndex(4);
     }
}

void Interface::on_lineEdit_3_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabservice->setModel(tmpservice.afficher());
    }else{
        ui->tabservice->setModel(tmpservice.recherche(arg1));
    }
}

void Interface::on_pushButton_12_clicked()
{
    service s;
    if(s.rech(ui->InfoServ->text())){
      bool test=tmpservice.supprimer(ui->InfoServ->text());
      if(test){
            ui->tabservice->setModel(tmpservice.afficher());
            ui->ServicesTabs->setCurrentIndex(0);
        }
     }else{
         ui->ServicesTabs->setCurrentIndex(0);
     }
}

void Interface::on_RDVBtnG_clicked()
{
    ui->Hometabs->setCurrentIndex(7);
}

void Interface::on_btnBackHomeRDV_clicked()
{
    ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_lineEdit_6_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabRDV->setModel(tmpRDV.afficher());
    }else{
        ui->tabRDV->setModel(tmpRDV.recherche(arg1));
    }
}

void Interface::on_btnAddHomeRDV_clicked()
{
    ui->Hometabs->setCurrentIndex(8);
}

void Interface::on_btnBackHomeRDV_3_clicked()
{
    ui->Hometabs->setCurrentIndex(7);
}

void Interface::on_BtnRDVAdd_clicked()
{
    QString id = ui->lineEdit_IDRDV->text();
    QString date = ui->lineEdit_DateRDV->text();
    QString cin = ui->combo_CinRDV->currentText();
    RDV r(id,date,cin);
    bool test=r.ajouter();
    if(test){
        ui->tabRDV->setModel(tmpRDV.afficher());
        ui->RDVTotal->setText(r.total());
        ui->Hometabs->setCurrentIndex(7);
    }
}

void Interface::on_tabRDV_activated(const QModelIndex &index)
{
    QString val=ui->tabRDV->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select id,cin,date_rdv from Rendezvous where id = :id;");
    query.bindValue(":id",val);

    if(query.exec())
    {
        if(query.first())
        {
              ui->lineEdit_DateRDV_2->setText(query.value(2).toString());
              ui->InfoRDVPat->setText(query.value(1).toString());
              ui->InfoRDVId->setText(val);
              ui->Hometabs->setCurrentIndex(9);
        }

     }
}

void Interface::on_PatientBtnG_clicked()
{
    ui->Hometabs->setCurrentIndex(10);
}

void Interface::on_btnBackHomePatient_clicked()
{
    ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_btnAddHomePatient_clicked()
{
    ui->Hometabs->setCurrentIndex(11);
}

void Interface::on_btnBackHomePatient_2_clicked()
{
    ui->Hometabs->setCurrentIndex(10);
}

void Interface::on_BtnPatienAdd_clicked()
{
    QString cin = ui->lineEdit_cin->text();
    QString nom = ui->lineEdit_nom_4->text();
    QString prenom = ui->lineEdit_prenom_3->text();
    QString tel = ui->lineEdit_email_2->text();
    QString email = ui->lineEdit_tel_5->text();
    patient pa(cin,nom,prenom,tel,email);
    bool test=pa.ajouter();
    if(test){
        ui->tabPatient->setModel(tmpPatient.afficher());
        ui->MaterialTotal->setText(pa.total());
        ui->Hometabs->setCurrentIndex(10);
    }
}


void Interface::on_lineEdit_10_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabPatient->setModel(tmpPatient.afficher());
    }else{
        ui->tabPatient->setModel(tmpPatient.recherche(arg1));
    }
}

void Interface::on_tabPatient_activated(const QModelIndex &index)
{
    QString val=ui->tabPatient->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select nom,prenom,tel,email from patient where cin = :cin;");
    query.bindValue(":cin",val);

    if(query.exec())
    {
        if(query.first())
        {
              ui->lineEdit_nom_5->setText(query.value(0).toString());
              ui->lineEdit_prenom_4->setText(query.value(1).toString());
              ui->lineEdit_email_3->setText(query.value(3).toString());
              ui->lineEdit_tel_6->setText(query.value(2).toString());
              ui->InfoPatient->setText(val);
              ui->Hometabs->setCurrentIndex(12);
        }

     }
}

void Interface::on_PatientbtnUpdate_clicked()
{
    QString nom = ui->lineEdit_nom_5->text();
    QString prenom = ui->lineEdit_prenom_4->text();
    QString tel = ui->lineEdit_tel_6->text();
    QString email = ui->lineEdit_email_3->text();
    QString cin = ui->InfoPatient->text();

    patient pa;
    if(pa.rech(cin)){
        bool test = pa.modifier(cin,nom,prenom,tel,email);
        if(test){
            ui->tabPatient->setModel(tmpPatient.afficher());
            ui->Hometabs->setCurrentIndex(10);
        }
     }
}

void Interface::on_btnBackHomePatient_3_clicked()
{
    ui->Hometabs->setCurrentIndex(10);
}

void Interface::on_PatientbtnDelete_clicked()
{
    patient pa;
    if(pa.rech(ui->InfoPatient->text())){
      bool test=tmpPatient.supprimer(ui->InfoPatient->text());
      if(test){
            ui->tabPatient->setModel(tmpPatient.afficher());
            ui->PatientTotal->setText(pa.total());
            ui->Hometabs->setCurrentIndex(10);
        }
     }else{
         ui->Hometabs->setCurrentIndex(10);
     }
}

void Interface::on_RDVbtnUpdate_clicked()
{
    QString id = ui->InfoRDVId->text();
    QString date = ui->lineEdit_DateRDV_2->text();
    QString cin = ui->InfoRDVPat->text();

    RDV r;
    if(r.rech(id)){
        bool test = r.modifier(id,cin,date);
        if(test){
            ui->tabRDV->setModel(tmpRDV.afficher());
            ui->Hometabs->setCurrentIndex(7);
        }
     }
}

void Interface::on_btnBackHomeRDV_4_clicked()
{
    ui->Hometabs->setCurrentIndex(0);
}
void Interface::on_ConventionBtnG_clicked()
{
    ui->Hometabs->setCurrentIndex(13);
}

void Interface::on_btnBackHomePatient_4_clicked()
{
    ui->Hometabs->setCurrentIndex(13);
}

void Interface::on_btnAddHomeRDV_3_clicked()
{
    ui->Hometabs->setCurrentIndex(14);
}

void Interface::on_BtnConventionAdd_clicked()
{
    QString id = ui->lineEdit_IdConv->text();
    QString idfour = ui->combo_IDFour->currentText();
    QString date_d = ui->lineEdit_date_3->text();
    QString date_f = ui->lineEdit_date_4->text();
    QString desc = ui->ConventionDesc->toPlainText();
    convention c(id,idfour,date_d,date_f,desc);
    bool test=c.ajouter();
    if(test){
        ui->tabConvention->setModel(tmpConvention.afficher());
        ui->ConventionTotal->setText(c.total());
        ui->Hometabs->setCurrentIndex(13);
    }
}

void Interface::on_tabConvention_activated(const QModelIndex &index)
{
    QString val=ui->tabConvention->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select idfour,date_d,date_f,des from convention where id = :id;");
    query.bindValue(":id",val);

    if(query.exec())
    {
        if(query.first())
        {
              ui->lineEdit_date_6->setText(query.value(1).toString());
              ui->ConventionDesc_2->setText(query.value(3).toString());
              ui->lineEdit_date_5->setText(query.value(2).toString());
              ui->InfoConvetionIDF->setText(query.value(0).toString());
              ui->InfoConvetionID->setText(val);
              ui->Hometabs->setCurrentIndex(15);
        }

     }
}

void Interface::on_ConvbtnUpdate_clicked()
{
    QString id = ui->InfoConvetionID->text();
    QString idfour = ui->InfoConvetionIDF->text();
    QString date_d = ui->lineEdit_date_6->text();
    QString date_f = ui->lineEdit_date_5->text();
    QString desc = ui->ConventionDesc_2->toPlainText();

    convention c;
    if(c.rech(id)){
        bool test = c.modifier(id,idfour,date_d,date_f,desc);
        if(test){
            ui->tabConvention->setModel(tmpConvention.afficher());
            ui->Hometabs->setCurrentIndex(13);
        }
     }
}

void Interface::on_btnBackHomeConvention_clicked()
{
    ui->Hometabs->setCurrentIndex(13);
}

void Interface::on_ConvbtnDelete_clicked()
{
    convention c;
    if(c.rech(ui->InfoConvetionID->text())){
      bool test=tmpConvention.supprimer(ui->InfoConvetionID->text());
      if(test){
            ui->tabConvention->setModel(tmpConvention.afficher());
            ui->ConventionTotal->setText(c.total());
            ui->Hometabs->setCurrentIndex(13);
        }
     }else{
         ui->Hometabs->setCurrentIndex(13);
     }
}

void Interface::on_RDVDelete_clicked()
{
    RDV r;
    if(r.rech(ui->InfoRDVId->text())){
      bool test=tmpRDV.supprimer(ui->InfoRDVId->text());
      if(test){
            ui->tabRDV->setModel(tmpRDV.afficher());
            ui->RDVTotal->setText(r.total());
            ui->Hometabs->setCurrentIndex(7);
        }
     }else{
         ui->Hometabs->setCurrentIndex(7);
     }
}

void Interface::on_btnBackHomeRDV_2_clicked()
{
    ui->Hometabs->setCurrentIndex(7);
}

void Interface::on_WROOMBtnG_clicked()
{
    ui->Hometabs->setCurrentIndex(16);
}

void Interface::on_btnSalleBackHome_clicked()
{
    ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_lineEdit_7_textChanged(const QString &arg1)
{
    if(arg1 == ""){
       ui->tabsalle->setModel(tmpsalle.afficher());
    }else{
        ui->tabsalle->setModel(tmpsalle.Rechercher(arg1.toInt()));
    }
}

void Interface::on_btnAddService_2_clicked()
{
    ui->Hometabs->setCurrentIndex(17);
}

void Interface::on_btnBackHomePatient_5_clicked()
{
     ui->Hometabs->setCurrentIndex(0);
}

void Interface::on_BtnSalleAdd_clicked()
{
    int num = ui->lineEdit_numsalle->text().toInt();
    QString bloc = ui->lineEdit_blocsalle->text();
    salle s(num,bloc);
    bool test=s.ajouter();
    if(test){
        ui->tabsalle->setModel(tmpsalle.afficher());
        ui->Hometabs->setCurrentIndex(16);
    }
}

void Interface::on_tabsalle_activated(const QModelIndex &index)
{
    QString val=ui->tabsalle->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select num,bloc from salle where num = :num;");
    query.bindValue(":num",val);

    if(query.exec())
    {
        if(query.first())
        {
              ui->lineEdit_blocsalle_2->setText(query.value(1).toString());
              ui->lineEdit_numsalle_2->setText(val);
              ui->Hometabs->setCurrentIndex(18);
        }

     }
}

void Interface::on_SallebtnUpdate_clicked()
{
    int num = ui->lineEdit_numsalle_2->text().toInt();
    QString bloc = ui->lineEdit_blocsalle_2->text();

    salle s;
    if(s.rech(num)){
        bool test = s.modifier(num,bloc);
        if(test){
            ui->tabsalle->setModel(tmpsalle.afficher());
            ui->Hometabs->setCurrentIndex(16);
        }
     }
}

void Interface::on_SallebtnDelete_clicked()
{
    salle s;
    if(s.rech(ui->lineEdit_numsalle_2->text().toInt())){
      bool test=tmpsalle.supprimer(ui->lineEdit_numsalle_2->text().toInt());
      if(test){
            ui->tabsalle->setModel(tmpsalle.afficher());
            ui->Hometabs->setCurrentIndex(16);
        }
     }else{
         ui->Hometabs->setCurrentIndex(16);
     }
}
