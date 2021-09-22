#include "filetrandialog.h"
#include "ui_filetrandialog.h"

FileTranDialog::FileTranDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileTranDialog)
{
    ui->setupUi(this);
}

FileTranDialog::~FileTranDialog()
{
    delete ui;
}
