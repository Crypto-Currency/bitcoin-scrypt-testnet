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

string rdBlockType;
string rdVoteNum;
string rdChoicesEnabled;
string rdQuestion;
string rdChoice1;
string rdChoice2;
string rdChoice3;
string rdChoice4;
string rdChoice5;

string wrBlockType;
string wrVoteNum;
string wrChoicesEnabled;
string wrQuestion;
string wrChoice1;
string wrChoice2;
string wrChoice3;
string wrChoice4;
string wrChoice5;

ReadData rd;

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
  memcpy(&rd,bdataread,160);
int cnt=3;
rd.ChoicesEnabled[0]=cnt;

rd.BlockType[0]=3;

//d.VoteNum=VoteNum.c_str();
rdVoteNum="00000002";
strncpy ((char*) rd.VoteNum,rdVoteNum.c_str(),8);


//AnsiString RQcalling=(char*)Header.calling;
string mess;
mess=boost::lexical_cast<string>(rd.VoteNum);
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
  strncpy ((char*) rd.Question,mess.c_str(),100);

  mess="1st choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) rd.Choice1,mess.c_str(),10);


mess="2nd choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) rd.Choice2,mess.c_str(),10);

mess="3rd choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) rd.Choice3,mess.c_str(),10);

mess="4th choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) rd.Choice4,mess.c_str(),10);

mess="5th choice";
  for (int t=mess.length();t<10;t++)
  {
    mess=mess+" ";
  }
  strncpy ((char*) rd.Choice5,mess.c_str(),10);

rdQuestion=(char*)rd.Question;
rdQuestion.resize(100);
rdVoteNum=(char*)rd.VoteNum;
rdVoteNum.resize(8);
rdChoicesEnabled=(char*)rd.ChoicesEnabled;
rdChoicesEnabled.resize(1);
rdChoice1=(char*)rd.Choice1;
rdChoice1.resize(10);
rdChoice2=(char*)rd.Choice2;
rdChoice2.resize(10);
rdChoice3=(char*)rd.Choice3;
rdChoice3.resize(10);
rdChoice4=(char*)rd.Choice4;
rdChoice4.resize(10);
rdChoice5=(char*)rd.Choice5;
rdChoice5.resize(10);

printf("rd.VoteNum %s \nrd.Question %s\n\n",rdVoteNum.c_str(),rdQuestion.c_str());
printf("rd :\n%s\n",&rd);

  ui->Qnum->setText(rdVoteNum.c_str());
  ui->questionString->setText(rdQuestion.c_str());
  ui->CB1->setText(rdChoice1.c_str());
  ui->CB2->setText(rdChoice2.c_str());
  ui->CB3->setText(rdChoice3.c_str());
  ui->CB4->setText(rdChoice4.c_str());
  ui->CB5->setText(rdChoice5.c_str());

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
//  dlg.exec();

//QString result;
  if (dlg.exec() == QDialog::Accepted)
  {
//    result = dlg->selectedFile();
//    workingDirectory = dlg->url();
    printf("accepted is true\n");
printf(" block type %s\n",wrBlockType.c_str());
printf("%s %s\n",wrVoteNum.c_str(),wrQuestion.c_str());
printf("1 %s\n",wrChoice1.c_str());
printf("2 %s\n",wrChoice2.c_str());
printf("3 %s\n",wrChoice3.c_str());
printf("4 %s\n",wrChoice4.c_str());
printf("5 %s\n",wrChoice5.c_str());

  }
  else
  {
    printf("accepted is false\n");
  }

}


