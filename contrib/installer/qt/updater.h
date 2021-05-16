#ifndef UPDATERFORM_H
#define UPDATERFORM_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "ui_updaterForm.h"

boost::filesystem::path GetDefaultDataDir();


class UpdaterForm : public QWidget
{
  Q_OBJECT

  public:
    UpdaterForm(QWidget *parent = 0);

  private slots:
//     void on_inputSpinBox1_valueChanged(int value);
//     void on_inputSpinBox2_valueChanged(int value);

  private:
    Ui::UpdaterForm ui;
};
#endif
