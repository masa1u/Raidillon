# examples/cpp/CMakeLists.txt
# 実行ファイルを作成
add_executable(flat flat.cc)

# ライブラリをリンク
target_link_libraries(flat PRIVATE Raidillon)