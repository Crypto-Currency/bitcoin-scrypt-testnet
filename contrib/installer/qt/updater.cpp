#include <QApplication>
#include <QProcess>
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

string FileName; //global 

std::string strDataDir = GetDefaultDataDir().string();
std::string strAppDir = GetDefaultAppDir().string();


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
  Qt::WindowFlags flags = uf.windowFlags();
  uf.setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
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
  boost::trim_right(localtx);
  if(!localtx.length())
  {
    localtx="0000";
  }

cout<<"local version "<<localtx<<"\n";
  ui.label3->setText(localtx.c_str());

// get remote version.txt and read it
  getlist();
  while(networkTimer->isActive())
  {// wait for download to finish
    qApp->processEvents();
  }

  int iLocalVer=ui.label3->text().toInt();
  int iRemoteVer=ui.label4->text().toInt();

string label4txt=ui.label4->text().toStdString();
cout<<"label4txt "<<label4txt<<"\n"; 
cout<<"iLocalVer "<<iLocalVer<<"\n"; 
cout<<"iRemoteVer "<<iRemoteVer<<"\n"; 
  if(iRemoteVer > iLocalVer)
  {
    temp="Found new version";
    ui.TextEdit->appendPlainText(temp.c_str());

    download(QString::fromStdString(strAppDir),NULL);
//cout<<"returned from Download "<<qtemp<<"\n";
//    ui.TextEdit->appendPlainText(qtemp);
  }  
  else
  { // launch wallet
    string strAppFilename=GetDefaultAppName();
    string strPathApp=strAppDir+strAppFilename;
cout<<"strAppDir "<<strAppDir<<"\n";
cout<<"strAppFilename "<<strAppFilename<<"\n";
cout<<"strPathApp "<<strPathApp<<"\n";

    QProcess::startDetached(strPathApp.c_str());
exit(0);
  }
}

//-------------------------------------------------------------------------------------
void UpdaterForm::getlist()
{
  string temp="checking "+downlocation;
  ui.TextEdit->appendPlainText(temp.c_str());
//cout<<"temp "<<temp<<"\n";

// get remote version
// connect the event and launch it
  connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getListFinished(QNetworkReply*)));

  QNetworkRequest request;
  downloadLocation = QString::fromStdString(downlocation+"/version.txt");
cout<<"downloadLocation "<<downloadLocation.toStdString()<<"\n";

  request.setUrl(QUrl(downloadLocation));
  request.setRawHeader("User-Agent", "Wallet update request");

//cout<<"starting network timer \n";
  networkTimer->start();
//cout<<"manager get \n";
  manager.get(request);

}

//-------------------------------------------------------------------------------------
void UpdaterForm::getListFinished(QNetworkReply* reply)
{
  if (netHandleError(reply, downloadLocation))
  {
    disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
    QString versionlist=reply->readAll();

  string line=versionlist.toStdString();//at(0).toLocal8Bit().constData();
cout<<"remote version "<<line<<"\n";
  boost::trim_right(line);
  ui.label4->setText(line.c_str());
  }
  else
  {
    reply->abort();
  } 
}

//-------------------------------------------------------------------------------------
void UpdaterForm::download(const QUrl &downTo,QNetworkReply *reply)
{
  networkTimer->stop();
  QString temp=downTo.toString();
  string appFilename=GetDefaultAppName();
cout<<"in download : download APP to folder "<<temp.toStdString()<<"\n";
cout<<"in download : download APP from "<<downlocation<<"\n";
cout<<"in download : download DATA to "<<strDataDir<<"\n";
cout<<"in download : download DATA FROM "<<downloadLocation.toStdString()<<"\n";

cout<<"in download : download APP name "<<appFilename<<"\n";

// get app
  disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
  connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
  QNetworkRequest request;//(filename);

string tempurl=downlocation+"/"+appFilename;
  request.setUrl(QString::fromStdString(tempurl));
cout<<"requesting "<<tempurl<<"\n";
  request.setRawHeader("User-Agent", "app request");

  FileName=temp.toStdString()+appFilename;

  networkTimer->start();
  reply = manager.get(request);
  connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(updateProgress(qint64, qint64)));
  while(networkTimer->isActive())
  {// wait for download to finish
    qApp->processEvents();
  }
