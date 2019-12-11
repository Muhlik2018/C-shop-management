#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"connection.h"
#include<QMessageBox>
#include <QSqlError>
#include <QSplashScreen>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //开头动画
    QPixmap pixmap("screen.png");
    QSplashScreen screen(pixmap);
    screen.show();
    screen.showMessage("胡辰昕的小商店管理系统", Qt::AlignCenter, Qt::red);
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
       do
    {
           now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=2);

    //获取系统当前时间，以完成之后outDateBox中的判断
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();
    qDebug()<<systemYear;
    ui->setupUi(this);

    //添加即将售罄商品清单
    cargoModel->setQuery("select name from cargo where amount<=5");
    ui->comboBox->setModel(cargoModel);

    //向tabelview添加模型以显示
    cargoviewmodel = new QSqlTableModel(this);
    cargoviewmodel->setTable("cargo");
    cargoviewmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);//对数据的改变会暂时储存在缓存中，直到调用submit函数
    cargoviewmodel->select();//选取整个表的所有行

    //outDateBox的判断
    ui->cargoTableView->setModel(cargoviewmodel);
    timeModel->setQuery(QString ("select name from cargo where year = %1 and( month = %2 +1)").arg(systemYear).arg(systemMonth));
    ui->timeCombox->setModel(timeModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_newBtn_clicked()
{
    //获取系统时间方便之后的同步
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();

    //获取用户输入的各项值以便添加
    QString tempName= ui->nameEdit->text();
    int tempAmount = ui->amountEdit->text().toInt();
    int tempPrice=ui->priceEdit->text().toInt();
    int tempYear = ui->yearEdit->text().toInt();
    int tempMonth = ui->monthEdit->text().toInt();
    int tempDay = ui->dayEdit->text().toInt();
    int tempid=0;

    //开始添加
    QSqlQuery query;

    //获取最大id
    query.prepare("select max(id) from cargo");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    else
    {
        while(query.next())
        {
            tempid=query.value(0).toInt();
            qDebug()<<QString("max id: %1").arg(tempid);
        }

    }
    tempid++;
    query.prepare("insert into cargo values(?,?,?,?,?,?,?)");
    query.bindValue(0,tempid);
    query.bindValue(1,tempName);
    query.bindValue(2,tempPrice);
    query.bindValue(3,tempAmount);
    query.bindValue(4,tempYear);
    query.bindValue(5,tempMonth);
    query.bindValue(6,tempDay);
    query.exec();

    //刷新各model数据
    cargoviewmodel->setTable("cargo");
    cargoviewmodel->select();
    ui->cargoTableView->setModel(cargoviewmodel);
    cargoModel->setQuery("select name from cargo where amount<=5");
    ui->comboBox->setModel(cargoModel);
    timeModel->setQuery(QString ("select name from cargo where year = %1 and( month = %2 +1)").arg(systemYear).arg(systemMonth));
    ui->timeCombox->setModel(timeModel);
    QMessageBox::information(this,tr("已添加"),
                                      tr("已成功添加"),QMessageBox::Ok);
}

void MainWindow::on_cancelBtn_clicked()
{
        this->close();
}

void MainWindow::on_resetBtn_clicked()
{
    //删除所有除defaultData之外的数据
    QSqlQuery tempQuery;
    tempQuery.prepare("delete from cargo where id !=0");
    QSqlQuery tempQuery_2;
    tempQuery_2.prepare("delete from sell where id != 0");
    int ok = QMessageBox::warning(this,tr("删除所有！"),
                                  tr("您确定删除所有吗？删除后将关闭程序"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::No)
        return;
    else
    {
        if(!tempQuery.exec()||!tempQuery_2.exec())
    {
        qDebug()<<tempQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
        this->close();

    }
    }
}


void MainWindow::on_deleteButton_clicked()
{
    //获取系统时间方便之后的同步
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();

    //获取当前行并删除
    int curRow = ui->cargoTableView->currentIndex().row();
    qDebug()<<curRow;
    cargoviewmodel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                  tr("您确定删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        cargoviewmodel->revertAll();
    }
    else cargoviewmodel->submitAll();


    //同步信息
    cargoviewmodel->setTable("cargo");
    cargoviewmodel->select();
    ui->cargoTableView->setModel(cargoviewmodel);
    cargoModel->setQuery("select name from cargo where amount<=5");//将信息同步到两个combox中
    ui->comboBox->setModel(cargoModel);
    timeModel->setQuery(QString ("select name from cargo where year = %1 and( month = %2 +1)").arg(systemYear).arg(systemMonth));
    ui->timeCombox->setModel(timeModel);
}

void MainWindow::on_sellButton_clicked()
{
    //获取时间
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();//获取系统时间方便之后的同步
    solddialog.show();

    //同步信息
    cargoviewmodel->setTable("cargo");
    cargoviewmodel->select();
    ui->cargoTableView->setModel(cargoviewmodel);
    cargoModel->setQuery("select name from cargo where amount<=5");
    ui->comboBox->setModel(cargoModel);
    timeModel->setQuery(QString ("select name from cargo where year = %1 and( month = %2 +1)").arg(systemYear).arg(systemMonth));
    ui->timeCombox->setModel(timeModel);//重新设定model以保持同步
}

void MainWindow::on_renewBtn_clicked()
{
    //获取系统时间方便之后的同步
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();


    cargoviewmodel->setTable("cargo");
    cargoviewmodel->select();
    ui->cargoTableView->setModel(cargoviewmodel);
    cargoModel->setQuery("select name from cargo where amount<=5");
    ui->comboBox->setModel(cargoModel);
    timeModel->setQuery(QString ("select name from cargo where year = %1 and( month = %2 +1)").arg(systemYear).arg(systemMonth));
    ui->timeCombox->setModel(timeModel);//重新设定model以保持同步
}

void MainWindow::on_assginBtn_clicked()
{
    //提交所做的修改
    cargoviewmodel->database().transaction();
    if(cargoviewmodel->submitAll())
    {
        cargoviewmodel->database().commit();
    }
    else
    {
        cargoviewmodel->database().rollback();
        QMessageBox::warning(this, tr("tableModel"),
                                     tr("数据库错误: %1")
                                     .arg(cargoviewmodel->lastError().text()));//如果无法提交则报错
    }


    //同步
    QDate systemDate;
    systemDate=QDate::currentDate();
    int systemYear=systemDate.year();
    int systemMonth=systemDate.month();
    int systemDay= systemDate.day();
    cargoModel->setQuery("select name from cargo where amount<=5");
    ui->comboBox->setModel(cargoModel);
    timeModel->setQuery(QString ("select name from cargo where year = %1 and( month = %2 +1)").arg(systemYear).arg(systemMonth));
    ui->timeCombox->setModel(timeModel);
}

void MainWindow::on_rollBackBtn_clicked()
{
    //撤回修改
    cargoviewmodel->revertAll();
}

void MainWindow::on_viewOutDateCargo_clicked()
{
    outDateCargoDialog.show();
}

void MainWindow::on_helperBtn_clicked()
{
    helpDialog.show();
}

void MainWindow::on_viewSellBtn_clicked()
{
    sellDialog.show();
}

void MainWindow::on_guidBtn_clicked()
{
    gDialog.show();
}

void MainWindow::on_pushButton_clicked()
{
    changeDialog.show();
}
