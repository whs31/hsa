cmake_minimum_required(VERSION 3.15)

project(HSA
  VERSION 1.0.0
  DESCRIPTION "HeliSim Adapter to JSON"
  HOMEPAGE_URL "com.radar-mms.uav"
  LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON CACHE BOOL "Export all symbols")

option(HSA_ENABLE_LOGGING "Enable CLI output" OFF)
option(HSA_STANDALONE "Build standalone application. If not set, dynamic library will be built instead" OFF)

if(HSA_STANDALONE)
  message(STATUS "[HSA] Building standalone executable.")
  add_executable(${PROJECT_NAME})
else()
  message(STATUS "[HSA] Building shared library.")
  add_library(${PROJECT_NAME} SHARED)

  if(WIN32)
    set_target_properties (${PROJECT_NAME} PROPERTIES
      OUTPUT_NAME "${PROJECT_NAME}"
      PREFIX ""
    )
  endif()
endif()

target_sources(${PROJECT_NAME}
  PUBLIC
    src/c++/export/hsa.h
    src/c++/export/export.h
    src/c++/export/dgram.h
  PRIVATE
    src/c++/adapter.h
    src/c++/adapter.c++
    src/c++/config/config.h
    src/c++/config/config.c++
    src/c++/protocol/ruavputility.h
    src/c++/protocol/ruavputility.c++
    src/c++/protocol/protocolparser.h
    src/c++/protocol/protocolparser.c++
    src/c++/protocol/data.h
    src/c++/protocol/parameters.h
    src/c++/protocol/wrapper.h
    src/c++/ip/isocket.h
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

add_subdirectory(libs/libra)
add_subdirectory(libs/asio)
add_subdirectory(libs/3rd-party/vt45-protocol)
add_subdirectory(libs/3rd-party/bimap)

set_target_properties(BidirectionalMap PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(Libra PRIVATE -fPIC)
target_compile_options(asio INTERFACE -fPIC)
target_compile_options(vt45 PRIVATE -fPIC)
target_compile_options(BidirectionalMap PRIVATE -fPIC)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
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