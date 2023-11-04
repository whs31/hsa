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

find_package(Threads REQUIRED)

add_library(asio INTERFACE)
target_include_directories(asio SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/libs/3rd-party/asio-standalone/include)
message(STATUS "[ASIO] Path to ASIO: ${CMAKE_SOURCE_DIR}/libs/3rd-party/asio-standalone/include")
target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)
target_link_libraries(asio INTERFACE Threads::Threads)

if(WIN32)
  # macro see @ https://stackoverflow.com/a/40217291/1746503
  macro(get_win32_winnt version)
    if(CMAKE_SYSTEM_VERSION)
      set(ver ${CMAKE_SYSTEM_VERSION})
      string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
      string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
      if("${verMajor}" MATCHES "10")
        set(verMajor "A")
        string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
      endif("${verMajor}" MATCHES "10")
      string(REPLACE "." "" ver ${ver})
      string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
      set(${version} "0x${ver}")
    endif()
  endmacro()

  if(NOT DEFINED _WIN32_WINNT)
    get_win32_winnt(ver)
    set(_WIN32_WINNT ${ver})
  endif()

  message(STATUS "[ASIO] Set _WIN32_WINNET=${_WIN32_WINNT}")

  target_compile_definitions(asio INTERFACE _WIN32_WINNT=${_WIN32_WINNT} WIN32_LEAN_AND_MEAN)
endif()

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
else()
  message(STATUS "[HSA] Building shared library.")
  add_library(${PROJECT_NAME} SHARED)
endif()

target_sources(${PROJECT_NAME}
  PRIVATE
    src/c++/adapter.h
    src/c++/adapter.c++
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
    src/c++/ip/isocket.h
    src/c++/ip/socketqtnetwork.h
    src/c++/ip/socketqtnetwork.c++
    src/c++/ip/socketasio.h
    src/c++/ip/socketasio.c++
    src/c++/utility/enumutils.h
    src/c++/utility/clilogger.h
    src/c++/utility/clilogger.c++
)

if(HSA_STANDALONE)
  target_sources(${PROJECT_NAME}
    PRIVATE
      src/c++/standalone/main.c++
  )
endif()

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
    asio
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