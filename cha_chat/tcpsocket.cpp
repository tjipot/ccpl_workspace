/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Description: Inherits From QTcpSocket, The "#include"
 * Statement Is In "tcpsocket.h".
 */

#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject* parent){
    Q_UNUSED(parent)
}

void TcpSocket::slotDisconnected(){
    emit disconnected(socketDescriptor());
}
