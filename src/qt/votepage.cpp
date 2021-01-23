#include "votepage.h"
#include "ui_votepage.h"
#include "util.h"
#include "bitcoingui.h"

#include <QSettings>
#include <string>
#include <QMainWindow>
#include "ui_interface.h"

extern BitcoinGUI *guiref;

#include <QDebug>
using namespace std;



VotePage::VotePage(QWidget *parent) : QWidget(parent), ui(new Ui::VotePage)
{
  ui->setupUi(this);

  connect(ui->CB1, SIGNAL(clicked(bool)), this, SLOT(on_CB1_clicked()));
  connect(ui->CB2, SIGNAL(clicked(bool)), this, SLOT(on_CB2_clicked()));
  connect(ui->CB3, SIGNAL(clicked(bool)), this, SLOT(on_CB3_clicked()));
  connect(ui->CB4, SIGNAL(clicked(bool)), this, SLOT(on_CB4_clicked()));
  connect(ui->CB5, SIGNAL(clicked(bool)), this, SLOT(on_CB5_clicked()));
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

