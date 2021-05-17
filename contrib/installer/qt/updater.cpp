#include <QApplication>
#include <QtGui>
#include <QUrl>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include "updater.h"

using namespace std;
using namespace boost;


bool sucess=false;

string initicker="BTCS";// check GetDefaultDataDir() for lowercase
string DirName="Bitcoin-sCrypt";
string downlocation="http://altcoinwarz.com:8080/BTCS";
QString downloadLocation;
string appname="Bitcoin-sCrypt-qt.exe";
string apppath="C:\\"+DirName+"\\";

std::string strDataDir = GetDefaultDataDir().string();


//-------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  UpdaterForm uf;
  QDesktopWidget widget;
  QRect screenGeometry = widget.screenGeometry();
  int height = screenGeometry.height();
  int width = screenGeometry.width();
  int x=(width - uf.width()) / 2.0;
  int y=(height - uf.height()) / 2.0;
  uf.setGeometry(x,y,uf.width(),uf.height());
  uf.show();
  return app.exec();
}


//-------------------------------------------------------------------------------------
UpdaterForm::UpdaterForm(QWidget *parent) : QWidget(parent)
{
  networkTimer = new QTimer(this);
  networkTimer->setInterval(10000);
  connect(networkTimer, SIGNAL(timeout()), this, SLOT(networkTimeout()));
  ui.setupUi(this);
  ui.TextEdit->appendPlainText("working ...");
cout<<"data dir "<<strDataDir<<"\n";

QTimer::singleShot(1000, this, SLOT(start()));
}

//-------------------------------------------------------------------------------------
void UpdaterForm::start()
{
  string temp="checking path "+strDataDir;
  ui.TextEdit->appendPlainText(temp.c_str());

  try
  {
    QDir dir(strDataDir.c_str());
    if (!dir.exists())
    {
      temp="creating "+strDataDir;
      ui.TextEdit->appendPlainText(temp.c_str());
      if(!dir.mkpath(strDataDir.c_str()))
      {
        temp="can not create "+strDataDir;
        ui.TextEdit->appendPlainText(temp.c_str());
        throw runtime_error("Can not create "+strDataDir);
      }
    }
    else
    {
      temp="path exists.";
      ui.TextEdit->appendPlainText(temp.c_str());
    }
  }
  catch (std::exception& e)
  {
    QMessageBox::information(this,tr("creating path"),tr(e.what()) );
  }

// get local version.txt and read it
  string filename = strDataDir + "/version.txt";
  ifstream file;
  file.open(filename.c_str());
  string localtx;
  getline(file, localtx);
  file.close();

cout<<"local version "<<localtx<<"\n";
  ui.label3->setText(localtx.c_str());

// get remote version.txt and read it
  getlist();




}

//-------------------------------------------------------------------------------------
void UpdaterForm::getlist()
{
  string temp="checking "+downlocation;
  ui.TextEdit->appendPlainText(temp.c_str());
cout<<"temp "<<temp<<"\n";

// get remote version
// connect the event and launch it
  connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getListFinished(QNetworkReply*)));

  QNetworkRequest request;
  QString downloadLocation = QString::fromStdString(downlocation+"/version.txt");
cout<<"downloadLocation "<<downloadLocation.toStdString()<<"\n";

  request.setUrl(QUrl(downloadLocation));
  request.setRawHeader("User-Agent", "Wallet update request");

cout<<"starting network timer \n";
  networkTimer->start();
cout<<"manager get \n";
  manager.get(request);
}

//-------------------------------------------------------------------------------------
void UpdaterForm::getListFinished(QNetworkReply* reply)
{
cout<<"in getListFinished \n";
  if (netHandleError(reply, downloadLocation))
  {
cout<<"getListFinished : disconnect finished\n";
    disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
cout<<"getListFinished : connect finished\n";
    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
    QString versionlist=reply->readAll();

string line=versionlist.toStdString();//at(0).toLocal8Bit().constData();
cout<<"remote version "<<line<<"\n";
  ui.label4->setText(line.c_str());


//    QStringList list = pagelist.split('\n');
//    QString line;

/*    for(int i=0;i<list.count();i++)
    {
      line=list.at(i).toLocal8Bit().constData();
      line.simplified(); // strip extra characters
      line.replace("\r",""); // this one too
      if(line.length())
      {  
        download("http://btcs.altcoinwarz.com/themes/"+line);
      } 
    }
*/
  }
  else
  {
    reply->abort();
  } 
}

