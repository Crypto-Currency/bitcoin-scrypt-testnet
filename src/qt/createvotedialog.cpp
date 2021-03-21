#include "createvotedialog.h"
#include "ui_createvotedialog.h"
#include "clientmodel.h"

#include "version.h"

CreateVoteDialog::CreateVoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVoteDialog)
{
    ui->setupUi(this);
}

void CreateVoteDialog::setModel(ClientModel *model)
{
    if(model)
    {
        ui->versionLabel->setText(model->formatFullVersion());
    }
}

CreateVoteDialog::~CreateVoteDialog()
{
    delete ui;
}

void CreateVoteDialog::on_buttonBox_accepted()
{
    close();
}
