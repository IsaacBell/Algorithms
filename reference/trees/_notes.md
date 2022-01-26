# Distance Queries
Distance between node u and v can be calculated as 𝑑𝑒𝑝𝑡ℎ[𝑢]+𝑑𝑒𝑝𝑡ℎ[𝑣]−2∗𝑑𝑒𝑝𝑡ℎ[𝐿𝐶𝐴(𝑢,𝑣)]

# Counting Paths
This problem can be solved using prefix sum on trees.

For every given path 𝑢→𝑣, we do following changes to the prefix array.

prefix[u]++
prefix[v]++
prefix[lca]--
prefix[parent[lca]]--

Next, we run a subtree summation over entire tree which means every node now holds the number of paths that node is a part of. This method is analogous to range update and point query in arrays, when all updates are preceded by queries.
𝑝𝑟𝑒𝑓𝑖𝑥[𝑢]=∑𝑣:𝑐ℎ𝑖𝑙𝑑𝑟𝑒𝑛[𝑢]𝑝𝑟𝑒𝑓𝑖𝑥[𝑣]

