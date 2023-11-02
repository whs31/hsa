//
// Created by whs31 on 11/1/2023.
//

#include <iostream>
#include <QtCore/QCoreApplication>
#include "adapter.h"

namespace Qt { using CoreApplication = QCoreApplication; }

int main(int argc, char** argv)
{
  Qt::CoreApplication app(argc, argv);
  std::cout << "HSA version " << PROJECT_VERSION << " started." << std::endl;
  HSA::Adapter adapter;
  return Qt::CoreApplication::exec();
}