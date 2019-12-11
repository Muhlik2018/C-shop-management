#include "mainwindow.h"
#include <QApplication>
#include"connection.h"
#include"logindialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!creatconnection())return 0;
    MainWindow w;
    loginDialog dlg;
    //若输入密码成功，则显示
    if(dlg.exec()==QDialog::Accepted)
    {
        w.show();
    }
    else
    {
        return 0;
    }
    return a.exec();
}
