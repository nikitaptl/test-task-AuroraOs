cmake_minimum_required(VERSION 3.14)

project(test-task-AuroraOs LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core DBus)

add_executable(test-task-AuroraOs
  main.cpp
  SharingFramework.h
  SharingFramework.cpp
  ConfigManager.h
  ConfigManager.cpp
  Validator.h
  InputValidator.cpp
  ServiceException.h
)

target_link_libraries(test-task-AuroraOs Qt5::Core Qt5::DBus)

include(GNUInstallDirs)
install(TARGETS test-task-AuroraOs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
