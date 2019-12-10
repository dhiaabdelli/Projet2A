#ifndef Interface_H
#define Interface_H

#include <QDialog>
#include "adminpersonnel.h"
#include "service.h"
#include "fournisseur.h"
#include "materiel.h"
#include "rdv.h"
#include "patient.h"
#include "convention.h"
// We'll need some regular expression magic in this code:
#include <QRegExp>
#include <QTcpSocket>
namespace Ui {
class Interface;
}

class Interface : public QDialog
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr,int type = 0,QString nom = "");
    ~Interface();

private slots:
    void on_pushButton_clicked();



    void on_tabpersonnel_activated(const QModelIndex &index);


    void on_pushButton_2_clicked();


    void on_tabservice_activated(const QModelIndex &index);


    void on_pushButton_13_clicked();


    void load();

    void load2();

    void setbtnEnable(QPushButton*,QPushButton* &,QString);

    void on_btnChat_clicked();


    void on_btnAdmin_clicked();

    void on_btnHome_clicked();

    void on_btnPersonnel_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void slot_table_clicked(int);
    void slot_table_clickedservice(int);
    void slot_table_clickedMaterial(int num);
    void slot_table_clickedRDV(int num);
    void slot_table_clickedPatient(int num);
    void connected(QString);
    void readyRead();
    void on_backBtn_clicked();

    void on_pushButton_19_clicked();

    void on_btnAddService_clicked();

    void on_btnBackAddService_clicked();

    void on_btnBackEditService_clicked();

    void on_MaterialBtnG_clicked();

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_btnBackHomeFour_clicked();

    void on_btnAddHomeFour_clicked();

    void on_btnBackHomeFourAdd_clicked();

    void on_BtnFourAdd_clicked();

    void on_FournisseurBtnG_clicked();

    void on_tabFournisseur_activated(const QModelIndex &index);

    void on_backBtn_2_clicked();

    void on_FourbtnUpdate_clicked();
        
    void on_FourbtnDelete_clicked();

    void on_btnBackHomeMat_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_btnAddHomeMat_clicked();

    void on_btnBackHomeMatAdd_clicked();

    void on_BtnMatAdd_clicked();

    void on_tabMaterial_activated(const QModelIndex &index);

    void on_btnBackHomeMatAdd_2_clicked();

    void on_BtnMatEdit_clicked();

    void on_BtnMatSup_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_12_clicked();

    void on_RDVBtnG_clicked();

    void on_btnBackHomeRDV_clicked();

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_btnAddHomeRDV_clicked();

    void on_btnBackHomeRDV_3_clicked();

    void on_BtnRDVAdd_clicked();

    void on_tabRDV_activated(const QModelIndex &index);

    void on_PatientBtnG_clicked();

    void on_btnBackHomePatient_clicked();

    void on_btnAddHomePatient_clicked();

    void on_btnBackHomePatient_2_clicked();

    void on_BtnPatienAdd_clicked();

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_tabPatient_activated(const QModelIndex &index);

    void on_PatientbtnUpdate_clicked();

    void on_btnBackHomePatient_3_clicked();

    void on_PatientbtnDelete_clicked();

    void on_RDVbtnUpdate_clicked();

private:
    Ui::Interface *ui;
    QWidget* parent;
    adminpersonnel tmppersonnel;
    service tmpservice;
    Fournisseur tmpfournisseur;
    Materiel tmpMaterial;
    RDV tmpRDV;
    patient tmpPatient;
    QString pagetitle;
    QPushButton* btncurrent;
    QTcpSocket *socket;
};


#endif // Interface_H
