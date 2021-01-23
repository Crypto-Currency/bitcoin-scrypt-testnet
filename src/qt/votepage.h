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

private slots:

protected:

private:
  Ui::VotePage *ui;


signals:
};

#endif
