cmake_minimum_required(VERSION 3.15)

project(HSA
  VERSION 1.0.0
  DESCRIPTION "HeliSim Adapter to JSON"
  HOMEPAGE_URL "com.radar-mms.uav"
  LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(HSA_ENABLE_LOGGING "Enable CLI output" ON)
option(HSA_STANDALONE "Build standalone application. If not set, dynamic library will be built instead" ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
  Core
  Network
)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

if(HSA_STANDALONE)
  message(STATUS "[HSA] Building standalone executable.")
  add_executable(${PROJECT_NAME})
endif()

target_sources(${PROJECT_NAME}
  PRIVATE
    src/c++/adapter.h
    src/c++/adapter.c++
    src/c++/standalone/main.c++
    src/c++/export/hsa.h
    src/c++/export/export.h
    src/c++/config/config.h
    src/c++/config/config.c++
    src/c++/protocol/ruavputility.h
    src/c++/protocol/ruavputility.c++
    src/c++/protocol/protocolparser.h
    src/c++/protocol/protocolparser.c++
    src/c++/protocol/datagram.h
    src/c++/protocol/parameters.h
    src/c++/ip/socket.h
    src/c++/ip/socket.c++
    src/c++/utility/enumutils.h
    src/c++/utility/clilogger.h
    src/c++/utility/clilogger.c++
)

set(LIBRA_QT_TYPEDEFS ON CACHE BOOL "Enable Qt-specific type aliases" FORCE)
add_subdirectory(libs/libra)

add_subdirectory(libs/3rd-party/vt45-protocol)
add_subdirectory(libs/3rd-party/bimap)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network

    Libra
    vt45
    BidirectionalMap
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    src/c++
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    -DPROJECT_NAME="${PROJECT_NAME}"
    -DPROJECT_VERSION="${PROJECT_VERSION}"
    -DPROJECT_COMPANY="Radar-MMS"
    -DPROJECT_DOMAIN="${PROJECT_HOMEPAGE_URL}"

    -DHSA_LIBRARY
)

if(HSA_ENABLE_LOGGING)
  message(STATUS "[HSA] CLI output enabled.")
  target_compile_definitions(${PROJECT_NAME}
    PRIVATE
      -DHSA_ENABLE_LOGGING
  )
endif()

unset(HSA_ENABLE_LOGGING CACHE)
unset(HSA_STANDALONE CACHE)