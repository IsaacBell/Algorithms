/* 
  Original Author: tourist
  Edited by Isaac Bell
*/

template <typename T>
class graph {
public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  map<pl,ll> weightDict; // todo - use faster data structure
  vector<edge> edges;
  vvi g;
  vl dist;
  int n;

  function<bool(int)> ignore;

  graph(int _n) : n(_n) {
    g.resize(n), dist.resize(n);
    ignore = nullptr;
  }

  virtual int add(int from, int to, T cost) = 0;

  virtual void set_ignore_edge_rule(const function<bool(int)> &f) {
    ignore = f;
  }

  virtual void unset_ignore_edge_rule() {
    ignore = nullptr;
  }
};

template <typename T>
class digraph : public graph<T> {
public:
  using vt = vector<T>;

  using graph<T>::weightDict;
  using graph<T>::edges;
  using graph<T>::dist;
  using graph<T>::g;
  using graph<T>::n;
  using graph<T>::ignore;

  digraph(int _n) : graph<T>(_n) {}

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g.from.push_back(id);
    edges.push_back({from, to, cost});
    weightDict[{from, to}] = cost;
    return id;
  }

  digraph<T> reverse() {
    digraph<T> rev(n);
    for (auto &e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    if (ignore != nullptr) {
      rev.set_ignore_edge_rule([&](int id) {
        return ignore(id);
      });
    }
    return rev;
  }

  // 0-1 BFS
  // single-source shortest path w/ edge weights of 0 or 1
  T binaryBFS(ll k) {
    Fo(i,1,k+1) dist[i] = mod;
    deque<ll> q;
    q.push_front(1);
    dist[1] = 0;

    wqe {
      ll u = q.front();
      q.pop_front();
      Fo(i,1,k+1) {
        if(u == i)  continue;
        ll val = mod;
        ll dx = abs(lit[u].x - lit[i].x);
        ll dy = abs(lit[u].y - lit[i].y);
        if(dx+dy == 1) val = 0;
        else if (dx <= 2 || dy <= 2) val = 1;

        if(val <= 1 && dist[i] > dist[u] + val) {
          dist[i] = dist[u] + val;
          if(val == 1) q.push_back(i);
          else q.push_front(i);
        }
      }
    }

    if(dis[k] != mod)
      return dis[k];
    return -1;
  }

  vt bellmanFord() {
    dist[1] = 0;

    fo(j,n-1) {
      fo(i,m) {
        T value = dist[edges[i].from] + edges[i].cost;
        if(dist[edges[i].from] == -mod) value = -mod;
        if(value > dist[edges[i].to])
          dist[edges[i].to] = dist[edges[i].from] + edges[i].cost;
      }
    }

    fo(j,n-1) {
      fo(i,m) {
        T value = dist[edges[i].from] + edges[i].cost;
        if(dist[edges[i].from] == -mod) value = -mod;
        if(value > dist[edges[i].to])
          dist[edges[i].to] = mod;
      }
    }

    if(dist[n] == mod) put(-1);
    else return dist;
  }

  T dfsMaxSumPath(ll i = 0, ll tar = -1e18, ll o = 0) {
    if (tar == -1e18) tar = n;
    if (i == n) return o;
    trav(nei, g[i])
      ckmax(o, dfsMaxSumPath(tar, nei, o + weightDict[{i, nei}]) );
  }
};

template <typename T>
class undigraph : public graph<T> {
  public:
  using graph<T>::weightDict;
  using graph<T>::edges;
  using graph<T>::dist;
  using graph<T>::g;
  using graph<T>::n;

  undigraph(int _n) : graph<T>(_n) {}

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g.from.push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    weightDict[{from, to}] = cost;
    return id;
  }
};

template <typename T>
vector <T> dijkstra(const graph<T> &g, int start) {
  assert(0 <= start && start < g.n);
  vector<T> dist(g.n, numeric_limits<T>::max());
  priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > > s;
  dist[start] = 0;
  s.emplace(dist[start], start);
  while (!s.empty()) {
    T expected = s.top().first;
    int i = s.top().second;
    s.pop();
    if (dist[i] != expected) {
      continue;
    }
    for (int id : g.g[i]) {
      if (g.ignore != nullptr && g.ignore(id)) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.from ^ e.to ^ i;
      if (dist[i] + e.cost < dist[to]) {
        dist[to] = dist[i] + e.cost;
        s.emplace(dist[to], to);
      }
    }
  }
  return dist;
  // returns numeric_limits<T>::max() if there's no path
}

template <typename T>
vector< vector<int> > find_cycles(const graph<T> &g, int bound_cnt = 1 << 30, int bound_size = 1 << 30) {
  vector<int> was(g.n, -1);
  vector<int> st;
  vector< vector<int> > cycles;
  int total_size = 0;
  function<void(int, int)> dfs = [&](int v, int pe) {
    if ((int) cycles.size() >= bound_cnt || total_size >= bound_size) {
      return;
    }
    was[v] = (int) st.size();
    for (int id : g.g[v]) {
      if (id == pe || (g.ignore != nullptr && g.ignore(id))) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.from ^ e.to ^ v;
      if (was[to] >= 0) {
        vector<int> cycle(1, id);
        for (int j = was[to]; j < (int) st.size(); j++) {
          cycle.push_back(st[j]);
        }
        cycles.push_back(cycle);
        total_size += (int) cycle.size();
        if ((int) cycles.size() >= bound_cnt || total_size >= bound_size) {
          return;
        }
        continue;
      }
      if (was[to] == -1) {
        st.push_back(id);
        dfs(to, id);
        st.pop_back();
      }
    }
    was[v] = -2;
  };
  for (int i = 0; i < g.n; i++) {
    if (was[i] == -1) {
      dfs(i, -1);
    }
  }
  return cycles;
  // cycles are given by edge ids, all cycles are simple
  // breaks after getting bound_cnt cycles or total_size >= bound_size
  // digraph: finds at least one cycle in every connected component (if not broken)
  // undigraph: finds cycle basis
}
template <typename T>
vector<int> edges_to_vertices(const graph<T> &g, const vector<int> &edge_cycle) {
  int sz = (int) edge_cycle.size();
  vector<int> vertex_cycle;
  if (sz <= 2) {
    vertex_cycle.push_back(g.edges[edge_cycle[0]].from);
    if (sz == 2) {
      vertex_cycle.push_back(g.edges[edge_cycle[0]].to);
    }
  } else {
    for (int i = 0; i < sz; i++) {
      int j = (i + 1) % sz;
      auto &e = g.edges[edge_cycle[i]];
      auto &other = g.edges[edge_cycle[j]];
      if (other.from == e.from || other.to == e.from) {
        vertex_cycle.push_back(e.to);
      } else {
        vertex_cycle.push_back(e.from);
      }
    }
  }
  return vertex_cycle;
  // only for simple cycles!
}
