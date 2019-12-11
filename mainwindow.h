#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlTableModel>
#include <QMainWindow>
#include "QTime"
#include"solddialog.h"
#include"outdatecargodialog.h"
#include"helperdialog.h"
#include"sellviewdialog.h"
#include"logindialog.h"
#include"guidedialog.h"
#include"changecodedialog.h"
#pragma execution_character_set("utf-8")//设定读取文件所用编码，防止中文乱码出现
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_newBtn_clicked();

    void on_cancelBtn_clicked();

    void on_resetBtn_clicked();

    void on_deleteButton_clicked();

    void on_sellButton_clicked();

    void on_renewBtn_clicked();

    void on_assginBtn_clicked();

    void on_rollBackBtn_clicked();

    void on_viewOutDateCargo_clicked();

    void on_helperBtn_clicked();

    void on_viewSellBtn_clicked();

    void on_guidBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //建设几个Dialog类以调用各Dialog
    soldDialog solddialog;//倘若放在on_sellButton_clicked()函数中，则函数完成的同时删除该对象，界面也就消失，具体就像是一闪而逝,另外改为指针会造成程序异常闪退，原因未知
    outDateCargoDialog outDateCargoDialog;
    helperDialog helpDialog;
    sellViewDialog sellDialog;
    //建立模型类
    QSqlTableModel *cargoviewmodel;//倘若只添加在main.cpp的构造函数中,则on_Btn_clicked函数无法调用该模型
    QSqlQueryModel *cargoModel = new QSqlQueryModel(this);//同上
    QSqlQueryModel *timeModel = new QSqlQueryModel(this);//获取时间
    //建立dialog类
    guideDialog gDialog;
    changeCodeDialog changeDialog;
};

#endif // MAINWINDOW_H
