#ifndef Interface_H
#define Interface_H

#include <QDialog>
#include "adminpersonnel.h"
#include "service.h"
#include "fournisseur.h"
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

    void on_btnAddP_clicked();

    void on_btnPersonnel_clicked();

    void on_btnListP_clicked();

    void on_tabpersonnel_activated(const QModelIndex &index);


    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_btnTrie_clicked();

    void on_btnTriee_clicked();

    void on_pushButton_3_clicked();

    void on_btnreload_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_btnService_clicked();

    void on_btnAddP_2_clicked();

    void on_btnListP_2_clicked();

    void on_btnreload_2_clicked();

    void on_btnTriee_2_clicked();

    void on_pushButton_4_clicked();

    void on_tabservice_activated(const QModelIndex &index);

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_btnstat_clicked();

    void load();
    void stat();

    void setbtnEnable(QPushButton*,QPushButton* &,QString);

    void on_btnChat_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_btnAdmin_clicked();

    void on_btnHome_clicked();

    void on_btnPersonnel_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();
    void slot_table_clicked(int);
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

private:
    Ui::Interface *ui;
    QWidget* parent;
    adminpersonnel tmppersonnel;
    service tmpservice;
    Fournisseur tmpfournisseur;
    QString pagetitle;
    QPushButton* btncurrent;
    QTcpSocket *socket;
};


#endif // Interface_H
