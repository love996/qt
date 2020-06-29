#ifndef VERIFICATIONDIALOG_H
#define VERIFICATIONDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class VerificationDialog; }
QT_END_NAMESPACE

class VerificationDialog : public QDialog
{
    Q_OBJECT

public:
    VerificationDialog(QWidget *parent = nullptr);
    ~VerificationDialog();

private:
    Ui::VerificationDialog *ui;
};
#endif // VERIFICATIONDIALOG_H
