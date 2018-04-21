#include <QApplication>
#include "MainWindow.h"

#include <iostream>
#include <QDir>
#include <QDebug>

/*!
*
* @file
*
* @brief
* @author F. Aubert
*
*/

int main(int argc, char *argv[]) {

  QApplication application(argc,argv);
  QDir::setCurrent(QCoreApplication::applicationDirPath());


  MainWindow mainWindow;
  mainWindow.show();


  int finished=application.exec();

  return finished;

}

