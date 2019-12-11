#ifndef HELPERDIALOG_H
#define HELPERDIALOG_H

#include <QDialog>

namespace Ui {
class helperDialog;
}

class helperDialog : public QDialog
{
    Q_OBJECT

public:
    explicit helperDialog(QWidget *parent = nullptr);
    ~helperDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::helperDialog *ui;
};

#endif // HELPERDIALOG_H
