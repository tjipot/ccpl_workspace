/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: entrance of this local-chatting program.
 */

#include "mainpage.h"
#include "chatpage.h"
#include "adminpage.h"
#include "registerpage.h"
#include "tcpserverwidget.h"
#include <QApplication>
//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QMessageBox>
//#include <QDebug>
//#include <QDir>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

//    ChatWidget w;
//    w.show();
//
//    LoginForm lf;
//    lf.show();
//
//    ChatPage cp;
//    cp.show();
//
//    RegisterPage rp;
//    rp.show();
//
//    TcpServerWidget tsw;
//    tsw.show();
//
//    AdminPage ap;
//    ap.show();

    MainPage mp;
    mp.show();

    return a.exec();
}