//-------------------------------------------------------------------------------------
void UpdaterForm::downloadFinished(QNetworkReply *reply)
{
cout<<"in downloadFinished \n";
  QUrl url = reply->url();
  if (netHandleError(reply, url.toEncoded()))
  {
//    QString filename = inipath + url.path().replace("/themes/","/");
//    if (!saveToDisk(filename, reply))
//    {
//      QString fError = tr("Could not open ") + filename + " for writing: " + latestFileError;
//      emit error(tr("File Saving Error"), fError, false);
//    }
//    currentDownloads.removeAll(reply);
    reply->deleteLater();

    // when finish all, re-enable the download button and force a find
//    if (currentDownloads.isEmpty()) 
//    {
//	  statusLabel->setText("");
//      downloadButton->setEnabled(true);
      disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
//      find();
//      emit information(tr("Themes Download"), tr("Themes were successfully downloaded and installed."));
//    }
  }
}

//-------------------------------------------------------------------------------------
bool UpdaterForm::netHandleError(QNetworkReply* reply, QString urlDownload)
{
cout<<"in netHandleError\n";
  networkTimer->stop();
  if (reply->error())
  {
    latestNetError = tr("Download of ") + urlDownload + tr(" failed: ") + reply->errorString();
cout<<"netHandleError : reply->error\n";
  }
  else if (isHttpRedirect(reply))
  {
cout<<"netHandleError : isHttpRedirect\n";
    latestNetError = tr("HTTP redirect while attempting download of ") + urlDownload;
  }
  else
 {
cout<<"netHandleError : passed\n";

  // signal no errors here
  return(true);
}

  // execute the same function, displaying latest occured error
cout<<"netHandleError : calling network timeout\n";
  networkTimeout();
  return(false);
}

//-------------------------------------------------------------------------------------
void UpdaterForm::networkTimeout()
{
  // signal error and preset for next operation
  networkTimer->stop();
  if (latestNetError == "")
  {
    latestNetError = tr("Network timeout. Please check your network and try again.");
  }
//  statusLabel->setText("");
//  downloadButton->setEnabled(true);
  disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
//  Find();
//  emit error(tr("Network Error : Timeout"), latestNetError, true);
    QMessageBox::information(this,tr("Network Error"),tr(latestNetError.toStdString().c_str()) );
}

//-------------------------------------------------------------------------------------
bool UpdaterForm::isHttpRedirect(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

//-------------------------------------------------------------------------------------
boost::filesystem::path GetDefaultDataDir()
{
    namespace fs = boost::filesystem;
    // Windows < Vista: C:\Documents and Settings\Username\Application Data\DirName
    // Windows >= Vista: C:\Users\Username\AppData\Roaming\DirName
    // Mac: ~/Library/Application Support/DirName
    // Unix: ~/.DirName
#ifdef WIN32
    // Windows
    return GetSpecialFolderPath(CSIDL_APPDATA) / DirName.c_str();
#else
    fs::path pathRet;
    char* pszHome = getenv("HOME");
    if (pszHome == NULL || strlen(pszHome) == 0)
        pathRet = fs::path("/");
    else
        pathRet = fs::path(pszHome);
#ifdef MAC_OSX
    // Mac
    pathRet /= "Library/Application Support";
    fs::create_directory(pathRet);
    return pathRet / DirName.c_str();
#else
    // Unix
  string dname="."+DirName;
  boost::algorithm::to_lower(dname);  // some coins use all lower case
  return pathRet / dname.c_str();
#endif
#endif
}
