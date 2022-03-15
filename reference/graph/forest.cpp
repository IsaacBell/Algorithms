/* Author: tourist */

template <typename T>
class graph {
  public:
  struct edge {
    int from;
    int to;
    T cost;
  };
 
  vector<edge> edges;
  vector< vector<int> > g;
  int n;
 
  graph(int n) : n(n) {
    g.resize(n);
  }
 
  virtual int add(int from, int to, T cost) = 0;
};

template <typename T>
class forest : public graph<T> {
  public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;
 
  forest(int n) : graph<T>(n) {
  }
 
  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = edges.size();
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};
 
template <typename T>
class dfs_forest : public forest<T> {
  public:
  using forest<T>::edges;
  using forest<T>::g;
  using forest<T>::n;
 
  vector<int> pv;
  vector<int> pe;
  vector<int> order;
  vector<int> pos;
  vector<int> end;
  vector<int> sz;
  vector<int> root;
  vector<int> depth;
  vector<T> dist;
 
  dfs_forest(int n) : forest<T>(n) {
  }
 
  void clear() {
    pv.clear();
    pe.clear();
    order.clear();
    pos.clear();
    end.clear();
    sz.clear();
    root.clear();
    depth.clear();
    dist.clear();
  }
 
  void init() {
    pv = vector<int>(n, -1);
    pe = vector<int>(n, -1);
    order.clear();
    pos = vector<int>(n, -1);
    end = vector<int>(n, -1);
    sz = vector<int>(n, 0);
    root = vector<int>(n, -1);
    depth = vector<int>(n, -1);
    dist.clear();
    dist.resize(n);
  }
 
  private:
  void do_dfs(int v) {
    pos[v] = order.size();
    order.push_back(v);
    sz[v] = 1;
    for (int id : g[v]) {
      if (id == pe[v]) {
        continue;
      }
      auto &e = edges[id];
      int to = e.from ^ e.to ^ v;
      // since this is a forest...
      assert(depth[to] == -1);
      depth[to] = depth[v] + 1;
      dist[to] = dist[v] + e.cost;
      pv[to] = v;
      pe[to] = id;
      root[to] = root[v];
      do_dfs(to);
      sz[v] += sz[to];
    }
    end[v] = order.size() - 1;
  }
 
  void do_dfs_from(int v) {
    depth[v] = 0;
    dist[v] = T{};
    root[v] = v;
    pv[v] = pe[v] = -1;
    do_dfs(v);
  }
 
  public:
  int dfs_one_unsafe(int v) {
    // run init() before this
    // then run this with the required v's
    do_dfs_from(v);
    return v;
  }
 
  int dfs(int v) {
    init();
    do_dfs_from(v);
    assert((int) order.size() == n);
    return v;
  }
 
  vector<int> dfs_all() {
    init();
    vector<int> roots;
    for (int v = 0; v < n; v++) {
      if (depth[v] == -1) {
        roots.push_back(v);
        do_dfs_from(v);
      }
    }
    assert((int) order.size() == n);
    return roots;
  }
};
 
template <typename T>
class lca_forest : public dfs_forest<T> {
  public:
  using dfs_forest<T>::edges;
  using dfs_forest<T>::g;
  using dfs_forest<T>::n;
  using dfs_forest<T>::pv;
  using dfs_forest<T>::pos;
  using dfs_forest<T>::end;
  using dfs_forest<T>::depth;
 
  int h;
  vector< vector<int> > pr;
 
  lca_forest(int n) : dfs_forest<T>(n) {
  }
 
  inline void build_lca() {
    assert(!pv.empty());
    int max_depth = 0;
    for (int i = 0; i < n; i++) {
      max_depth = max(max_depth, depth[i]);
    }
    h = 1;
    while ((1 << h) <= max_depth) {
      h++;
    }
    pr.resize(n);
    for (int i = 0; i < n; i++) {
      pr[i].resize(h);
      pr[i][0] = pv[i];
    }
    for (int j = 1; j < h; j++) {
      for (int i = 0; i < n; i++) {
        pr[i][j] = (pr[i][j - 1] == -1 ? -1 : pr[pr[i][j - 1]][j - 1]);
      }
    }
  }
 
  inline bool anc(int x, int y) {
    return (pos[x] <= pos[y] && end[y] <= end[x]);
  }
 
