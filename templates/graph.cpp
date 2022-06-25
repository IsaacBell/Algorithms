/* 
  Original Author: tourist
  Edited by Isaac Bell
*/

template <typename T>
class graph {
  using vt = vector<T>;
  using vvt = vector<vt>;
  using pi = pair<int, int>;
  using pt = pair<T,T>;
public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  map<pi,T> weightDict; // todo - use faster data structure
  vector<edge> edges;
  vvt g;
  vt dist;
  int n;
  int m;

  function<bool(int)> ignore;

  graph(int _n) : n(_n) {
    g.resize(n+1), dist.resize(n+1);
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
  using pt = pair<T,T>;
  using vt = vector<T>;
  using vvt = vector<vt>;

  using graph<T>::weightDict;
  using graph<T>::edges;
  using graph<T>::dist;
  using graph<T>::g;
  using graph<T>::n;
  using graph<T>::m;
  using graph<T>::ignore;

  vt par;
  vt vis;
  vt dfsNum;
  vt dfsLow;

  const T UNVISITED = -1;
  const T EXPLORED = 0;
  const T VISITED = 1;

  digraph(int _n) : graph<T>(_n) {
    m = n - 1;
    g.rsz(n + 1, vt {});

    par.rsz(_n + 1, UNVISITED),
    vis.rsz(_n + 1, UNVISITED),
    dist.rsz(_n + 1, mod),
    dfsNum.rsz(_n + 1),
    dfsLow.rsz(_n + 1);
  }

  void read(int m_) {
    m = m_;
    fo(i,m_) {
      ll a, b; rd(a >> b);
      add(a,b);
    }
  }
  void readWeighted(int m_) {
    m = m_;
    fo(i,m_) {
      ll a, b, c; rd(a >> b >> c);
      add(a,b,c);
    }
  }

  // Note - "m" won't be set if you call this directly,
  // so set it manually e.g.: `myGraph.m = 7;`
  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from <= n && 0 <= to && to <= n);
    int id = (int) edges.size();
    // g[from].pb(id);

    g[from].pb(to);
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

  /*
  	0-1 BFS
  	SSSP to all vertices, given edge weights of 0 or 1

    Returns the `dist` array, note this array is 1-indexed
  */
  vt binaryBFS(ll src = 1) {
    fill(all(dist), mod);
    deque<ll> q;
    q.push_front(src);
    dist[src] = 0;

    wqe {
      ll u = q.front();
      q.pop_front();
      Fo(i, 1, g[u].sz()) {
        if(u == i)  continue;

        if(dist[i] > dist[u] + weightDict[{u,i}]) {
          dist[i] = dist[u] + weightDict[{u,i}];
          
          // process deque in ASC weight order
          if(weightDict[{u,i}] == 1) q.push_back(i);
          else q.push_front(i);
        }
      }
    }

    return dist;
  }

  /*
    Length of shortest paths from vertex v to a target vertex,
    handling the possibility of negative weight cycles

    Prefer Djikstra's when negative elements not present
    
    Use the dist[] array to see results for every other vertex

    auto [distance, path] = G.bellmanFord(1, n);
  */
  pair<T, vt> bellmanFord(ll v, ll t) {
    fill(all(dist), mod);
    dist[v] = 0;

    for (;;) {
      bool any = false;
      fo(j,m) {
        if (dist[edges[j].from] < mod) {
          if (dist[edges[j].to] > dist[edges[j].from] + edges[j].cost) {
            dist[edges[j].to] = dist[edges[j].from] + edges[j].cost;
            par[edges[j].to] = edges[j].from;
            any = true;
          }
        }
      }
      if (!any)  break;
    }
    puts(dist);

    if (dist[t] == mod)
      return {-1, {}};
    
    vt path;
    for (auto cur = t; cur != -1; cur = par[cur])
      path.pb(cur);
    std::reverse(all(path));
    return {dist[t], path};
  }

  T dfsMaxSumPath(ll i = 0, ll tar = -1e18, ll o = 0) {
    if (tar == -1e18) tar = n;
    if (i == n) return o;
    trav(nei, g[i])
      ckmax(o, dfsMaxSumPath(tar, nei, o + weightDict[{i, nei}]) );
  }

