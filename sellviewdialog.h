#ifndef SELLVIEWDIALOG_H
#define SELLVIEWDIALOG_H
#include <QSqlTableModel>
#include <QDialog>
#include "QTime"
#pragma execution_character_set("utf-8")//设定读取文件所用编码，防止中文乱码出现
namespace Ui {
class sellViewDialog;
}

class sellViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sellViewDialog(QWidget *parent = nullptr);
    ~sellViewDialog();

private slots:
    void on_cancelBtn_clicked();
    void on_revertBtn_clicked();

    void on_delteBtn_clicked();

    void on_renewBtn_clicked();

private:
    Ui::sellViewDialog *ui;
    //建立模型类
    QSqlTableModel *sellviewmodel;
};

#endif // SELLVIEWDIALOG_H
