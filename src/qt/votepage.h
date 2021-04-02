#ifndef VOTEPAGE_H
#define VOTEPAGE_H

#include "bitcoingui.h"

#include <QWidget>
#include <QMainWindow>
#include <QObject>
#include <string>

#include <QWebView>

 
namespace Ui
{
  class VotePage;
}

class WalletModel;

class VotePage : public QWidget
{
  Q_OBJECT

public:
  VotePage(QWidget *parent = 0);
  ~VotePage();
  void buffWRblock();
  void HexDump(unsigned char* pBuffer, int size);
  void ClearCBs();
  std::string IntToHex(int a,int s);
  std::string SizeString(std::string ms,int ln);
  int getChoice();

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
  WalletModel *model;


signals:
};

struct ReadData
{
  unsigned char BlockType[1]; //1-question 2-question pt2 3-vote
  unsigned char VoteNum[8];
  unsigned char Question[100];
  unsigned char ChoicesEnabled[1];
  unsigned char Choice1[10];
  unsigned char Choice2[10];
  unsigned char Choice3[10];
  unsigned char Choice4[10];
  unsigned char Choice5[10];
};

struct WriteData
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

struct VoteData
{
  char BlockType[1];
  char VoteNum[8];
  char Vote[1];
};

#endif
