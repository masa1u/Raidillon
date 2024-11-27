import os
import raidillon_bindings as rb

from src.extractor import FeatureExtractor
from src.display import display_result

# データベースを作成
db = rb.Database("MyDatabase")

# コレクションを作成
collection = db.createCollection("MyCollection")

extractor = FeatureExtractor("resnet34")

# ../data/dataにある画像を全てエンベディングしてインサート
inserted_images = {}
data_dir = os.path.join(os.path.dirname(__file__), '../../data/data')
for i, filename in enumerate(os.listdir(data_dir)):
    if filename.endswith('.jpeg') or filename.endswith('.png'):
        image_path = os.path.join(data_dir, filename)
        embedding = extractor(image_path).tolist()
        collection.insert(i, embedding)
        inserted_images[i] = image_path

# インデックスを作成
numClusters = 10
index = collection.buildIndex("IVFFlat", "euclidean", numClusters)

# ../data/queryにあるベクトルを用いて検索
query_dir = os.path.join(os.path.dirname(__file__), '../../data/query')
for filename in os.listdir(query_dir):
    if filename.endswith('.jpeg') or filename.endswith('.png'):
        query_path = os.path.join(query_dir, filename)
        query = extractor(query_path).tolist()
        top_k = 10
        nprobe = 3
        nearest_results = index.search(query, top_k, nprobe)
        results_filenames = []
        for result in nearest_results:
            results_filenames.append(inserted_images[result[0]])
        display_result(query_path, results_filenames)
            
