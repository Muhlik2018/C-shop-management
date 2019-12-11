#ifndef SOLDDIALOG_H
#define SOLDDIALOG_H
#include <QSqlTableModel>
#include <QDialog>
#pragma execution_character_set("utf-8")//设定读取文件所用编码，防止中文乱码出现
namespace Ui {
class soldDialog;
}

class soldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit soldDialog(QWidget *parent = nullptr);
    ~soldDialog();

private slots:
    void on_quitBtn_clicked();

    void on_confirmBtn_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_renewButton_clicked();

private:
    Ui::soldDialog *ui;
    //建立模型类
    QSqlQueryModel *cargoModel = new QSqlQueryModel(this);
};

#endif // SOLDDIALOG_H
