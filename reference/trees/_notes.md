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

# Tree Painting (online)

Given a tree G w/ N vericies, we have two queries: paint an edge and get # colored edges between vertices, and update a vertex's value in the tree.

To solve, we can find the LCA to reduce query2(i,j) to 2 queries (l, i) and (l, j) where l is the LCA of i & j

Query(i,j) 's answer is the sum of both queries

## Algorithm

### Preprocessing

DFS root w/ Euler tour. Get LCA computations

Each edge(u,v) appears twice in the Tour. Forwards and backwards from (u->v) and (v->u).

## Build 2 lists of edges

The 1st stores forward edges, the 2nd backwards.

Store as 1 for colored trees

Build a SegTree for both lists (range sum + modifications)

## Answer Queries

Find i and j in the Euler tour (for the 1st time), at positions p and q in euler[]

Ans = T1[p..q-1] - T2[p..q-1];

^ Here T1 is our SegTree of forward edges

We use q-1 so we don't capture j's outgoing edge

For update queries, find i & j in euler[] and update them in T1/T2