#include "outdatecargodialog.h"
#include "ui_outdatecargodialog.h"
#include "connection.h"
#include<QMessageBox>
#include <QSqlError>
outDateCargoDialog::outDateCargoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outDateCargoDialog)
{
    //同mainwindow当中一样
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();
    ui->setupUi(this);
    outDateModel=new QSqlTableModel(this);
    outDateModel->setTable("cargo");
    outDateModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//对数据的改变会暂时储存在缓存中，直到调用submit函数
    outDateModel->setFilter(QString("(year= %1 and month < %2) or (year < %1)").arg(systemYear).arg(systemMonth));//判断是否已经过期
    outDateModel->select();//选取整个表的所有行
    ui->outDateTabel->setModel(outDateModel);
}

outDateCargoDialog::~outDateCargoDialog()
{
    delete ui;
}

void outDateCargoDialog::on_cancelBtn_clicked()
{
    this->close();
}

void outDateCargoDialog::on_renewBtn_clicked()
{
    //同步
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();
    outDateModel->setFilter(QString("(year=%1 and month <%2) or (year<%1)")
                            .arg(systemYear).arg(systemMonth));
    outDateModel->select();//选取整个表的所有行
    ui->outDateTabel->setModel(outDateModel);
}

void outDateCargoDialog::on_pushButton_clicked()
{
    //同mainwidow中的delete一样
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();//获取系统时间方便之后的同步
    int curRow = ui->outDateTabel->currentIndex().row();
    outDateModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                  tr("您确定删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        outDateModel->revertAll();
    }
    else outDateModel->submitAll();
}




