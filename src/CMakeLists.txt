# src/CMakeLists.txt
# ソースファイルをリストアップ
set(SOURCES
    collection.cc
    database.cc
    index/flat.cc
)

# ライブラリを作成
add_library(Raidillon STATIC ${SOURCES})