#ifndef UPDATERFORM_H
#define UPDATERFORM_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "ui_updaterForm.h"

boost::filesystem::path GetDefaultDataDir();


class UpdaterForm : public QWidget
{
  Q_OBJECT

  QNetworkAccessManager manager;

  public:
    UpdaterForm(QWidget *parent = 0);
    Ui::UpdaterForm ui;

  private slots:
    void start();
    void getlist();
    void getListFinished(QNetworkReply* reply);
    void downloadFinished(QNetworkReply *reply);
    bool netHandleError(QNetworkReply* reply, QString urlDownload);
    void networkTimeout();
    static bool isHttpRedirect(QNetworkReply *reply);

  private:
    QTimer *networkTimer;

  QString latestNetError;
  QString latestFileError;

};
#endif