  inline int lca(int x, int y) {
    // maybe optimize?
    // if depth[x] > depth[y], swap
    // then go from j = log(depth[x])?
    assert(!pr.empty());
    if (anc(x, y)) {
      return x;
    }
    if (anc(y, x)) {
      return y;
    }
    for (int j = h - 1; j >= 0; j--) {
      if (pr[x][j] != -1 && !anc(pr[x][j], y)) {
        x = pr[x][j];
      }
    }
    return pr[x][0];
  }
};
 
template <typename T>
class hld_forest : public lca_forest<T> {
  public:
  using lca_forest<T>::edges;
  using lca_forest<T>::g;
  using lca_forest<T>::n;
  using lca_forest<T>::pv;
  using lca_forest<T>::sz;
  using lca_forest<T>::pos;
  using lca_forest<T>::order;
  using lca_forest<T>::depth;
  using lca_forest<T>::dfs;
  using lca_forest<T>::dfs_all;
  using lca_forest<T>::lca;
  using lca_forest<T>::build_lca;
 
  vector<int> head;
  vector<int> length_down;
  vector<int> visited;
 
  hld_forest(int n) : lca_forest<T>(n) {
    visited.resize(n);
  }
 
  void build_hld(int v) {
    if (v == -1) {
      dfs_all();
    } else {
      dfs(v);
    }
    for (int i = 0; i < n; i++) {
      if (g[i].empty()) {
        continue;
      }
      int best = -1, bid = 0;
      for (int j = 0; j < (int) g[i].size(); j++) {
        int id = g[i][j];
        int v = edges[id].from ^ edges[id].to ^ i;
        if (pv[v] != i) {
          continue;
        }
        if (sz[v] > best) {
          best = sz[v];
          bid = j;
        }
      }
      swap(g[i][0], g[i][bid]);
    }
    if (v == -1) {
      dfs_all();
    } else {
      dfs(v);
    }
    build_lca();
    head.resize(n);
    length_down.resize(n);
    for (int i = 0; i < n; i++) {
      head[i] = i;
      length_down[i] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
      int x = order[i];
      int y = order[i + 1];
      if (pv[y] == x) {
        head[y] = head[x];
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      int x = order[i];
      if (head[x] != x) {
        length_down[pv[x]] = length_down[x] + 1;
      }
    }
  }
 
  void build_hld_all() {
    build_hld(-1);
  }
 
/*
  vector< pair<int, int> > get_path(int x, int y) {
    vector< pair<int, int> > path[2];
    int z = lca(x, y);
    for (int id = 0; id < 2; id++) {
      int v = (id == 0 ? x : y);
      while (v != z) {
        if (depth[head[v]] <= depth[z]) {
          path[id].emplace_back(pos[z] + 1, pos[v]);
          break;
        }
        path[id].emplace_back(pos[head[v]], pos[v]);
        v = pv[head[v]];
      }
    }
    vector< pair<int, int> > ret;
    for (int i = 0; i < (int) path[0].size(); i++) {
      ret.emplace_back(path[0][i].second, path[0][i].first);
    }
    ret.emplace_back(-1, pos[z]);
    for (int i = (int) path[1].size() - 1; i >= 0; i--) {
      ret.push_back(path[1][i]);
    }
    return ret;
    // returns segments of the path:
    //   first from x to lca, reversed segments
    //   then (-1, pos[lca])
    //   then from lca to y, direct segments
    // but in most cases, apply_on_path should be enough
  }
*/
 
  void apply_on_path(int x, int y, bool with_lca, function<void(int,int,bool)> f) {
    // f(x, y, up): up -- whether this part of the path goes up
    int z = lca(x, y);
    {
      int v = x;
      while (v != z) {
        if (depth[head[v]] <= depth[z]) {
          f(pos[z] + 1, pos[v], true);
          break;
        }
        f(pos[head[v]], pos[v], true);
        v = pv[head[v]];
      }
    }
    if (with_lca) {
      f(pos[z], pos[z], false);
    }
    {
      int v = y;
      int cnt_visited = 0;
      while (v != z) {
        if (depth[head[v]] <= depth[z]) {
          f(pos[z] + 1, pos[v], false);
          break;
        }
        visited[cnt_visited++] = v;
        v = pv[head[v]];
      }
      for (int at = cnt_visited - 1; at >= 0; at--) {
        v = visited[at];
        f(pos[head[v]], pos[v], false);
      }
    }
  }
};
 
template <typename T>
class fenwick {
  public:
  vector<T> fenw;
  int n;
 
  fenwick(int n) : n (n) {
    fenw.resize(n);
  }
 
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};