  // Back Edges:
    // if EXPLORED -> EXPLORED, nei is ancestor of p
    // if par[nei] == u, cycle is a bi-directional edge
  void cycleCheck(ll u) {
    dfsNum[u] = EXPLORED;
    trav(nei, g[u]) {
      if (dfsNum[nei] == UNVISITED) {
        par[nei] = u;
        cycleCheck(nei);
      } else if (dfsNum[nei] == EXPLORED)
        if (nei == par[u]) {} // Bi-directional edge
        else {} // Back Edge
      else if (dfsNum[nei] == VISITED) {} // Forward Edge (rarely useful in CP)

      dfsNum[nei] = VISITED;
    }
  }

  /*
    O(V^3 * K)
    
    Use a 3D matrix table to store cost of shortest path.
    dp[i][j][e] = SP from i to j w/ e edges
    Base Case: dp[i][j][e] = 0

    If i == j && !e, there's no path so cost is 0.
    If there's an edge i->j, cost of SP is cost of i->j
  */
  T minCostPathWithKEdges(T u, T v, T k) {
    T dp[n+1][n+1][k+1];
    vvt G(n + 1, vt(n + 1)); // 1-0 Adj Matrix
    fo(i,g.sz()) for (auto j: g[i]) G[i][j] = 1;
    
    // fo(i, n+1) {puts(G[i]); cnl;}

    fo(e, k+1)
      fo(i, n+1)
        fo(j, n+1) {
          dp[i][j][e] = mod;
          if (!e && i == j) dp[i][j][e] = 0;
          if (e == 1 && weightDict[{i,j}])
            dp[i][j][e] = weightDict[{i,j}];
          
      	  // go to adjacent when # edges > 1
          if (e > 1)
            fo(b, n+1)
              // There should be an edge from i to b.
              // b should not be same as either i or j.
              if (
                weightDict[{i,b}] && 
                b != i && 
                b != j && 
                dp[b][j][e-1] != mod
              ) {
                ckmin(dp[i][j][e], dp[b][j][e-1] + weightDict[{i,b}]);
              }
        }

    return dp[u][v][k];
  }
};

template <typename T>
class undigraph : public graph<T> {
  using vt = vector<T>;

public:
  using graph<T>::weightDict;
  using graph<T>::edges;
  using graph<T>::dist;
  using graph<T>::g;
  using graph<T>::n;

  vt par;
  vt vis;
  vt dfsNum;
  vt dfsLow;
  vt articulation_vertex;

  const T UNVISITED = -1;
  const T EXPLORED = 0;
  const T VISITED = 1;

  T dfsCnt;
  T dfsRoot = -1;
  T rootChildren;
  T m = 0;

  undigraph(int _n) : graph<T>(_n) {
    dfsCnt = 0, rootChildren = 0;
    par.rsz(_n + 1, UNVISITED),
    vis.rsz(_n + 1, UNVISITED),
    articulation_vertex.rsz(_n + 1),
    dfsNum.rsz(_n + 1),
    dfsLow.rsz(_n + 1);
  }

  void read(int m_) {
    m = m_;
    fo(i,m_) {
      ll a, b; rd(a >> b);
      add(a,b);
      add(b,a);
    }
  }
  void readWeighted(int m_) {
    m = m_;
    fo(i,m_) {
      ll a, b, c; rd(a >> b >> c);
      add(a,b,c);
      add(b,a,c);
    }
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from <= n && 0 <= to && to <= n);
    int id = (int) edges.size();
    g[from].push_back(to);
    g[to].push_back(from);
    edges.push_back({from, to, cost});
    weightDict[{from, to}] = cost;
    return id;
  }

  vt articulationPtsAndBridges() {
    dfsCnt = 0;
    vt out;
    fo(i,n) {
      if (dfsNum[i] == UNVISITED) {
        dfsRoot = i; rootChildren = 0;
        dfsArticulationPtsAndBridges(i);
        articulation_vertex[dfsRoot] = rootChildren > 1;
      }
    }
    fo(i,n) if (articulation_vertex[i]) out.pb(i);
    return out;
  }

  void dfsArticulationPtsAndBridges(ll u) {
    assert(dfsRoot != -1); // set this to 1 or 0
    dfsNum[u] = dfsCnt++;
    dfsLow[u] = dfsNum[u];
    trav(nei, g[u]) {
      if (dfsNum[nei] == UNVISITED) {
        par[nei] = u;
        if (u == dfsRoot) rootChildren++;
        articulationPtsAndBridges(nei);

        if (dfsLow[nei] >= dfsLow[u])
          articulation_vertex[u] = 1;
        if (dfsLow[nei] > dfsNum[u]) {} // Edge u->v is a bridge
        ckmin(dfsLow[u], dfsLow[nei]);
      } else if (nei != par[u])
        ckmin(dfsLow[u], dfsNum[nei]);
    }
  }

  T num_connected_components() {
    T cnt = 0;
    vb used(n);
    stack<T> stk;

    fo(i, n) if (not used[i]) {
      cnt++;
      used[i] = true;
      stk.push(i);

      while (not stk.empty()) {
        T x = stk.top();
        stk.pop();
        for (T nei : g[x]) if (not used[nei]) {
          used[nei] = true;
          stk.push(nei);
        }
      }
    }

    return cnt;
  }

  bool is_connected_graph() {
    return num_connected_components(g) == 1;
  }
};

