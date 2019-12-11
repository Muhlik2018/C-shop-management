#include "solddialog.h"
#include "ui_solddialog.h"
#include "connection.h"
#include<QMessageBox>
soldDialog::soldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::soldDialog)
{
    ui->setupUi(this);
    cargoModel->setQuery("select name from cargo ");
    ui->comboBox->setModel(cargoModel);
}

soldDialog::~soldDialog()
{
    delete ui;
}

void soldDialog::on_quitBtn_clicked()
{
    this->close();
}

void soldDialog::on_confirmBtn_clicked()
{
    //获取系统当前时间，并在之后作为出售清单类的时间数据保存
    //自动获取出售商品的名称 价格 出售数量 并计算利润
    int tempid=0;
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    QSqlQuery tempQuery;
    tempQuery.first();
    QString tempName=ui->comboBox->currentText();
    int tempAmount=ui->numLabel->text().toInt();
    int amountToSell= ui->amountEdit->text().toInt();
    int tempPrice=ui->priceLabel->text().toInt();
    int newAmount = tempAmount-amountToSell;
    qDebug()<<newAmount;
    tempQuery.exec(QString ("update cargo set amount = %1 where name = '%2' ").arg(newAmount).arg(tempName));
    int tempProfile = tempPrice*amountToSell;

    //开始出售,实质是更新表单内容
    QSqlQuery tempQueryForSell;
    tempQueryForSell.prepare("select max(id) from sell");
    if(!tempQueryForSell.exec())
    {
        qDebug()<<tempQueryForSell.lastError();
    }
    else
    {
        while(tempQueryForSell.next())
        {
            tempid=tempQueryForSell.value(0).toInt();
            qDebug()<<QString("max id: %1").arg(tempid);
        }

    }
    tempid++;
    tempQueryForSell.prepare("insert into sell values(?, ?, ?, ?, ?, ?, ?)");
    tempQueryForSell.bindValue(0,tempid);
    tempQueryForSell.bindValue(1,tempName);
    tempQueryForSell.bindValue(2,tempPrice);
    tempQueryForSell.bindValue(3,amountToSell);
    tempQueryForSell.bindValue(4,tempProfile);
    tempQueryForSell.bindValue(5,systemYear);
    tempQueryForSell.bindValue(6,systemMonth);
    tempQueryForSell.exec();
    QMessageBox::information(this,tr("已出售"),
                                      tr("已成功出售"),QMessageBox::Ok);


}

void soldDialog::on_comboBox_activated(const QString &arg1)
{
    QSqlQuery tempQuery;
    QSqlQuery tempQuery2;
    tempQuery.first();

    if(arg1=="请选择商品")
    {
        ui->numLabel->clear();
        ui->priceLabel->clear();
    }
    else
    {
      tempQuery.exec(QString ("select amount from cargo where name = '%1' ").arg(arg1));
      tempQuery.first();
      int amount=tempQuery.value(0).toInt();
       qDebug()<<amount;
       ui->numLabel->setNum(amount);
       tempQuery2.exec(QString ("select price from cargo where name = '%1' ").arg(arg1));
       tempQuery2.first();
       int price=tempQuery2.value(0).toInt();
       ui->priceLabel->setNum(price);
    }



}

void soldDialog::on_renewButton_clicked()
{
    cargoModel->setQuery("select name from cargo ");
    ui->comboBox->setModel(cargoModel);
}
