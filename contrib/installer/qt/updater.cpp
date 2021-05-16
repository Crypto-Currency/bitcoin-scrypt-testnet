#include <QApplication>
#include <QtGui>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "updater.h"

using namespace std;
using namespace boost;


bool sucess=false;

string initicker="BTCS";
string DirName="Bitcoin-sCrypt";
string downlocation="http://altcoinwarz.com:8080/BTCS/";
string appname="Bitcoin-sCrypt-qt.exe";
string apppath="C:\\"+DirName+"\\";

std::string strDataDir = GetDefaultDataDir().string();


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


UpdaterForm::UpdaterForm(QWidget *parent)
     : QWidget(parent)
{
     ui.setupUi(this);
cout<<"data dir "<<strDataDir<<"\n";
string something="data dir "+strDataDir;
ui.listWidget->addItem(something.c_str());

}

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
  string dirname="."+DirName;
    return pathRet / dirname.c_str();
#endif
#endif
}
