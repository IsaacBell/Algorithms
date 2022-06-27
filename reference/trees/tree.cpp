template <class T=int>
struct Tree {
  using pt = pair<T, T>;
  using vt = vector<T>;
  using vvt = vector<vt>;
  const int MAXN = 300005;
  const int LOG = log2(MAXN);

public:
  int n, m;
  T dist;
  vt dp;
  vb vis;
  vvt adj;
  vvt up;    // LCA jump table
  vvt Ch;    // children of node
  vt d;      // dist
  vt szz;    // size
  vt f,      // # subtrees at i
     g;      // # subtrees w/o i

  Tree<T>(int n_): n(n_), m(n_ - 1) {
    resize(n_);
  }
  Tree<T>(int n_, int m_): n(n_), m(m_) {
    resize(n_);
  }

  void resize(int n_) {
    up.rsz(LOG + 1, vt(MAXN));
    Ch.rsz(n_ + 1, vt {});
    szz.rsz(n_ + 1),
    vis.rsz(n_ + 1),
      d.rsz(n_ + 1),
      f.rsz(n_ + 1),
      g.rsz(n_ + 1),
      dp.rsz(n_ + 1);
  }

  void build(T mm = -1e9) {
    buildAdj(mm > 0 ? mm : n - 1);
  }

  // return val of node k levels up from x
  int jmp(T x, T k) {
    fo(i,LOG+1) if ((k >> i) & 1) x = up[i][x];
    return x ?: -1; // -1 if not found
  };

  void readABInput() {
    fo(i,n-1) {
      ll a,b; rd(a >> b);
      Ch[a].pb(b);
    }
  }

  void readDirected() {
    Fo(i,2,n+1) {
      ll ch; rd(ch);
      Ch[i].pb(ch);
      up[0][i] = ch;
    }

    fo(i,LOG) fo(j,n) up[i+1][j+1] = up[i][up[i][j+1]];
  }
  void readUndirected() {
    fo(i,n-1) {
      ll a,b; rd(a >> b);
      Ch[a].pb(b);
      Ch[b].pb(a);
    }

    fo(i,LOG) fo(j,n) up[i+1][j+1] = up[i][up[i][j+1]];
  }

  T diameter() {
    dfsDiameter(1,-1);
    return dist;
  }

  /*
    Find # paths, w/ K edges, from source u to sink v

    We Divide and Conquer in O(V^3 * log(K)) time w/ matrix exponentiation.

    The Kth power (Gk) of a graph (G1) has the same set of vertices
    as G1. Gk has an edge btwn 2 vertices, if there's a path of length <= k
    btwn them.

    A path of len K exists btwn u & v for every vertex where {u,v} & {w,v} are
    edges in G1.

    The {u,v}th element of Gk gives the # of K-length paths from u to v

    Usage:
      Tree<ll> tree(n);
      tree.readABInput();
      put(tree.numPathsWithKEdges(1, 4, k));
  */
  T numPathsWithKEdges(T u, T v, T k) {
    vvt res(n + 1, vt(n + 1));
    vvt G(n + 1, vt(n + 1)); // 1-0 Adj Matrix

    fo(i,n+1) res[i][i] = 1;
    fo(i,Ch.sz()) for (auto j: Ch[i]) G[i][j] = 1;

    while (k) {
      // Debug:
        // fo(i,n+1) puts(res[i]); cnl;
        // fo(i,n+1) puts(G[i]); cnl;
        // put("---");
      if (k&1) res = this->matrixMultiply(res, G);
      G = this->matrixMultiply(G, G);
      k /= 2;
    }

    // Debug:
    // fo(i,n+1) puts(res[i]); cnl;
    // fo(i,n+1) puts(G[i]); cnl;

    return res[u][v];
  }

  /*
    Processes and returns the node size array

    Usage:
      auto sizes = tree.dfsSubtreeSizes();
  */
  vt dfsSubtreeSizes() {
    Fo(i,1,n+1) if (!vis[i]) dfsSubtreeSize(i);
    return szz;
  }

  // Distance to another node, for each node i to n
  vt distanceSums() {
    dfsDP(1,-1);
    dfsDP2(1,-1);

    vt out;
    Fo(i,1,n+1) out.pb(f[i] + g[i]);
    return out;
  }

  vt ancestorQueries(int q) {
    while (q--) {
      int a,b; rd(a >> b);
      return jmp(a,b);
    }
  }

