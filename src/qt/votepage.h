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

protected:

private:
  Ui::VotePage *ui;


signals:
};

#endif
