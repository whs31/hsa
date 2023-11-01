cmake_minimum_required(VERSION 3.15)

project(HSA
  VERSION 1.0.0
  DESCRIPTION "HeliSim Adapter to JSON"
  HOMEPAGE_URL "com.radar-mms.uav"
  LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 COMPONENTS Core)
find_package(Qt5 COMPONENTS
  Core
  Network
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    src/c++/main.c++
)

set(LIBRA_QT_TYPEDEFS ON CACHE BOOL "Enable Qt-specific type aliases" FORCE)
add_subdirectory(libs/libra)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt5::Core
    Qt5::Network
    Libra
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
)