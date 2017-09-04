#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H
#include <QDialog>

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QDialog{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = 0);
    ~RegisterPage();
    QString getUsername();  //return username in register page;
    QString getPassword();  //return password in register page;
private:
    Ui::RegisterPage *ui;

signals:

public slots:

private slots:
    void on_buttonBoxConfirm_accepted();
    void on_buttonBoxConfirm_rejected();
    void on_pushButtonBackToLogin_clicked();
};

#endif // REGISTERPAGE_H
