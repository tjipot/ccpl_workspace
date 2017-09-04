/*
 * @UNIVESRE.COM @Oct 06, 2016 @HYe
 * Descrition: this is the client page, normal user uses this page to send messgaes to
 * their friends through server, and server sends messages to their friends in the same
 * local network.
 *
 */

#include "chatpage.h"
#include "ui_chatpage.h"
#include <iostream>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QHostAddress>
#include <QAbstractSocket>

/* ChatPage Constructor */
ChatPage::ChatPage(QWidget *parent, QString name):QWidget(parent), ui(new Ui::ChatPage), username(name){ //初始化时应传入登录的"username";
    ui->setupUi(this);

    chatSocket = new QTcpSocket(this);                                               //创建TCP套接字, 一个客户端对象运行一个TcpSocket descriptor;
    /* 建立信号和槽的关联 */
    connect(chatSocket, SIGNAL(connected()), this, SLOT(slotConnected()));           //chatSocket对象的连接信号: QTcpSocket内含connected(), 槽函数是自定义的;
    connect(chatSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));     //chatSocket对象的断开信号: QTcpSocket内含disconnected(), 槽函数是自定义的;
    connect(chatSocket, SIGNAL(readyRead()), this, SLOT(slotReadData()));            //chatSocket对象的可读信号(读数据): QTcpSocket内含readyRead(), 槽函数是自定义的;
    /* 异步Connect, TCP Socket */
    chatSocket->connectToHost(QHostAddress("127.0.0.1"), QString("8080").toShort()); //ui->lineEditHostIp->text()和ui->lineEditHostPort->text().toShort();
    chatSocket->waitForConnected();                                                  //要等待连接, 要不然程序接着执行了;
    if(chatSocket->state() == QAbstractSocket::ConnectedState){                      //Note: socket's state must be ConnectedState before reading/writing, 提醒: QT的API;
        /* 如果Connected了..Placeholder Here */                                       //发送用户信息到服务器, 并等待回应; -> 短连接, 可以不用上面的三个connect信号槽函数
        chatSocket->waitForReadyRead(200);                                           //要等待, 因为程序执行时间太快而网络没那么快;
        if(chatSocket->bytesAvailable()){                                            //读数据(的流程)
            QByteArray ba;                                                           //QByteArray: 字节的array, 可以按需转换成特定对象, 如字符串对象;
            ba.resize(chatSocket->bytesAvailable());
            chatSocket->read(ba.data(), ba.size());
            //Placeholder..
        }
    }

    /* ChatPage->this */
    this->setWindowTitle("Hello~ " + username + "!");
    /* Helper Function */
    geneFriendList();
}

/* ChatPage Destructor */
ChatPage::~ChatPage(){
    delete ui;
}

/* Helper Function
 * QT中SQL流程: SQL Statement -> SQL Query -> Query Result;
 */
void ChatPage::geneFriendList(){

    QString u_friend_id_sql = "select user_friend_info.u_friend_id from user_friend_info, user_info where\
                                      user_friend_info.u_id = user_info.u_id and\
                                      user_info.u_name = '" + username + "'";       //从两张表中查询"u_friend_id"值;
    QSqlQuery u_friend_id_query;                                                    //QSqlQuery就是MySQL数据库的query;
    if(!u_friend_id_query.exec(u_friend_id_sql)){
        QMessageBox::critical(this, "Query u_friend_id Error.", u_friend_id_query.lastError().text());
        return;
    }

    /* 有多少输出,就执行多少次 */
    while(u_friend_id_query.next()){                                                        //Query结果按行读取, 每行按索引取值(像数组那样);
        QString tmpId = u_friend_id_query.value(0).toString();                              //QString::number(query.value(0).toInt()): "u_friend_id";
        QString u_name_sql = "select u_name from user_info where u_id = '" + tmpId + "'";   //查询"u_friend_id"对应的username;
        QSqlQuery u_name_query;
        if(!u_name_query.exec(u_name_sql)){                                                 //先执行SQL语句, 并对执行结果取反, 交由if语句判断: 二合一的效果;
            QMessageBox::critical(this, "Query u_name Error.", u_name_query.lastError().text());
            return;
        }

        QString uname = "u_name";
        QString tmpName;
        while(u_name_query.next()){                         //next()是QSqlQuery对象的一个迭代器, 默认值为query结果的第一个元素: 其实"u_name"元素就一个, 也可以用if()替代while();
            tmpName = u_name_query.value(uname).toString(); //由于之前生成ChatPage时没有初始化username, 导致这个查询语句错误: "QSqlQuery::value: unknown field name", 是这样吧?!
        }
        ui->listWidgetFriend->addItem(tmpName);             //将查询到的friend username显示出来;
        ui->comboBox_FriendSelection->addItem(tmpName);     //创建发送列表"comboBox";
    }

    /* 查询该用户的群组(group)情况, 并添加的friend list中 */
    QString group_name_sql = "select user_group_info.group_name from user_group_info, user_info where\
                                     user_group_info.group_member_user_id = user_info.u_id and\
                                     user_info.u_name = '" + username + "'";    //查询"group_name";
    QSqlQuery group_name_query;
    if(!group_name_query.exec(group_name_sql)){
        QMessageBox::critical(this, "Query group_name Error.", group_name_query.lastError().text());
        return;
    }
    while(group_name_query.next()){                          //next()迭代器+while语句: 我遍历完你;
        QString tmpGroupName = group_name_query.value("group_name").toString();
        ui->listWidgetFriend->addItem(tmpGroupName);         //将查询到的friend username显示出来;
        ui->comboBox_FriendSelection->addItem(tmpGroupName); //创建发送列表"comboBox";
    }
}

