// Created by proof on 2020-10-10 13:59.
#include <bits/stdc++.h>
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
using namespace std;

class bipartite_matching {
public:
  const int32_t n, m;
  vector<vector<int32_t>> g;
  vector<int32_t> pa;
  vector<int32_t> pb;
  vector<int32_t> was;
  int32_t cardinality = 0;
  int32_t iter = 0;

  bipartite_matching(const int32_t n, const int32_t m)
      : n(n), m(m), g(n), pa(n, -1), pb(m, -1), was(n, 0) {
    assert(0 <= n);
    assert(0 <= m);
  }

  void add(const int32_t from, const int32_t to) {
    assert(0 <= from and from < n);
    assert(0 <= to and to < m);
    g[from].push_back(to);
  }

  bool dfs(const int32_t x) {
    was[x] = iter;
    for (int32_t y : g[x]) {
      if (pb[y] == -1) {
        pa[x] = y;
        pb[y] = x;
        return true;
      }
    }
    for (int32_t y : g[x]) {
      if (was[pb[y]] != iter and dfs(pb[y])) {
        pa[x] = y;
        pb[y] = x;
        return true;
      }
    }
    return false;
  }

  int32_t match() {
    while (true) {
      bool again = false;
      iter++;
      for (int32_t x = 0; x < n; x++) {
        if (pa[x] == -1 and dfs(x)) {
          cardinality++;
          again = true;
        }
      }
      if (not again) {
        break;
      }
    }
    return cardinality;
  }

  int32_t once(const int32_t x) {
    assert(0 <= x and x < n);
    if (pa[x] == -1) {
      return 0;
    }
    iter++;
    int32_t augment = dfs(x);
    cardinality += augment;
    return augment;
  }
};

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  struct road {
    int from;
    int to;
    int days;
  };
  int n, m;
  cin >> n >> m;

  vector<road> roads(m);

  for (road &r : roads) {
    cin >> r.from >> r.to >> r.days;
    r.from--;
    r.to--;
  }
  sort(roads.begin(), roads.end(),
       [&](const road &a, const road &b) { return a.days < b.days; });

  auto solved = [&](int t) -> bool {
    assert(0 <= n);
    assert(0 <= t and t < m);
    bipartite_matching bim(n, n);
    for (int i = 0; i <= t; i++) {
      bim.add(roads[i].from, roads[i].to);
    }
    return bim.match() == n;
  };
  if (not solved(m - 1)) {
    cout << -1 << "\n";
    return 0;
  }
  int lo = 0, hi = m - 1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (solved(mid)) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  cout << roads[lo].days << "\n";
#ifdef LOCAL
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
