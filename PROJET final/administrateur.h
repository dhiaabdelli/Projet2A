#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include <QDialog>
#include "adminpersonnel.h"
#include "service.h"
namespace Ui {
class administrateur;
}

class administrateur : public QDialog
{
    Q_OBJECT

public:
    explicit administrateur(QWidget *parent = nullptr);
    ~administrateur();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_nom_textChanged(const QString &arg1);

    void on_btnAddP_clicked();

    void on_btnPersonnel_clicked();

    void on_btnListP_clicked();

    void on_tabpersonnel_activated(const QModelIndex &index);

    void on_pushButton_6_clicked();

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

private:
    Ui::administrateur *ui;
    adminpersonnel tmppersonnel;
    service tmpservice;
};


#endif // ADMINISTRATEUR_H
