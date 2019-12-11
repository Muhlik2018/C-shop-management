#ifndef OUTDATECARGODIALOG_H
#define OUTDATECARGODIALOG_H
#include <QSqlTableModel>
#include <QDialog>
#pragma execution_character_set("utf-8")//设定读取文件所用编码，防止中文乱码出现
namespace Ui {
class outDateCargoDialog;
}

class outDateCargoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit outDateCargoDialog(QWidget *parent = nullptr);
    ~outDateCargoDialog();

private slots:
    void on_cancelBtn_clicked();

    void on_renewBtn_clicked();

    void on_pushButton_clicked();



private:
    Ui::outDateCargoDialog *ui;
    //建立模型类
     QSqlTableModel *outDateModel;
};

#endif // OUTDATECARGODIALOG_H
