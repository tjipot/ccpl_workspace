#ifndef ADMINPAGE_H
#define ADMINPAGE_H
#include "server.h"
#include <QWidget>

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = 0);
    ~AdminPage();
private:
    Ui::AdminPage *ui;
    Server *server;

private slots:
    void on_pushButtonUpdate_clicked();
    void on_pushButtonReset_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonLogout_clicked();
};

#endif // ADMINPAGE_H
