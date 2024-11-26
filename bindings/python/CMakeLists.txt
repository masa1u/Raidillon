cmake_minimum_required(VERSION 3.10)
project(RaidillonPythonBindings)

# pybind11をサブモジュールとして追加
add_subdirectory(pybind11)

# Pythonバインディングを作成
pybind11_add_module(raidillon_bindings raidillon_bindings.cc)

# ライブラリをリンク
target_link_libraries(raidillon_bindings PRIVATE Raidillon)