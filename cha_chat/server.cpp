/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: this is the server of chatting program, it recvives message from clients,
 * processes message, and send back to designated clients.
 */

#include "server.h"

/* Placeholder: "Server::Server(quint16 Port){" */
/* Constructor of Server Class: listen() tells the server to
 * listen for incoming connections on address address and port
 * port. If port is 0, a port is chosen automatically. If address
 * is QHostAddress::Any, the server will listen on all network
 * interfaces. Returns true on success; otherwise returns false. */
Server::Server(QObject *parent, int port): QTcpServer(parent){
    /* Inherits From QTcpServer, So, listen() */
    listen(QHostAddress::AnyIPv4, port);                    //connect(this, SIGNAL(newConnection()), SLOT(slotAccept()));
}

/* Implement Virtual Function: Add An Incoming Connection Into client list */
void Server::incomingConnection(qintptr socketDescriptor){  //连进来一个client: 用户登录;
    Q_UNUSED(socketDescriptor)
    TcpSocket *client = new TcpSocket();                    //创建一个Socket, 相当于Linux中的动态数据: 堆中创建, 退出不回收?!;
    client->setSocketDescriptor(socketDescriptor);          //相当于Linux中的bind(): Socket Descriptor: Socket ID;

    /* Signal, Slot */
    connect(client, SIGNAL(readyRead()), this, SLOT(slotReadData()));
    connect(client, SIGNAL(disconnected(int)), this, SLOT(slotDisconnected(int)));
    //connect(client, SIGNAL(disconnected()), this, SLOT(slotDisconnected())); //断开连接;
    clients << client;                                      //将TcpSocket对象加入到QList对象中: 连进来加一个(动态);
}

/* Signal: readyRead(), Slot: slotReadData(),
 * Read Data(QByteArray); */
void Server::slotReadData(){
    foreach(QTcpSocket *client_1, clients){                 //clients Is An Aggregation Of QTcpSocket objects;
        while(client_1->bytesAvailable() > 0){
            QByteArray ba;
            ba.resize(client_1->bytesAvailable());
            /* 粘包: Package Splicing Happens,
             * Because QT Will Buffer The Data,
             * Reference To "README.md" of This
             * Project. */
            client_1->read(ba.data(), ba.size());           //Same With The One In ChatPage Class;
            foreach (QTcpSocket *client_2, clients) {
                client_2->write(ba);                        //转发给所有: ;
                //qDebug() << cli->localPort() << " " << cli->socketDescriptor();
            }
        }
    }
}

void Server::slotAccept(){ }
void Server::slotDisconnected(int socketDes){ Q_UNUSED(socketDes) }