/* Send Message's Helper Function:
 * called by on_lineEditSendMsg_returnPressed()
 * and on_pushButtonSendMsg_clicked();
 * Msg format: "MSG/GRP_SENDER_RECVER_MSGCONETNT";
 */
void ChatPage::sendMessage(){
    if(chatSocket->isValid()){                                                                      //Returns true if the socket is valid and ready for use; otherwise returns false.
        QByteArray ba;
        QString sendingTo = ui->comboBox_FriendSelection->currentText();
        if(sendingTo.contains("grp_")){                                                             //"grp_" is the prefix of group chat's name;
            QString u_name_sql = "select user_info.u_name from user_info, user_group_info where\
                                                user_info.u_id = user_group_info.group_member_user_id and\
                                                user_group_info.group_name = '" + sendingTo + "'";  //select all names in a group;
            QSqlQuery u_name_query;
            if(!u_name_query.exec(u_name_sql)){
                QMessageBox::critical(this, "SQL Name In Group Query Error.", u_name_query.lastError().text());
                return;
            }

            QString tmpLineEditSentMsg = QString(ui->lineEditSendMsg->text().toUtf8());
            while(u_name_query.next()){
                ba.clear();                     //每次拼接完一个群聊成员用户的消息后, 要清空一次ba;
                QString groupMemberName = u_name_query.value("u_name").toString();
                QString msgEnding = "MSGEND";   //qDebug() << groupMemberName;
                QString finalMessage = QString("GRP_" + username + "_" + groupMemberName + "_[GRP]" + tmpLineEditSentMsg + msgEnding);
                ba.append(finalMessage);        //qDebug() << finalMessage;
                chatSocket->write(ba);
                /* 严重怀疑这里chatSocket是带有缓冲的, 要不然server那里怎么都黏在一起了:
                 * "Server: "GRP_alex_alex_[GRP]heregoMSGENDGRP_alex_cathy_[GRP]
                 * heregoMSGENDGRP_alex_emma_[GRP]heregoMSGEND"", 也间接证明了,
                 * "chatSocket->waitForReadyRead(500)"在这里不是必要的;
                 * 关于粘包的问题, 请参考项目说明("README.md")中的知识来龙去脉章节; */
                ui->lineEditSendMsg->clear();   //发送完后清空编辑区域;
            }
        }else{
            ba.append("MSG_" + username + "_" + sendingTo + "_");               //Message Header Format: "MSG_senderName_recverName_MsgContent";
            ba.append(QString(ui->lineEditSendMsg->text().toUtf8()));           //Append Message Content;
            chatSocket->write(ba);                                              //Send The Pickled Msg;
            ui->lineEditSendMsg->clear();
        }
    }
}
/* Send Message: Return Pressed */
void ChatPage::on_lineEditSendMsg_returnPressed(){ sendMessage(); }             //Calls sendMessage();
/* Send Message: Button Clicked */
void ChatPage::on_pushButtonSendMsg_clicked(){ sendMessage(); }                 //Calls sendMessage();


/* Read Data, Decode The Msg!
 * The server sends all the messages to each client connecting
 * to it since this program is designed to be a local network
 * chatting program, the client/customer side recv the msg and
 * decode them, if the msg is sent to them, the client show the
 * msg, otherwise, the client not show the msg.
 */
void ChatPage::slotReadData(){
    QByteArray ba;
    ba.resize(chatSocket->bytesAvailable());                                    //记住: QTcpSocket对象已经高度封装了一些功能了, 如bytesAvailable();
    chatSocket->read(ba.data(), ba.size());                                     //重要: read ba.size()大小的数据到ba.data(), 这点和Linux内核的API形微不同, 但质同;
    QString recvedMsg = QString(ba);
    if(recvedMsg.contains("GRP")){                                              //Decode the message follow the message origanize rule;
        QStringList groupMsgSeperator = recvedMsg.split(QRegExp("MSGEND"));     //Group msg type: split messages into each independent msg, because the recved msg is a "spliced package(粘包)";
        for(int i=0; i<groupMsgSeperator.size()-1; i++){                        //There is no character after "MSGEND", but split() will generate an element in QStringList;
            QString eachMsg = groupMsgSeperator.at(i);
            QStringList sections = eachMsg.split(QRegExp("_"));                 //把每一块装进一个QStringList中: MSG + SENDER + RECVER + CONTENT;
            QString sender_1 = sections.at(1).trimmed();                        //SENDER section;
            QString recver_1 = sections.at(2).trimmed();                        //RECVER section;
            QString msgContent_1 = sections.at(3).trimmed();                    //MSG CONTENT section;
            if(username == sender_1 || username == recver_1){                   //ANY one who is the sender or recver COULD show the message!;
                ui->listWidgetChating->addItem(sender_1 + "->" + recver_1 + ": " + msgContent_1);
            }
        }
    }else{                                                                      //Normal msg: one to one type;
        QStringList sections = recvedMsg.split(QRegExp("_"));                   //把每一块装进一个QStringList中: MSG + SENDER + RECVER + CONTENT;
        QString sender_1 = sections.at(1).trimmed();
        QString recver_1 = sections.at(2).trimmed();
        QString msgContent_1 = sections.at(3).trimmed();
        if(username == sender_1 || username == recver_1){
            ui->listWidgetChating->addItem(sender_1 + "->" + recver_1 + ": " + msgContent_1);
        }
    }
}


/* Placeholder Function: Left For Blank */
void ChatPage::slotConnected(){ qDebug() << "slotConnected()"; }
void ChatPage::slotDisconnected(){ qDebug() << "slotDisconnnected()";}
void ChatPage::setUsername(QString un){ this->username = un; }
QString ChatPage::getUsername(){ return this->username; }
