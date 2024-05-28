cmake_minimum_required(VERSION 3.10)
project(PersonalFinanceApp)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

include_directories(include)

add_executable(PersonalFinanceApp src/main.cpp src/database.cpp)
target_link_libraries(PersonalFinanceApp PRIVATE SQLite::SQLite3)