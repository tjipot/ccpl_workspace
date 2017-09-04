/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: this is the register page, mainly handle user's register operation, and
 * can return to mainpage to login.
 *
 */

#include "registerpage.h"
#include "ui_registerpage.h"
#include <QDebug>
#include <QMessageBox>

/* RegisterPage Constructor */
RegisterPage::RegisterPage(QWidget *parent):QDialog(parent), ui(new Ui::RegisterPage){
    ui->setupUi(this);
    this->setWindowTitle("Register Page");
}

/* RegisterPage Destructor */
RegisterPage::~RegisterPage(){
    delete ui;
}

/* Helper Function: Reduce The Retyping When
 * Jumping From MainPage Into This RegisterPage */
QString RegisterPage::getUsername(){
    return ui->lineEditUsername->text();
}

/* Helper Function: Reduce The Retyping When
 * Jumping From MainPage Into This RegisterPage */
QString RegisterPage::getPassword(){
    return ui->lineEditPassword->text();
}

/* Register Accepted */
void RegisterPage::on_buttonBoxConfirm_accepted(){
    if(ui->lineEditUsername->text().isEmpty() || ui->lineEditPassword->text().isEmpty() || ui->lineEditPassword->text() != ui->lineEditRepwd->text()){
        QMessageBox::critical(this, "Register Failed", "Info Not Complete");
    }
    qDebug() << "Register Confirmed";
}

/* Register Rejected */
void RegisterPage::on_buttonBoxConfirm_rejected(){
    qDebug() << "Register Canceled";
}

/* Back To MainPage */
void RegisterPage::on_pushButtonBackToLogin_clicked(){
    close(); //Mark: Just So?!
    qDebug() <<"Back To Login Pressed";
}
