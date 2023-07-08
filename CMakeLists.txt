cmake_minimum_required(VERSION 3.2)
project(
  AdventOfCode
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(
  Boost REQUIRED
  COMPONENTS system filesystem
  REQUIRED)
# add_executable(OpenMPTutorial challenges/day1/main.cpp)

# add_subdirectory("${PROJECT_SOURCE_DIR}/challenges/day1/")
# add_subdirectory("${PROJECT_SOURCE_DIR}/challenges/day2/")
# add_subdirectory("${PROJECT_SOURCE_DIR}/challenges/day3/")
# add_subdirectory("${PROJECT_SOURCE_DIR}/challenges/day4/")
# add_subdirectory("${PROJECT_SOURCE_DIR}/challenges/day5/")
add_subdirectory("${PROJECT_SOURCE_DIR}/challenges/day6/")
