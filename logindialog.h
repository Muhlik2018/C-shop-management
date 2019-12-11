#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QSqlTableModel>
#include <QDialog>
#pragma execution_character_set("utf-8")//设定读取文件所用编码，防止中文乱码出现
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
