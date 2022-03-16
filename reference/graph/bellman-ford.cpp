vl bellman_ford_shortest_path(int root, vvpi const& g) {
  assert (not g.empty());
  int n = g.size();
  vl dist(n, mod);

  // update n - 1 times
  dist[root] = 0;
  fo (iteration, n - 1) {
    fo (i, n) if (dist[i] != mod) {
      for (auto edge : g[i]) {
        int j; int64_t cost; std::tie(j, cost) = edge;
        dist[j] = std::min(dist[j], dist[i] + cost);
      }
    }
  }

  // propagate effects of negative cycles
  std::stack<int> stk;
  fo (i, n) if (dist[i] != mod) stk.push(i);

  while (!stk.empty()) {
    int i = stk.top();
    stk.pop();
    for (auto edge : g[i]) {
      int j; int64_t cost; std::tie(j, cost) = edge;
      if (dist[j] != -mod) {
        if (dist[i] == -mod or dist[i] + cost < dist[j]) {
          dist[j] = -mod;
          stk.push(j);
        }
      }
    }
  }

  return dist;
}
