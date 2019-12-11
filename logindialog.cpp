#include "logindialog.h"
#include "ui_logindialog.h"
#include"connection.h"
#include<QMessageBox>
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{
    //获取输入的密码，若为空则返回
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("请输入密码"),tr("请输入密码再登陆！"),QMessageBox::Ok);
        ui->lineEdit->setFocus();
    }
    else
    {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if(query.value(0).toString()==ui->lineEdit->text())
        {
            QDialog::accept();
        }
        else
        {
            QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码"),QMessageBox::Ok);
            ui->lineEdit->clear();
            ui->lineEdit->setFocus();
        }
    }
}

void loginDialog::on_pushButton_2_clicked()
{
    //返回一个值给main_cpp以判断是否成功输入密码
    QDialog::reject();
}
