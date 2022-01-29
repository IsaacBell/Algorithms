# Games on Graphs

```
Impl:
      See: #reference/graph/policeman_and_thief.cpp

Problem:
  - Curr state is a V
  - Players move to adj Vs by E
  - Player who can't move loses/wins

Description:
  - If V has an outgoing E to a losing V, the V wins
  - If all outgoing edges lead to losing V, the V loses
  - If at some pt there are still undefined V's, and neither will fit the 1st/2nd rule, then each V when used as a starting V, leads to a draw

Approach:
  - DFS forward and back over E's and reversed E's
    - Don't enter V's marked as winning/losing
    - If search goes from a losing V to an undefined V, it wins
      - Continue DFS w/ this V
    - If we go from winning V to undefined to winning V
      - check if all other outgoing Es go to winning Vs
      - If all outgoing Es go to winning Vs, curr V is losing. Do a DFS out from it
      - Otherwise, we don't know, stop DFS from this V

```

# Edge Connectivity / Vertex Connectivity

- Definition
  - Given undirected graph G w/ n vertices and m edges
  - Edge Connectivity: λ of G = min # edge dels to disconnect G
  - S is the set of edges that disconnect G on del
  - Vertex Connectivity: κ of G = # vertices needed to disconnect T
  - A set T of vertices separates the vertices s and t, if, after removing all vertices in T from the graph G, the vertices end up in different connected components.

- Whitney Inequalities
  - δ = smallest degree of vertices
  - κ <= λ <= δ
  - If we take the endpoints of λ, we get κ

- Ford-Fulkerson
  - Biggest # of edge-disjoint paths connecting 2 vertices = smallest # edges separating the vertices

- Computing Vals
  - Max Flow
  - Iterate all pairs of V's(s,t) and find the largest # disjoint paths between them
  - Using max flow w/ each edge at capacity 1, the max flow is the # disjoint paths
  - O(V^2 * E^2)

- Stoer-Wagner
  - Calcs the global min cut
  - Same time complexity as Ford-Fulkerson
  - Split each vertex (v != s and v != t) into 2 vertices v1 and v2
  - Then connect them to v's w/ a directed edge (v1, v2) w/ capacity 1, and replace all edges (u, v) by the directed edges (u2, v1) and (u1, v2), both w/ capacity 1
  - Max Flow = min # v's to separate s & t
