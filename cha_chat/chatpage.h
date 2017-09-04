#ifndef CHATPAGE_H
#define CHATPAGE_H
#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = 0, QString name = "alex");
    ~ChatPage();
    void setUsername(QString un);
    QString getUsername();

private:
    Ui::ChatPage *ui;
    QString username;
    QList<QTcpSocket*> friendSocketList;
    QTcpSocket *chatSocket;     //Includes Port And SocketId
    void geneFriendList();
    void sendMessage();

signals:
    //void sigMsgSent();

private slots:
    void on_lineEditSendMsg_returnPressed();
    void on_pushButtonSendMsg_clicked();
    //void slotTextBrowserRead();
    void slotConnected();       //Connect Connected()
    void slotDisconnected();    //Connect Disconnected()
    void slotReadData();        //Connect ReadyRead()
};

#endif // CHATPAGE_H
