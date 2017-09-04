/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: this page helps administrator to manage the chatting server(server.cpp),
 * also helps to setup configurations of the chating system.
 */

#include "adminpage.h"
#include "ui_adminpage.h"
#include <QMessageBox>
#include <QTcpServer>

AdminPage::AdminPage(QWidget *parent): QWidget(parent), ui(new Ui::AdminPage){
    ui->setupUi(this);
    ui->pushButtonStop->setEnabled(false);  //"Server Stop" should be disabled when admin page starts;
    this->setWindowTitle("Admin Page");
}

AdminPage::~AdminPage(){
    delete ui;
}

/* Reset The Default Settings: IP and Port */
void AdminPage::on_pushButtonReset_clicked(){
    ui->lineEditIpAddr->setText("127.0.0.1");
    ui->lineEditPort->setText("8080");
}

/* Launch The Server When Button Clicked:
 * Will Call Server Class's Constructor.
 */
void AdminPage::on_pushButtonStart_clicked(){
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
    if(ui->lineEditIpAddr->text().isEmpty() || ui->lineEditPort->text().isEmpty()){
        QMessageBox::critical(this, "Connecting Error", "IP Address/Port Should Not Be Empty");
        return;
    }
    /* Call Server Class To Launch The TCP Server */
    server = new Server();  //QTcpServer::listen(QHostAddress::AnyIPv4, ui->lineEditPort->text().toInt());;
}

/* Function Placeholder */
void AdminPage::on_pushButtonUpdate_clicked(){ }
void AdminPage::on_pushButtonStop_clicked(){ }
void AdminPage::on_pushButtonLogout_clicked(){ }
