#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H
#include "server.h"
#include <QWidget>
#include <QTcpServer>
//#include "server1.h"

namespace Ui {
class TcpServerWidget;
}

class TcpServerWidget : public QWidget{
    Q_OBJECT

public:
    explicit TcpServerWidget(QWidget *parent = 0);
    ~TcpServerWidget();
private:
    Ui::TcpServerWidget *ui;
    Server *server;
    //Server1 *server1;
};

#endif // TCPSERVERWIDGET_H