QFile myfile(QString::fromStdString(FileName));
myfile.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
cout<<"wrote file to "<<FileName<<"\n";


// get version.txt
  disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
  connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
  request.setUrl(downloadLocation);
cout<<"requesting "<<downloadLocation.toStdString()<<"\n";
  request.setRawHeader("User-Agent", "version.txt request");

  FileName=strDataDir+"/version.txt";
  networkTimer->start();
  reply = manager.get(request);
  connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(updateProgress(qint64, qint64)));

  while(networkTimer->isActive())
  {// wait for download to finish
    qApp->processEvents();
  }
cout<<"wrote file to "<<FileName<<"\n";

}

//-------------------------------------------------------------------------------------
void UpdaterForm::downloadFinished(QNetworkReply *reply)
{
  networkTimer->stop();

  if (!saveToDisk(FileName.c_str(), reply))
  {
    QString fError=tr("Could not open ")+FileName.c_str()+" for writing: "+latestFileError;
cout<<"File Saving Error"<<fError.toStdString()<<"\n";
  }

  disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
cout<<"downloadFinished done\n";

}

//-------------------------------------------------------------------------------------
bool UpdaterForm::saveToDisk(const QString &filename, QNetworkReply *reply)
{
  string temp="saving "+filename.toStdString();
  ui.TextEdit->appendPlainText(temp.c_str());
cout<<"save to disk writing "<<filename.toStdString()<<"\n";
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly))
  {
    latestFileError = file.errorString();
cout<<"file open error "<<file.errorString().toStdString()<<"\n";

    return false;
  }

  file.write(reply->readAll());
  file.close();

  ui.progressBar->setValue(0);
  return true;
}

//-------------------------------------------------------------------------------------
void UpdaterForm::updateProgress(qint64 read, qint64 total)
{
  ui.progressBar->setMaximum(total);
  ui.progressBar->setValue(read);
  networkTimer->start(); // restart the timer so it doesn't timeout on long downloads
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
  disconnect(&manager, SIGNAL(finished(QNetworkReply*)), 0, 0);  
  QMessageBox::information(this,tr("Network Error"),tr(latestNetError.toStdString().c_str()));
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

//-------------------------------------------------------------------------------------
boost::filesystem::path GetDefaultAppDir()
{
    namespace fs = boost::filesystem;
    // Windows < Vista: C:\Documents and Settings\Username\Application Data\DirName
    // Windows >= Vista: C:\Users\Username\AppData\Roaming\DirName
    // Mac: ~/Library/Application Support/DirName
    // Unix: ~/.DirName
#ifdef WIN32
    // Windows
    return "C:" / DirName.c_str();
#else
    fs::path pathRet;
    char* pszHome = getenv("HOME");
    if (pszHome == NULL || strlen(pszHome) == 0)
        pathRet = fs::path("/");
    else
        pathRet = fs::path(pszHome);
#ifdef MAC_OSX
    // Mac
    pathRet = "/Applications/"+GetDefaultAppName()+".app/Contents/MacOS/";
downlocation=downlocation+"/MAC";
//    fs::create_directory(pathRet);
    return pathRet;
#else

    // Unix
  string dname=DirName;
  boost::algorithm::to_lower(dname);  // some coins use all lower case

////// make a folder on the desktop
dname="Desktop/"+dname+"/";
fs::create_directory(pathRet / dname.c_str());

/////  don't make a folder
//dname="Desktop/";

cout<<"unix location "<<pathRet / dname.c_str()<<"\n";

  return pathRet / dname.c_str();
#endif
#endif
}

//-------------------------------------------------------------------------------------
string GetDefaultAppName()
{
#ifdef WIN32
  // Windows
  return "Bitcoin-sCrypt-qt.exe";
#endif

#ifdef MAC_OSX
  // MAC
  return "Bitcoin-sCrypt-qt";
#endif

  // Unix
  return "Bitcoin-sCrypt-qt";
}

