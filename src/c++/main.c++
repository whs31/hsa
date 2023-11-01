//
// Created by whs31 on 11/1/2023.
//

#include <iostream>
#include <format>
#include <QtCore/QCoreApplication>
#include "def.h"
#include "config.h"

namespace Qt { using CoreApplication = QCoreApplication; }

int main(int argc, char** argv)
{
  Qt::CoreApplication app(argc, argv);
  printLn("HSA version {} started.", PROJECT_VERSION);
  HSA::Config();
  std::cin.get();
  return 0;//Qt::CoreApplication::exec();
}