#include "helperdialog.h"
#include "ui_helperdialog.h"

helperDialog::helperDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helperDialog)
{
    ui->setupUi(this);
}

helperDialog::~helperDialog()
{
    delete ui;
}

void helperDialog::on_pushButton_clicked()
{
    this->close();
}
