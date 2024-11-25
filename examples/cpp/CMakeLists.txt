# examples/cpp/CMakeLists.txt
# 実行ファイルを作成
add_executable(Flat Flat.cc)
add_executable(IVFFlat IVFFlat.cc)

# ライブラリをリンク
target_link_libraries(Flat PRIVATE Raidillon)
target_link_libraries(IVFFlat PRIVATE Raidillon)