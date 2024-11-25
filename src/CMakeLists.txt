# src/CMakeLists.txt
# ソースファイルをリストアップ
set(SOURCES
    collection.cc
    database.cc
    index/Flat.cc
    index/IVFFlat.cc
)

# ライブラリを作成
add_library(Raidillon STATIC ${SOURCES})