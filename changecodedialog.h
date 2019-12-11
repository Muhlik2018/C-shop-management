#ifndef CHANGECODEDIALOG_H
#define CHANGECODEDIALOG_H

#include <QDialog>
#pragma execution_character_set("utf-8")//设定读取文件所用编码，防止中文乱码出现
namespace Ui {
class changeCodeDialog;
}

class changeCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeCodeDialog(QWidget *parent = nullptr);
    ~changeCodeDialog();

private slots:
    void on_cancelBtn_clicked();

    void on_renewBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::changeCodeDialog *ui;
};

#endif // CHANGECODEDIALOG_H