/*
  Bipartite Maximum Matching Implementation:

  rd(n);
  bigraph<ll> G(n);
  G.read();
  put(G.maximumMatching());
*/

template <class T>
class bigraph : public graph<T> {

public:
  // n: number of nodes on left side, nodes are numbered 1 to n
  // m: number of nodes on right side, nodes are numbered n+1 to n+m
  // G = 0[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

  using vt = std::vector<T>;
  using vvt = std::vector<vt>;

  using graph<T>::weightDict;
  // using graph<T>::edges;
  using graph<T>::dist;
  using graph<T>::g;
  using graph<T>::n;
  using graph<T>::ignore;
  
  vt match;
  vvt adjInput;
  const T MAXN = 1e6;
  int m;

  bigraph(int n_): graph<T>(n_) {
    adjInput.rsz(MAXN, vt {});
    g.rsz(MAXN, vt {});
    dist.rsz(MAXN);
    match.rsz(MAXN);
  }

  int add(int from, int to, T cost) {
    // static_assert (fail<T>::value, "Do not use!");
    return 0;
  }

  void read() {
    fo(i, n - 1) {
      ll a, b;
      rd(a >> b);
      adjInput[a].pb(b);
      adjInput[b].pb(a);
    }
  }

  bool bfs_hopcroft_karp() {
    int i, u, v, len;
    queue<int> q;
    Fo(i,1,n+1) {
      if(!match[i]) {
        dist[i] = 0;
        qp(i);
      }
      else dist[i] = mod;
    }

    dist[0] = mod;

    wqe {
      u = q.front();
      q.pop();
      if(u != 0) {
        len = g[u].size();
        fo(i,len) {
          v = g[u][i];
          if(dist[match[v]] == mod) {
            dist[match[v]] = dist[u] + 1;
            qp(match[v]);
          }
        }
      }
    }

    return (dist[0] !=  mod);
  }

  bool dfs_hopcroft_karp(int u) {
    int i, v, len;
    if(u != 0) {
      len = g[u].size();
      fo(i, len) {
        v = g[u][i];
        if(dist[match[v]]==dist[u]+1) {
          if(dfs_hopcroft_karp(match[v])) {
            match[v] = u;
            match[u] = v;
            return true;
          }
        }
      }
      dist[u] = mod;
      return false;
    }

    return true;
  }

  void make_bipartite_dfs(int u, int p, int l) {
    if(l%2 and p != -1) {
        g[u].push_back(p+n);
        g[p+n].push_back(u);
    }
    for(int v: adjInput[u]) {
      if(v != p) {
        if(l & 1) {
          g[u].push_back(v+n);
          g[v+n].push_back(u);
        }

        make_bipartite_dfs(v, u, l+1);
      }
  }
}

  // Maximum bipartite matching
  int hopcroft_karp() {
    int matching = 0, i;
    // match[] is assumed 0 for all vertex in G
    while(bfs_hopcroft_karp())
      Fo(i,1,n+1)
        if(match[i] == 0 && dfs_hopcroft_karp(i))
          matching++;
    return matching;
  }

  int maximumMatching() {
    make_bipartite_dfs(1, -1, 1);
    return hopcroft_karp();
  }

// private:
//   template <typename FailType>
//   struct fail : std::false_type {};
};

template <typename T>
vector<T> dijkstra(const graph<T> &g, int start = 1) {
  assert(0 <= start && start <= g.n);
  vector<T> dist(g.n+1, mod);
  priority_queue<
    pair<T, int>,
    vector<pair<T, int>>,
    greater<pair<T, int>>
  > q;
  dist[start] = 0;
  q.emplace(dist[start], start);
  wqe {
    qt(expected, i);
    if (dist[i] != expected) continue;
    trav(nei, g.g[i]) {
      if (dist[i] + g.weightDict[{i,nei}] < dist[nei]) {
        dist[nei] = dist[i] + g.weightDict[{i,nei}];
        q.emplace(dist[nei], nei);
      }
    }
  }
  return dist;
  // returns mod if there's no path
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
