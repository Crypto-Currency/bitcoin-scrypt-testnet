#ifndef VOTEPAGE_H
#define VOTEPAGE_H

#include "bitcoingui.h"

#include <QWidget>
#include <QMainWindow>
#include <QObject>

#include <QWebView>

namespace Ui
{
  class VotePage;
}

class VotePage : public QWidget
{
  Q_OBJECT

public:
  VotePage(QWidget *parent = 0);
  ~VotePage();
private slots:
  void on_CB1_clicked();
  void on_CB2_clicked();
  void on_CB3_clicked();
  void on_CB4_clicked();
  void on_CB5_clicked();
  void on_SendButton_clicked();
  void on_RefreshButton_clicked();
  void on_CreateButton_clicked();

protected:

private:
  Ui::VotePage *ui;


signals:
};

struct ReadData
{
  unsigned char BlockType[1];
  unsigned char VoteNum[8];
  unsigned char Question[100];
  unsigned char ChoicesEnabled[1];
  unsigned char Choice1[10];
  unsigned char Choice2[10];
  unsigned char Choice3[10];
  unsigned char Choice4[10];
  unsigned char Choice5[10];
};

struct
{
  char BlockType[1];
  char VoteNum[8];
  char Question[100];
  char ChoicesEnabled[1];
  char Choice1[10];
  char Choice2[10];
  char Choice3[10];
  char Choice4[10];
  char Choice5[10];
} WriteData;

struct
{
  char BlockType[1];
  char VoteNum[8];
  char Vote[1];
} VoteData;

#endif
