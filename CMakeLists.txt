# CMakeLists.txt (root)
cmake_minimum_required(VERSION 3.10)
project(Raidillon)

# C++標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# インクルードディレクトリを設定
include_directories(include)

# Position Independent Codeを有効にする
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# サブディレクトリを追加
add_subdirectory(src)
add_subdirectory(examples/cpp)
add_subdirectory(bindings/python)