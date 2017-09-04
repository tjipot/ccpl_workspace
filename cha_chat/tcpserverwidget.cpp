/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: this is the functionality test during writting this chatting program,
 * not included in chatting program.
 */

#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TcpServerWidget::TcpServerWidget(QWidget *parent): QWidget(parent), ui(new Ui::TcpServerWidget){
    ui->setupUi(this);
    server = new Server();                          //创建了一个服务器, 交给Server类对象去处理
    //server->listen(QHostAddress::AnyIPv4, 8080);  //至此, 建立了一个服务器;
    //server1 = new Server1();
}

TcpServerWidget::~TcpServerWidget(){
    delete ui;
}
