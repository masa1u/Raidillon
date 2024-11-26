import random

import raidillon_bindings as rb

# データベースを作成
db = rb.Database("MyDatabase")

# コレクションを作成
collection = db.createCollection("MyCollection")

# ランダムなデータを生成してコレクションにインサート
for i in range(100):
    data = [random.uniform(0.0, 10.0) for _ in range(3)]
    collection.insert(i, data)

# インデックスを作成
index = collection.buildIndex("flat", "euclidean")

# 検索クエリ
query = [1.0, 2.0, 3.0]
top_k = 5
nearest_results = index.search(query, top_k)

# 検索結果を表示
print(f"Top {top_k} nearest IDs and distances: {nearest_results}")