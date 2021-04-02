#include <QSettings>
#include <string>
#include <QMainWindow>
#include <QMessageBox>


#include "boost/lexical_cast.hpp"
#include <json_spirit.h>
#include "votepage.h"
#include "ui_votepage.h"
#include "util.h"
#include "bitcoingui.h"
#include "bitcoinrpc.h"
#include "createvotedialog.h"
#include "clientmodel.h"
#include "ui_interface.h"
#include "rpcconsole.h"

#include "optionsmodel.h"
#include "walletmodel.h"

#include <QDebug>
using namespace std;
using namespace json_spirit;

extern BitcoinGUI *guiref;
extern Value createrawtransaction(const Array& params, bool fHelp);
extern Value signrawtransaction(const Array& params, bool fHelp);

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

string ans[6];

VotePage::VotePage(QWidget *parent) : QWidget(parent), ui(new Ui::VotePage)
{
  ui->setupUi(this);
//  ui->CreateButton->setVisible(false);

  connect(ui->CB1, SIGNAL(clicked(bool)), this, SLOT(on_CB1_clicked()));
  connect(ui->CB2, SIGNAL(clicked(bool)), this, SLOT(on_CB2_clicked()));
  connect(ui->CB3, SIGNAL(clicked(bool)), this, SLOT(on_CB3_clicked()));
  connect(ui->CB4, SIGNAL(clicked(bool)), this, SLOT(on_CB4_clicked()));
  connect(ui->CB5, SIGNAL(clicked(bool)), this, SLOT(on_CB5_clicked()));
  connect(ui->RefreshButton, SIGNAL(clicked(bool)), this, SLOT(on_RefreshButton_clicked()));


// ------------- this is temp stuff until we get some votes on the blockchain
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
  mess=SizeString(mess.c_str(),100);
  strncpy ((char*) rd.Question,mess.c_str(),100);

  ans[0]="no choice";
  mess="1st choice";
  mess=SizeString(mess.c_str(),10);
  strncpy ((char*) rd.Choice1,mess.c_str(),10);
  ans[1]=mess;

mess="2nd choice";
  mess=SizeString(mess.c_str(),10);
  strncpy ((char*) rd.Choice2,mess.c_str(),10);
  ans[2]=mess;

mess="3rd choice";
  mess=SizeString(mess.c_str(),10);
  strncpy ((char*) rd.Choice3,mess.c_str(),10);
  ans[3]=mess;

mess="4th choice";
  mess=SizeString(mess.c_str(),10);
  strncpy ((char*) rd.Choice4,mess.c_str(),10);
  ans[4]=mess;

mess="5th choice";
  mess=SizeString(mess.c_str(),10);
  strncpy ((char*) rd.Choice5,mess.c_str(),10);
  ans[5]=mess;

// debug - now we are reading back to double check
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


  ui->Qnum->setText(rdVoteNum.c_str());
  ui->questionString->setText(rdQuestion.c_str());
  ui->CB1->setText(rdChoice1.c_str());
  ui->CB2->setText(rdChoice2.c_str());
  ui->CB3->setText(rdChoice3.c_str());
  ui->CB4->setText(rdChoice4.c_str());
  ui->CB5->setText(rdChoice5.c_str());
//  end debug check

}

//---------------------------------------------------------------------------
VotePage::~VotePage()
{
  delete ui;
}

//---------------------------------------------------------------------------
void VotePage::on_CB1_clicked()
{
  ClearCBs();
  ui->CB1->setChecked(true);
}

//---------------------------------------------------------------------------
void VotePage::on_CB2_clicked()
{
  ClearCBs();
  ui->CB2->setChecked(true);
}

//---------------------------------------------------------------------------
void VotePage::on_CB3_clicked()
{
  ClearCBs();
  ui->CB3->setChecked(true);
}

//---------------------------------------------------------------------------
void VotePage::on_CB4_clicked()
{
  ClearCBs();
  ui->CB4->setChecked(true);
}

//---------------------------------------------------------------------------
void VotePage::on_CB5_clicked()
{
  ClearCBs();
  ui->CB5->setChecked(true);
}

//---------------------------------------------------------------------------
void VotePage::ClearCBs()
{
  ui->CB1->setChecked(false);
  ui->CB2->setChecked(false);
  ui->CB3->setChecked(false);
  ui->CB4->setChecked(false);
  ui->CB5->setChecked(false);
}

//---------------------------------------------------------------------------
int VotePage::getChoice()
{
  if(ui->CB1->isChecked())
    return(1);
  if(ui->CB2->isChecked())
    return(2);
  if(ui->CB3->isChecked())
    return(3);
  if(ui->CB4->isChecked())
    return(4);
  if(ui->CB5->isChecked())
    return(5);

  return(0);
}

