#include <QApplication>
#include <QtGui>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include "updater.h"

using namespace std;
using namespace boost;


bool sucess=false;

string initicker="BTCS";// check GetDefaultDataDir() for lowercase
string DirName="Bitcoin-sCrypt";
string downlocation="http://altcoinwarz.com:8080/BTCS/";
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
UpdaterForm::UpdaterForm(QWidget *parent)
     : QWidget(parent)
{
     ui.setupUi(this);
cout<<"data dir "<<strDataDir<<"\n";

  string temp="checking path "+strDataDir;
  ui.listWidget->addItem(temp.c_str());

//  Memo1->Lines->Add("checking path "+path);
  try
  {
    QDir dir(strDataDir.c_str());
    if (!dir.exists())
    {
      temp="creating "+strDataDir;
      ui.listWidget->addItem(temp.c_str());
      if(!dir.mkpath(strDataDir.c_str()))
      {
        temp="can not create "+strDataDir;
        ui.listWidget->addItem(temp.c_str());
        throw runtime_error("Can not create "+strDataDir);
      }
    }
    else
    {
      temp="path exists.";
      ui.listWidget->addItem(temp.c_str());
    }
  }
  catch (std::exception& e)
  {
    QMessageBox::information(this,tr("creating path"),tr(e.what()) );
  }



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

