#include "changecodedialog.h"
#include "ui_changecodedialog.h"
#include"connection.h"
#include<QMessageBox>
changeCodeDialog::changeCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeCodeDialog)
{
    ui->setupUi(this);
}

changeCodeDialog::~changeCodeDialog()
{
    delete ui;
}

void changeCodeDialog::on_cancelBtn_clicked()
{
    this->close();
}

void changeCodeDialog::on_renewBtn_clicked()
{
    //获取密码并显示在label上
    QSqlQuery tempQuery;
    tempQuery.exec("select pwd from password where id = 0");
    tempQuery.first();
    QString pwd=tempQuery.value(0).toString();
    ui->codeLabel->setText(pwd);
}

void changeCodeDialog::on_confirmBtn_clicked()
{
    //更改密码，具体注释见soldout的soldBtn有关函数
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("请输入密码"),tr("请输入密码再修改！"),QMessageBox::Ok);
        ui->lineEdit->setFocus();
    }
    else
    {
    QString newPassword=ui->lineEdit->text();
    QSqlQuery tempQuery;
    tempQuery.exec(QString ("update password set pwd = %1 where id = 0 ").arg(newPassword));
    QMessageBox::information(this,tr("已修改"),
                                      tr("已成功修改"),QMessageBox::Ok);
    }
}