//---------------------------------------------------------------------------
void VotePage::on_SendButton_clicked()
{
  int choice=getChoice();
  string choicenum=boost::lexical_cast<string>(choice);
  if(choice ==0)
  {
    uiInterface.ThreadSafeMessageBox(
      _("Confirm your vote:\nYou haven't made a selection yet"),
      _("Error"), CClientUIInterface::OK | CClientUIInterface::MODAL);
    return;
  }
  else
  {
    string ans_str=ans[choice];
    string mess ="Are you sure you want to submit answer #"+choicenum+"\n\""+ans[choice]+"\" as your choice?";
    QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm your vote"),
      tr(mess.c_str()), QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel);
    if(retval != QMessageBox::Yes)
    {
      return;
    }
  }
  
  // continue if true

  vector<string> temp=getunspent();
  if(temp.size() ==1)
  {// known error
    printf("error  %s\n",temp[0].c_str());
    printf("length %d\n",temp.size());
    uiInterface.ThreadSafeMessageBox(
      strprintf(_("Vote cast:\n"
                  "error %s\n"), temp[0].c_str()),
                _("Error"), CClientUIInterface::OK | CClientUIInterface::MODAL);
   }
  else
  if(temp.size() ==5)
  {
    printf("txid     %s\n",temp[0].c_str());
    printf("vout     %s\n",temp[1].c_str());
    printf("PubKey   %s\n",temp[2].c_str());
    printf("amount   %s\n",temp[3].c_str());
    printf("confirms %s\n",temp[4].c_str());

    string sValue=temp[3];
    sValue.insert(sValue.length()-8,".");
    double dvalue = boost::lexical_cast<double>(sValue.c_str());
    double change=dvalue-1;  //cost 1 coint to vote
    printf("svalue   %s\n",sValue.c_str());
    printf("dvalue   %f\n",dvalue);
    printf("change   %f\n",change);


// get an address that belongs to the wallet

cout <<"votepage : pubKey "<<temp[2]<<"\n";
string address=CBitcoinAddress(temp[2]).ToString();
//string address;

//CTxDestination dest =CBitcoinAddress(temp[2]).Get();


cout <<"votepage : Address "<<address<<"\n";

    CBitcoinAddress outaddress(address);
    if (!outaddress.IsValid())
    {
      cout <<"crap. now what ..."<<"\n";
      return;
    }


// build array
//    const Array& params;
string message="test message 03/30/2021";
//string address="mtRwEyanMyBdgHeTCUPyhQgMaaFmjYLk3N";
    Array param1;
    Array param2;
    Object obj1;
    Object obj2;

    int vout=boost::lexical_cast<int>(temp[1]);
    obj1.push_back(Pair("txid",temp[0]));
    obj1.push_back(Pair("vout",vout));
    param1.push_back(obj1);

    obj2.push_back(Pair("data",message));
    obj2.push_back(Pair(address,change));

    param2.push_back(param1);
    param2.push_back(obj2);
    Value createraw=createrawtransaction(param2,false);
    cout << json_spirit::write(createraw) <<"\n";

// createraw has the hex encoded raw transaction needed for next step - signrawtransaction

    Array param3;
    param3.push_back(createraw);
    Value signraw=signrawtransaction(param3,false);
cout << json_spirit::write(signraw) <<"\n";

// signraw has the hash needed for the next step - sendrawtransaction


//cout<<"stuff "<<write(stuff)<<"\n";
//    mObject obj3 = stuff.get_obj();
//    Object obj4 = obj3.find("complete")->second.get_obj();
//cout <<"complete is "<<json_spirit::write(obj4)<<"\n";

  }
  else
  {
    printf("unknown error  %s\n",temp[0].c_str());
    printf("vector length  %d\n",temp.size());

    string mess="unknown error "+temp[0];
    mess +="\nvector length "+boost::lexical_cast<string>(temp.size());
    mess+="\n\nyour vote was not cast";
    uiInterface.ThreadSafeMessageBox(
      strprintf(_("Vote cast:\n"
                  "%s\n"), mess.c_str()),
                _("Error"), CClientUIInterface::OK | CClientUIInterface::MODAL);
  }
  return;
}

//---------------------------------------------------------------------------
void VotePage::on_RefreshButton_clicked()
{
  ui->view->reload();
}

//---------------------------------------------------------------------------
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
void VotePage::HexDump(unsigned char* pBuffer, int size)         // temp dump
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
string VotePage::IntToHex(int a,int s)                           // temp dump
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

//---------------------------------------------------------------------------
void VotePage::buffWRblock()       // buff the strings and transfer to struct
{
  string mess;

  mess=SizeString(wrBlockType.c_str(),1);
  strncpy ((char*) wr.BlockType,mess.c_str(),1);

  mess=SizeString(wrVoteNum.c_str(),8);
  strncpy ((char*) wr.VoteNum,mess.c_str(),8);

  mess=SizeString(wrQuestion.c_str(),100);
  strncpy ((char*) wr.Question,mess.c_str(),100);

  mess=SizeString(wrChoicesEnabled.c_str(),1);
  strncpy ((char*) wr.ChoicesEnabled,mess.c_str(),1);

  mess=SizeString(wrChoice1.c_str(),10);
  strncpy ((char*) wr.Choice1,mess.c_str(),10);

  mess=SizeString(wrChoice2.c_str(),10);
  strncpy ((char*) wr.Choice2,mess.c_str(),10);

  mess=SizeString(wrChoice3.c_str(),10);
  strncpy ((char*) wr.Choice3,mess.c_str(),10);

  mess=SizeString(wrChoice4.c_str(),10);
  strncpy ((char*) wr.Choice4,mess.c_str(),10);

  mess=SizeString(wrChoice5.c_str(),10);
  strncpy ((char*) wr.Choice5,mess.c_str(),10);
}

//---------------------------------------------------------------------------
string VotePage::SizeString(string ms,int ln)              //right pad string
{
  for (int t=ms.length();t<=ln;t++)
  {
    ms=ms+" ";
  }
  ms.resize(ln);
  return(ms);
}



