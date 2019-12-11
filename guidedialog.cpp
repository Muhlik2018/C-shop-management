#include "guidedialog.h"
#include "ui_guidedialog.h"

guideDialog::guideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guideDialog)
{
    ui->setupUi(this);
}

guideDialog::~guideDialog()
{
    delete ui;
}

void guideDialog::on_cancelBtn_clicked()
{
    this->close();
}
