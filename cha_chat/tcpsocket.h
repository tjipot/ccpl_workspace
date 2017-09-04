#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QObject>
#include <QTcpSocket>

/* Inherits From QTcpSocket */
class TcpSocket : public QTcpSocket{
    Q_OBJECT

public:
    TcpSocket(QObject *parent = 0);

signals:
    void disconnected(int socketDes);   //断连时调用

private slots:
    void slotDisconnected();
};

#endif // TCPSOCKET_H
