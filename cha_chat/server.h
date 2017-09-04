#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "tcpsocket.h"

class Server : public QTcpServer{                       //继承了QTcpServer
    Q_OBJECT

public:
    Server(QObject *parent = 0, int port = 8080);       //Server(quint16 Port = 8080);
protected:
    void incomingConnection(qintptr socketDescriptor);  //Virtual Function: 在新连接进来时调用;
private:
    QList<TcpSocket*> clients;

public slots:
    void slotAccept();
    void slotReadData();
    void slotDisconnected(int);
};

#endif // SERVER_H
