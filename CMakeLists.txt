cmake_minimum_required(VERSION 3.10)
project(f1tenth_planner)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include 디렉토리 추가
include_directories(include)

# 모든 소스파일을 targets로 묶기
add_executable(f1tenth_planner
    read_csv1.cpp
    set_track_data.cpp
    main.cpp
)