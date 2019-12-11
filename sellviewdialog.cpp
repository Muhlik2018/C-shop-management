#include "sellviewdialog.h"
#include "ui_sellviewdialog.h"
#include<QMessageBox>
sellViewDialog::sellViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sellViewDialog)
{
    ui->setupUi(this);
    //同mainwindow
    sellviewmodel = new QSqlTableModel(this);
    sellviewmodel->setTable("sell");
    sellviewmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);//对数据的改变会暂时储存在缓存中，直到调用submit函数
    sellviewmodel->select();
    ui->tableView->setModel(sellviewmodel);
}

sellViewDialog::~sellViewDialog()
{
    delete ui;
}

void sellViewDialog::on_cancelBtn_clicked()
{
    this->close();
}



void sellViewDialog::on_revertBtn_clicked()
{
    sellviewmodel->revertAll();
}

void sellViewDialog::on_delteBtn_clicked()
{
    int curRow = ui->tableView->currentIndex().row();

    sellviewmodel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                  tr("您确定删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        sellviewmodel->revertAll();
    }
    else sellviewmodel->submitAll();
}

void sellViewDialog::on_renewBtn_clicked()
{
    sellviewmodel->setTable("sell");
    sellviewmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    sellviewmodel->select();
    ui->tableView->setModel(sellviewmodel);
}
