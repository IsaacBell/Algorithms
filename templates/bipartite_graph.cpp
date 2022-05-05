/*
  Bipartite Maximum Matching Implementation:

  void solution() {
    rd(n);
    bigraph<int> G(n);
    G.read();
    put(G.maximumMatching());
  }
*/

template <typename T>
class graph {
  using pt = pair<T,T>;
  using vt = vector<T>;
  using vvt = vector<vt>;
public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  map<pt,T> weightDict; // todo - use faster data structure
  vector<edge> edges;
  vvt g;
  vt dist;
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
