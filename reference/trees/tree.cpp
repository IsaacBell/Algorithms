template <class T=int>
struct Tree {
  using pt = pair<T, T>;
  using vt = vector<T>;
  using vvt = vector<vt>;
  const int MAXN = 2e5;
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
    up.rsz(LOG+1, vt(MAXN));
    Ch.rsz(n+1, vl {});
    szz.rsz(n+1),
    vis.rsz(n+1),
      d.rsz(n+1),
      f.rsz(n+1),
      g.rsz(n+1),
      dp.rsz(n+1);
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
  void calcMaxNonInfectedRoots(ll i = 1) {
    dfsSubtreeSize(i);
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
};
