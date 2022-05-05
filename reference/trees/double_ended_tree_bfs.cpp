/*
  Context & Usage:

  For each node, we want to calculate maximum distance to another node.
  
  Previously we saw that that if we start a BFS from any node,
  we end up on either of the diametric end.
  
  We can use this fact to efficiently compute the answer.
  
  Let's calculate distances of each node from both the ends of the diameter.

  Then maximum distance of each node can be calculated as:

  max_distance[u] = max(
    distance_from_diametric_end1[u],
    distance_from_diametric_end2[u]
  )
*/
vl ans;

ll bfs(vvl& Adj, ll src) {
  qpl q;
  ll endpoint = -1;

  vl vis(n+1);
  vl dist(n+1);
  qp({src, 0});
  
  wqe {
    qf(i, d);
    if (vis[i]) cont;
    endpoint = i;
    vis[i] = 1;
    dist[i] = d;
    ckmax(ans[i], dist[i]);
    trav(nei, Adj[i]) qp({nei, d+1});
  }

  return endpoint;
}

void solution() {
  rd(n);
  buildAdj(n, n-1);
  ans.rsz(n+1);
  ll endpoint1 = bfs(adj, 1);
  ll endpoint2 = bfs(adj, endpoint1);
  bfs(adj, endpoint2);

  Fo(i,1,n+1) prints(ans[i]);
}
