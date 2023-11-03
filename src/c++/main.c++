//
// Created by whs31 on 11/1/2023.
//

#include <QtCore/QCoreApplication>
#include "adapter.h"

#if defined HSA_ENABLE_LOGGING
#include <iostream>
#endif

namespace Qt { using CoreApplication = QCoreApplication; }

int main(int argc, char** argv)
{
  Qt::CoreApplication app(argc, argv);

  #if defined HSA_ENABLE_LOGGING
  std::cout << "HSA version " << PROJECT_VERSION << " started." << std::endl;
  #endif

  HSA::Adapter adapter;
  return Qt::CoreApplication::exec();
}