#include <QSettings>
#include <string>
#include <QMainWindow>
#include <QMessageBox>

#include "boost/lexical_cast.hpp"

#include "votepage.h"
#include "ui_votepage.h"
#include "util.h"
#include "bitcoingui.h"
#include "createvotedialog.h"
#include "clientmodel.h"
#include "ui_interface.h"

extern BitcoinGUI *guiref;

#include <QDebug>
using namespace std;

string BlockType;
string VoteNum;
string ChoicesEnabled;
string Question;
string Choice1;
string Choice2;
string Choice3;
string Choice4;
string Choice5;

ReadData d;

VotePage::VotePage(QWidget *parent) : QWidget(parent), ui(new Ui::VotePage)
{
  ui->setupUi(this);
//  ui->CreateButton->setVisible(false);

  connect(ui->CB1, SIGNAL(clicked(bool)), this, SLOT(on_CB1_clicked()));
  connect(ui->CB2, SIGNAL(clicked(bool)), this, SLOT(on_CB2_clicked()));
  connect(ui->CB3, SIGNAL(clicked(bool)), this, SLOT(on_CB3_clicked()));
  connect(ui->CB4, SIGNAL(clicked(bool)), this, SLOT(on_CB4_clicked()));
  connect(ui->CB5, SIGNAL(clicked(bool)), this, SLOT(on_CB5_clicked()));
  connect(ui->SendButton, SIGNAL(clicked(bool)), this, SLOT(on_SendButton_clicked()));
  connect(ui->RefreshButton, SIGNAL(clicked(bool)), this, SLOT(on_RefreshButton_clicked()));

char bdataread[]="000000001This would allow the BTCS wallet client to enable users to send messages to other BTCS wallets in a completely decentralized and censorship free manner world-wide.";

//  ReadData data;
  memcpy(&d,bdataread,160);
int cnt=3;
d.ChoicesEnabled[0]=cnt;

d.BlockType[0]=3;

//d.VoteNum=VoteNum.c_str();
VoteNum="00000002";
strncpy ((char*) d.VoteNum,VoteNum.c_str(),8);


//AnsiString RQcalling=(char*)Header.calling;
string mess;
mess=boost::lexical_cast<string>(d.VoteNum);
mess.resize(8);
  for (int t=mess.length();t<8;t++)
  {
    mess=mess+" ";
  }
//string mess="this is question number "+boost::lexical_cast<string>(d.VoteNum);//d.Question;
  mess="this is question number "+mess;//d.Question;
  for (int t=mess.length();t<100;t++)
  {
    mess=mess+" ";
  }
printf("question mess= |%s|\n",mess.c_str());
  strncpy ((char*) d.Question,mess.c_str(),100);

  mess="1st choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) d.Choice1,mess.c_str(),10);


mess="2nd choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) d.Choice2,mess.c_str(),10);

mess="3rd choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) d.Choice3,mess.c_str(),10);

mess="4th choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) d.Choice4,mess.c_str(),10);

mess="5th choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) d.Choice5,mess.c_str(),10);

Question=(char*)d.Question;
Question.resize(100);
VoteNum=(char*)d.VoteNum;
VoteNum.resize(8);
ChoicesEnabled=(char*)d.ChoicesEnabled;
Choice1=(char*)d.Choice1;
Choice2=(char*)d.Choice2;
Choice3=(char*)d.Choice3;
Choice4=(char*)d.Choice4;
Choice5=(char*)d.Choice5;

printf("d.VoteNum %s \nd.Question %s\n",VoteNum.c_str(),Question.c_str());

  ui->Qnum->setText(VoteNum.c_str());
  ui->questionString->setText(Question.c_str());
  ui->CB1->setText(Choice1.c_str());
  ui->CB2->setText(Choice2.c_str());
  ui->CB3->setText(Choice3.c_str());
  ui->CB4->setText(Choice4.c_str());
  ui->CB5->setText(Choice5.c_str());

}

VotePage::~VotePage()
{
  delete ui;
}

void VotePage::on_CB1_clicked()
{
  ui->CB1->setChecked(true);
  ui->CB2->setChecked(false);
  ui->CB3->setChecked(false);
  ui->CB4->setChecked(false);
  ui->CB5->setChecked(false);
}

void VotePage::on_CB2_clicked()
{
  ui->CB1->setChecked(false);
  ui->CB2->setChecked(true);
  ui->CB3->setChecked(false);
  ui->CB4->setChecked(false);
  ui->CB5->setChecked(false);
}

void VotePage::on_CB3_clicked()
{
  ui->CB1->setChecked(false);
  ui->CB2->setChecked(false);
  ui->CB3->setChecked(true);
  ui->CB4->setChecked(false);
  ui->CB5->setChecked(false);
}

void VotePage::on_CB4_clicked()
{
  ui->CB1->setChecked(false);
  ui->CB2->setChecked(false);
  ui->CB3->setChecked(false);
  ui->CB4->setChecked(true);
  ui->CB5->setChecked(false);
}

void VotePage::on_CB5_clicked()
{
  ui->CB1->setChecked(false);
  ui->CB2->setChecked(false);
  ui->CB3->setChecked(false);
  ui->CB4->setChecked(false);
  ui->CB5->setChecked(true);
}

void VotePage::on_SendButton_clicked()
{
  QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm your vote"),
    tr("Are you sure you want to submit your chioce?"),
    QMessageBox::Yes|QMessageBox::Cancel,
    QMessageBox::Cancel);

  if(retval != QMessageBox::Yes)
  {
    return;
  }
  // continue if true

}

void VotePage::on_RefreshButton_clicked()
{
  ui->view->reload();
}

void VotePage::on_CreateButton_clicked()
{
  CreateVoteDialog dlg;
  dlg.exec();
}


