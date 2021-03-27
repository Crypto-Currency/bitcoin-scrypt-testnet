#include "createvotedialog.h"
#include "ui_createvotedialog.h"
#include "clientmodel.h"
#include "votepage.h"

#include <string>
#include "boost/lexical_cast.hpp"

#include "version.h"

using namespace std;

extern string VoteNum;
extern string Question;
extern string Choice1;
extern string Choice2;
extern string Choice3;
extern string Choice4;
extern string Choice5;



CreateVoteDialog::CreateVoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVoteDialog)
{
    ui->setupUi(this);

  connect(ui->SendButton, SIGNAL(clicked(bool)), this, SLOT(on_SendButton_clicked()));
  connect(ui->RefreshButton, SIGNAL(clicked(bool)), this, SLOT(on_RefreshButton_clicked()));

  int vnum=boost::lexical_cast<int>(VoteNum.c_str());
  vnum++;
  string mess=boost::to_string(vnum);
  for (int t=mess.length();t<8;t++)
  {
    mess="0"+mess;
  }

  ui->Qnum->setText(mess.c_str());
}


CreateVoteDialog::~CreateVoteDialog()
{
    delete ui;
}

void CreateVoteDialog::on_SendButton_clicked()
{
// do stuff
    close();
}

void CreateVoteDialog::on_RefreshButton_clicked()
{
  ui->view->reload();
}

