#include "createvotedialog.h"
#include "ui_createvotedialog.h"
#include "clientmodel.h"
#include "votepage.h"

#include <string>
#include "boost/lexical_cast.hpp"

#include "version.h"

using namespace std;

extern string rdVoteNum;
extern string rdQuestion;
extern string rdChoice1;
extern string rdChoice2;
extern string rdChoice3;
extern string rdChoice4;
extern string rdChoice5;

extern string wrBlockType;
extern string wrChoicesEnabled;
extern string wrVoteNum;
extern string wrQuestion;
extern string wrChoice1;
extern string wrChoice2;
extern string wrChoice3;
extern string wrChoice4;
extern string wrChoice5;


CreateVoteDialog::CreateVoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVoteDialog)
{
    ui->setupUi(this);

  connect(ui->SendButton, SIGNAL(clicked(bool)), this, SLOT(on_SendButton_clicked()));
  connect(ui->ClearButton, SIGNAL(clicked(bool)), this, SLOT(on_ClearButton_clicked()));
  connect(ui->CancelButton, SIGNAL(clicked(bool)), this, SLOT(on_CancelButton_clicked()));

  connect(ui->RefreshButton, SIGNAL(clicked(bool)), this, SLOT(on_RefreshButton_clicked()));

  // get last vote number and inc
  int vnum=boost::lexical_cast<int>(rdVoteNum.c_str());
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
{// Qnum, Qtext,A1,A2,A3,A4,A5

  // count how many answers
  int qnum=0;
  if(ui->A1->text().length())
    qnum++;
  if(ui->A2->text().size())
    qnum++;
  if(ui->A3->text().size())
    qnum++;
  if(ui->A4->text().size())
    qnum++;
  if(ui->A5->text().size())
    qnum++;

printf("%d answers\n",qnum);

  // transfer data to votepage
  wrChoicesEnabled=boost::to_string(qnum);
  wrQuestion=ui->Qtext->text().toStdString();
printf("new question mess= |%s|\n",wrQuestion.c_str());

  wrVoteNum=ui->Qnum->text().toStdString();
  wrChoice1=ui->A1->text().toStdString();
  wrChoice2=ui->A2->text().toStdString();
  wrChoice3=ui->A3->text().toStdString();
  wrChoice4=ui->A4->text().toStdString();
  wrChoice5=ui->A5->text().toStdString();
wrBlockType="1"; // 1 is question - 3 is vote
  QDialog::accept();
}

void CreateVoteDialog::on_ClearButton_clicked()
{
//  ui->Qnum->setText("");
  ui->Qtext->setText("");
  ui->A1->setText("");
  ui->A2->setText("");
  ui->A3->setText("");
  ui->A4->setText("");
  ui->A5->setText("");
}

void CreateVoteDialog::on_CancelButton_clicked()
{
  close();
}

void CreateVoteDialog::on_RefreshButton_clicked()
{
  ui->view->reload();
}

