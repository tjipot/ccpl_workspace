#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class MainPage;
}

class MainPage: public QWidget{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainPage *ui;
    QSqlDatabase db;
    void recoverSettings(Ui::MainPage *ui);

private slots:
    void on_pushButtonRegister_clicked();   //三个UI界面;
    void on_pushButtonLogin_clicked();      //三个UI界面;
    void on_pushButtonAdminLogin_clicked(); //三个UI界面;
};

#endif // MAINPAGE_H