  /*
    Stores info for "infected root" tree problems

    Let 𝑑𝑝𝑖 be the maximum number of vertices we can save
    in the subtree of vertex 𝑖 if that vertex is infected
    and we use operations only in the subtree

    If 𝑐1 and 𝑐2 are the children of vertex 𝑖, the transition is

    𝑑𝑝𝑖=𝑚𝑎𝑥(𝑑𝑝𝑐1+𝑠2−1,𝑑𝑝𝑐2+𝑠1−1)
    where 𝑠𝑖 denotes the number of vertices in the subtree of 𝑖.
  */
  void calcMaxNonInfectedRoots(ll root = 1) {
    dfsSubtreeSize(root);
  }

	T centroid(T i = 1) {
		dfsCentroid(i);
		T num = szz[i];
		T p = -1;

		do {
			T nxt = -1;
			for (T nei: adj[i]) if (nei != p && !vis[nei]) {
				if (2 * szz[nei] > num)
					nxt = nei;
			}
			p = n, n = nxt;
		} while (~n);
		return p;
	}

  // Used to check if unrooted trees are isomorphic
  string encode(T i) {
    vstr tuples;
    trav(nei, adj[i])
      tuples.pb(encode(nei));
    sortall(tuples);

    string bracket_seq = "";
    trav(tup, tuples) bracket_seq += tup;

    return "(" + bracket_seq + ")";
  }

  /*
    Maximal Independent Set rooted at given vertex

    rd(n);
    Tree<ll> tree(n);
    tree.readABInput();
    put(tree.MIS());
  */
  T MIS(ll i = 1) { dfsMIS(i); ret f[i]; }

private:
  vvt buildAdj(T mm = -1e9) {
    if (mm = -1e9) mm = n-1;

    vvt A(n+1, vl {});
    fo(i,mm) {
      pt p; rd(p.F >> p.S);
      adj[p.F].pb(p.S);
      adj[p.S].pb(p.F);
    }
    adj = std::move(A);
    return adj;
  }

  void dfsSubtreeSize(T i, T p = -1) {
    if (vis[i]) ret;
    vis[i] = 1;
    szz[i] = 1;
    ll sum = 0;
    dp[i] = 0;

    trav(ch, Ch[i]) if (ch != p) {
      dfsSubtreeSize(ch, i);
      sum += dp[ch];
      szz[i] += szz[ch];
    }
    trav(ch, Ch[i])
      ckmax(dp[i], sum - dp[ch] + szz[ch] - 1);
  }

  void dfsCentroid(T i, T p = -1) {
		szz[i] = 1;
		for (T nei: adj[n]) if (nei != p && !vis[nei]) {
			dfsCentroid(nei, i);
			szz[i] += szz[nei];
		}
	}

  // maxIndependentSet()
  void dfsMIS(T i = 1, T p = -1) {
    if (vis[i]) ret;
    vis[i] = 1;
    szz[i] = 1;
    f[i] = 1;
    g[i] = 0;

    trav(ch, Ch[i]) {
      if (ch == p) continue;
      dfsMIS(ch, i);
      szz[i] += szz[ch];
      g[i] += f[ch];
      f[i] += g[ch];
    }
  }

  // Used in distance_sums()
  void dfsDP(T i, T p) {
    szz[i] = 1;
    f[i] = g[i] = 0;

    trav(ch, Ch[i]) {
      if (ch == p) continue;
      dfsDP(ch, i);
      szz[i] += szz[ch];
      f[i] += f[ch] + szz[ch];
    }
  }

  // Used in distance_sums()
  void dfsDP2(T i, T p) {
    T sum = 0;
    trav(ch, Ch[i]) if (ch != p) sum += f[ch] + szz[ch]*2;

    trav(ch, Ch[i])
      if (ch != p) {
        g[ch] = (g[i] + 1*(n - szz[i]+1)) + (sum - (f[ch] + szz[ch]*2));
        dfsDP2(ch, i);
      }
  }

  void dfsDiameter(T i, T p) {
    pq<T> q;

    trav(ch, Ch[i]) {
      if (ch == p) continue;
      dfsDiameter(ch, i);
      ckmax(f[i], f[ch] + 1);
      qp(f[ch]);
    }

    ckmax(dist, f[i]);

    if (q.sz() > 1) {
      auto mx  = q.top();
      q.pop();
      auto mx2 = q.top();
      g[i] = 2 + mx + mx2;
      ckmax(dist, g[i]);
    }
  }

  vvt matrixMultiply(vvt& a, vvt& b, T modd = mod) {
    // fo(i,n+1) deb2(a[i].sz(), b[i].sz());
    assert(a.sz() == b.sz());
		vvt c(a.sz(), vt(a.sz()));
		fo(k,a.sz())
			fo(i,a.sz())
				fo(j,a.sz())
					(c[i][j] += a[i][k] * b[k][j]) %= modd;
		return c;
	}
};
