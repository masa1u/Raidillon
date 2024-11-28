# IncreSearch: An Efficient Incrementally Updatable Vector Search Index

## Introduction
IncreSearch is a high-performance vector search index designed for efficient incremental updates. It addresses the limitations of existing vector search solutions by providing a globally unified index that can be updated with minimal computational overhead, ensuring consistent search performance even as new data is added.

## Features
- **Incremental Updates**: Efficiently update the index with new vectors without significant performance degradation.
- **Global Indexing**: Maintains a single global index for consistent and efficient searches.
- **Optimized Resource Usage**: Reduces computational costs associated with index maintenance and updates.
- **High Search Efficiency**: Delivers fast and accurate search results even with a continuously growing dataset.

## Comparison with Existing Products and Research
### Milvus
Milvus creates indexes in units called segments, requiring searches to be performed on a per-segment basis. This approach is less efficient compared to using a single global index. Additionally, compaction processes to merge segments are resource-intensive and continuously consume computational resources, making them costly.

### Vearch
Vearch adds new vectors directly to clusters within the vector search index. This method leads to imbalances between clusters, causing decreased search efficiency over time. As illustrated in the SPFresh paper (see Figure 3), performance degradation becomes significant as the data grows.

### Vald
Vald utilizes an index called NGT that supports incremental updates. However, updating the graph is computationally expensive and involves acquiring giant locks, which can hinder performance and scalability.

### SPFresh
SPFresh is a vector search index developed for on-disk usage. It performs index balancing adjustments for inserted data. While it mitigates some issues of incremental updates, it still requires partial graph updates, which can introduce drawbacks such as increased update latency and complexity.


**IncreSearch**, on the other hand, adapts SPFresh's rebalancing concepts for in-memory usage, eliminating the performance bottlenecks associated with graph updates. By managing cluster centroids as graphs and optimizing their updates, IncreSearch provides low-latency searches without the overhead of frequent graph adjustments.