cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME CustomString)

project(${PROJECT_NAME} VERSION 1.0.0)
message("------------------- Project files generaion for ${PROJECT_NAME} -------------------")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("C++ standard: ${CMAKE_CXX_STANDARD}")

set_property(GLOBAL PROPERTY VS_FOLDER_PROPS "Files")

include(FetchContent)
fetchcontent_declare(
    doctest
    URL https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h
    DOWNLOAD_NO_EXTRACT TRUE
)
fetchcontent_makeavailable(doctest)

add_subdirectory(Source)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})