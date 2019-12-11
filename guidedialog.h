#ifndef GUIDEDIALOG_H
#define GUIDEDIALOG_H

#include <QDialog>

namespace Ui {
class guideDialog;
}

class guideDialog : public QDialog
{
    Q_OBJECT

public:
    explicit guideDialog(QWidget *parent = nullptr);
    ~guideDialog();

private slots:
    void on_cancelBtn_clicked();

private:
    Ui::guideDialog *ui;
};

#endif // GUIDEDIALOG_H
