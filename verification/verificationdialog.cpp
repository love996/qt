#include "verificationdialog.h"
#include "ui_verificationdialog.h"

VerificationDialog::VerificationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerificationDialog)
{
    ui->setupUi(this);
}

VerificationDialog::~VerificationDialog()
{
    delete ui;
}

