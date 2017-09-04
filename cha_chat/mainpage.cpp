/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: this file operates the main UI page of this chat program, through the UI page,
 * normal users can login and register, adminstrator can login and manage the server. Three UI
 * pages are: user register, user login, admin login;
 */

#include "mainpage.h"
#include "chatpage.h"
#include "adminpage.h"
#include "ui_mainpage.h"
#include "registerpage.h"
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//#include <QSqlDatabase>

/* MainPage初始化: 构造函数 */
MainPage::MainPage(QWidget *parent):QWidget(parent), ui(new Ui::MainPage){
    ui->setupUi(this);

    recoverSettings(ui);                                                        //根据先前的remember设置, 恢复初始的状态;

    /* Database Section: qDebug() << QSqlDatabase::drivers(); */
    db = QSqlDatabase::addDatabase("QSQLITE");                                  //数据库对象, 私有全局变量;
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "//lanqq.db");    //加了separator()也可以不用"//";
    if(!db.open()){                                                             //数据库操作判断;
        QMessageBox::critical(0, "Database Open Error", db.lastError().text());
        return;
    }
    /* 数据库的初始化要在构造函数结束之前进行,
     * 顺序不能错, 可能可以放在构造函数中:
     * qDebug() << db.tables(); */
    this->setWindowTitle("ChaChat!");
}

/* MainPage析构函数 */
MainPage::~MainPage(){
    delete ui;
}

/* User Register */
void MainPage::on_pushButtonRegister_clicked(){         //用户注册按钮, dialog类型页面;
    RegisterPage rp(this);                              //生成RegisterPage对象, "registerpage.h" included;
    rp.show();
    int ret = rp.exec();
    if(ret == QDialog::Accepted){                       //根据返回选择, 设置MainPage(登录页面)的username和password值;
        ui->lineEditUsername->setText(rp.getUsername());
        ui->lineEditPassword->setText(rp.getPassword());
    }else{
        ui->lineEditUsername->clear();
        ui->lineEditPassword->clear();
    }
}

/* User Login */
void MainPage::on_pushButtonLogin_clicked(){
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    QString u_passcode_sql = "select u_passcode from user_info where u_name = '" + username + "'";
    QSqlQuery u_passcode_query;
    if(!u_passcode_query.exec(u_passcode_sql)){         //QSqlQuery和u_passcode_sql配对使用;
        QMessageBox::critical(this, "SQL Error", u_passcode_query.lastError().text());
        return;
    }
    while(u_passcode_query.next()){                     //query executed之后, 就会有结果, next()迭代器就可以丛中取数据;
        if(password != u_passcode_query.value("u_passcode")){
            QMessageBox::critical(this, "Login Failed", "Password Wrong");
        }else{
            ChatPage *cp = new ChatPage(0, username);   //坑了个大爹, 默认构造函数永远在设置名字username之前, 除非构造时就添上..;
            /* cp->setUsername(username);               //query.value("u_name").toString(): Fuck, Should Add toString(); */
            cp->show();                                 //A New ChatPage;
        }
    }
}

/* Admin Login */
void MainPage::on_pushButtonAdminLogin_clicked(){

    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    QString u_passcode_sql = "select u_passcode from user_info where u_name = '" + username + "'";
    QSqlQuery u_passcode_query;
    if(!u_passcode_query.exec(u_passcode_sql)){
        QMessageBox::critical(this, "SQL Error", u_passcode_query.lastError().text());
        return;
    }
    if(u_passcode_query.next()){
        if(password != u_passcode_query.value("u_passcode")){
            QMessageBox::critical(this, "Login Failed", "Admin/Password Not Match");
        }else{
            AdminPage *ap = new AdminPage();            //A New AdminPage;
            ap->show();
        }
    }
}

/* Helper Function When Closing The MainPage Page */
void MainPage::closeEvent(QCloseEvent *event){          //设置页面关闭的记忆功能, 保存设置信息;
    Q_UNUSED(event)
    QSettings settings("Chat", "MAC");                  //QSettings模块, 用于本地存储;
    settings.setValue("username", ui->lineEditUsername->text());
    if(ui->checkBoxRemember->isChecked()){
        settings.setValue("remember", true);
        settings.setValue("password", ui->lineEditPassword->text());
    }else{
        settings.setValue("remember", false);
    }
    delete ui;
}

/* Helper Function When Reopen The MainPage Page */
void MainPage::recoverSettings(Ui::MainPage *ui){
    QSettings settings("Chat", "MAC");
    if(settings.allKeys().contains("username")){
        ui->lineEditUsername->setText(settings.value("username").toString());
        ui->checkBoxRemember->setChecked(settings.value("remember").toBool());
        if(ui->checkBoxRemember->isChecked()){
            ui->lineEditPassword->setText(settings.value("password").toString());
        }
    }
}

