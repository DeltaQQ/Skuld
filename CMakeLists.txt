cmake_minimum_required(VERSION 3.12...3.21.1)
project(Skuld)
set(CMAKE_CONFIGURATION_TYPES "Release;Debug")

add_subdirectory("${PROJECT_SOURCE_DIR}/Client" "${PROJECT_SOURCE_DIR}/Client/Build")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine" "${PROJECT_SOURCE_DIR}/Engine/Build")
add_subdirectory("${PROJECT_SOURCE_DIR}/Server" "${PROJECT_SOURCE_DIR}/Server/Build")
add_subdirectory("${PROJECT_SOURCE_DIR}/Tests" "${PROJECT_SOURCE_DIR}/Tests/Build")