/*
  Reads a graph as std input on construction. Can detect whether the graph is
  bipartite

  Params:
    T: Vertex Data type
    root: Root vertex offset # (e.g. 1 if starting from root of 1)

  Example:
  BipartiteGraph<ll, 1> G(n,m);
  if (G.isBipartite())
    put("YES" << nl << G.as_binary_string());
*/
template <class T = ll, int root = 1>
struct BipartiteGraph {
  using pt = pair<T, T>;
  using vt = vector<T>;
  using vvt = vector<vt>;
  using vpt = vector<pt>;

  t n, m;
  vvt adj;
  vpt edges;
  vt group; // is el in group 0 or group 1?
  
  void build(T nn, T mm) {
    vvt A(nn+1, vl {});
    vpt pp(mm);
    fo(i,mm) {
      pl p; rd(p.F >> p.S);
      A[p.F].pb(p.S);
      A[p.S].pb(p.F);
      pp[i] = p;
    }
    
    group.rsz(n+1, 0);
    edges = std::move(pp);
    adj = std::move(A);
  }

  BipartiteGraph<T, root>(T _n, T _m = -1): n(_n), m(_m) {
    build(n+root, m);
  }
  BipartiteGraph<T, root>(
    T _n,
    T _m,
    vvt& adj
  ): n(_n+root), m(_m), adj(adj) {
    group.rsz(n+1, 0);
  }

  bool isBipartite() {
    bool yes = true;

    vt side(n+root, -1);
    qll q;
    Fo(st,root,n+root) {
      if (side[st] == -1) {
        qp(st);
        side[st] = 0;
        wqe {
          auto i = q.front(); q.pop();
          trav(nei, adj[i])
            if (side[nei] == -1) side[nei] = side[i] ^ 1, qp(nei);
            else yes &= side[nei] != side[i];
        }
      }
    }
    group = side;
    
    /* 
      Uncomment for debugging

      for (auto [i,j]: edges) deb2(i,j);
      puts(side);cnl;
      put(str);
    */

    return yes;
  }
  
  /* 
    The 𝑖-th element of this string should be '0' if the 𝑖-th edge 
    of the graph should be directed from 𝑢𝑖 to 𝑣𝑖, and '1' otherwise. 
    
    Edges are displayed in the order they are given in the input
    
    Example:
    if (graph.isBipartite()) cout << graph.as_binary_string();
  */
  string as_binary_string() {
    string str = "";
    for (auto [i,j]: edges) str += (group[i] < group[j] ? '1' : '0');
    return str;
  }
};
