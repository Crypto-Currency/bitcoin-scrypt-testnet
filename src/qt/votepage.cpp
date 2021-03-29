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
WriteData wr;
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
  if (dlg.exec() == QDialog::Accepted)
  {
    buffWRblock();  // add spaces to fill

    string mess;
unsigned char temp[160];
//mess=boost::lexical_cast<string>(wr.BlockType); // yes, nasty
  memcpy(temp,&wr,160);

//debug
printf("\nstart dump:\n");
HexDump(temp,160); 
printf("\nend dump\n\n");
printf("temp is:\n|%s|\n",temp);
  }
  else
  {
    printf("accepted is false\n");
  }

}

//---------------------------------------------------------------------------
void VotePage::HexDump(unsigned char* pBuffer, int size)
{
  printf("\nHexDump output:%d  chars [0x%s]\n",size,IntToHex(size,2).c_str());
  string c;
  c="      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n";
  printf(c.c_str());
  c="----  -----------------------------------------------------------------\n";
  printf(c.c_str());

  for(int i=0;i<size;i=i+16)
  {
    c=IntToHex(i,4)+" ";
    for(int tt=0;tt<16;tt++)
    {
      if(tt+i<size)
      {
        unsigned char cc =int(pBuffer[i+tt]);
        c=c+" "+IntToHex(int(cc),2);
      }
      else
        c=c+"   ";  
    }
    c=c+"  ";
    for(int tt=0;tt<16;tt++)
    {
      if(tt+i<size)
      {
        char cc = int(pBuffer[i+tt]);
        if(cc <32)
          cc=46; // make it a dot
        c=c+cc;
      }  
    }
    c=c+"\n";
  printf(c.c_str());
  c="";
  }
  printf(c.c_str());
  c="-----------------------------------------------------------------------";
  printf(c.c_str());
}

//---------------------------------------------------------------------------
string VotePage::IntToHex(int a,int s)
{//left pad
  string hex;
  char hex_char[4];
  sprintf(hex_char,"%X",a);
  hex=hex_char;
  for(int t=hex.length();t<s;t++)
  {
    hex=" "+hex;
  }
  return(hex);
}

void VotePage::buffWRblock()
{
  string mess;

  mess=wrBlockType.c_str();
  mess.resize(1);
  strncpy ((char*) wr.BlockType,mess.c_str(),1);

 mess=wrVoteNum.c_str();
  for (int t=mess.length();t<=8;t++)
  {
    mess=mess+" ";
  }
  mess.resize(8);
  strncpy ((char*) wr.VoteNum,mess.c_str(),8);

  mess=wrQuestion.c_str();
  for (int t=mess.length();t<=100;t++)
  {
    mess=mess+" ";
  }
  mess.resize(100);
  strncpy ((char*) wr.Question,mess.c_str(),100);

  mess=wrChoicesEnabled.c_str();
  mess.resize(1);
  strncpy ((char*) wr.ChoicesEnabled,mess.c_str(),1);

  mess=wrChoice1.c_str();
  for (int t=mess.length();t<=10;t++)
  {
    mess=mess+" ";
  }
  mess.resize(10);
  strncpy ((char*) wr.Choice1,mess.c_str(),10);

  mess=wrChoice2.c_str();
  for (int t=mess.length();t<=10;t++)
  {
    mess=mess+" ";
  }
  mess.resize(10);
  strncpy ((char*) wr.Choice2,mess.c_str(),10);

  mess=wrChoice3.c_str();
  for (int t=mess.length();t<=10;t++)
  {
    mess=mess+" ";
  }
  mess.resize(10);
  strncpy ((char*) wr.Choice3,mess.c_str(),10);

  mess=wrChoice4.c_str();
  for (int t=mess.length();t<=10;t++)
  {
    mess=mess+" ";
  }
  mess.resize(10);
  strncpy ((char*) wr.Choice4,mess.c_str(),10);

  mess=wrChoice5.c_str();
  for (int t=mess.length();t<=10;t++)
  {
    mess=mess+" ";
  }
  mess.resize(10);
  strncpy ((char*) wr.Choice5,mess.c_str(),10);

}
