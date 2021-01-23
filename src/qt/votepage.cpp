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
}



