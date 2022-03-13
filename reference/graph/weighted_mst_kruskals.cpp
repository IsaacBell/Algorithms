// Created by proofbycontradiction on 2019-01-24 01:18.
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define all(x) (x).begin(), (x).end()

template<class T, size_t n> ostream &operator<<(ostream &os, array<T, n> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.first << "," << P.second << ")";
}
template<class T> ostream &operator<<(ostream &os, set<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class K, class X> ostream &operator<<(ostream& os, map<K,X> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail...T) { cerr << " " << H; debug_out(T...); }

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

using ii = pair<int, int>;
using vb = vector<bool>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

class dsu {
  int n;
  vi e;

 public:
  dsu (int n): n(n), e(n, -1) { }

  int find(int x) {
    return (e[x] < 0) ? x : (e[x] = find(e[x]));
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return true;
  }
};

struct edge {
  int from, to, cost;

  inline bool operator<(const edge &o) const {
    return cost < o.cost;
  }
};

int32_t main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n; cin >> n;
  int m; cin >> m;
  vector<edge> edges;

  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    edges.push_back({from - 1, to - 1, cost});
  }
  sort(all(edges));
  dsu kruskal(n);
  dsu less(n);
  int cost = 0;
  vector<vector<edge>> same;
  for (auto &e: edges) {
    if (e.cost == cost) {
      same.back().push_back(e);
    } else {
      cost = e.cost;
      same.push_back({e});
    }
  }
  int ans = 0;
  for (auto &samev: same) {
    for (auto &e: samev) {
      if (kruskal.find(e.from) == kruskal.find(e.to)) {
        if (less.find(e.from) != less.find(e.to)) {
          ans++;
        }
      }
      kruskal.unite(e.from, e.to);
    }
    for (auto &e: samev) {
      less.unite(e.from, e.to);
    }
  }
  cout << ans << endl;
}
