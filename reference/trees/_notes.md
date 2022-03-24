# Coins

- Pick subset of nodes so no 2 adj are chosen, w/ max coin sum
- If we include node V, we can't include its direct children
- dp(V) = max( Σn dp(v1), C(v) + (Σn dp(j) for all v's children) )
- dp1 & dp2: if we include node V in our answer or not

# Min Root w/ Min Sum of Node Costs

- f(i) = time if we start at i = Ci + (Σn f(ch[i])/n)
- g(i) = time at parent[i] if tree rooted at i

# Splay Trees

- Repeat until node reaches root:
  - Rotate parent if node parent unbalanced
    - if (node == par.par.L.L) node = par.par.R.R
  - Otherwise, rotate node
- Insert: splay new node
- Erase: splay node and join its subtrees
- Splaying doesn't affect in-order traversal

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

# MAXIMUM INDEPENDENT SET

Compute via DFS.

The search will compute two values for each subtree in the graph:

- A(i) = The size of the maximum independent set in the subtree rooted at i with the constraint that node i must be included in the set.
- B(i) = The size of the maximum independent set in the subtree rooted at i with the restriction that node i must NOT be included in the set.
These can be computed recursively by considering two cases:

The root of the subtree is not included.

```B(i) = sum(max(A(j),B(j)) for j in children(i))```

The root of the subtree is included.

```A(i) = 1 + sum(B(j) for j in children(i))```

The size of the maximum independent set in the whole tree is `max(A(root),B(root))`.

# Maximal Independent Set

Maximal independent set: (one to which no vertices can be added)

To find the maximal independent set of vertices, we can use an important property of a tree: Every tree is Bipartite i.e. We can color the vertices of a tree using just two colors such that no two adjacent vertices have the same color.

Do a DFS traversal and start coloring the vertices with BLACK and WHITE.

Pick the set of vertices (either BLACK or WHITE) which are more in number. This will give you the maximal independent set of vertices for a tree.

Some Intuition behind the why this algorithm works:

Let us first revisit the definition of the maximal independent set of vertices. We have to pick just one end point of an edge and we have to cover every edge of the tree satisfying this property. We are not allowed to choose both end points of an edge.

Now what does bicoloring of a graph do? It simply divides the set of vertices into two subsets (WHITE and BLACK) and WHITE colored vertices are directly connected to BLACK ones. Thus if we choose either all WHITE or all BLACK ones we are inherently choosing an independent set of vertices. Thus to choose maximal independent set, go for the subset whose size is larger.
