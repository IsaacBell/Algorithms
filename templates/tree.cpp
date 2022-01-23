/* Solution starts here */
vvl Adj(N, vl {});
vvl Ch(N,  vl {});

vl tree(N), // subTree size
   d(N);    // depth

vl f(N), g(N);

void dfs(ll i, ll p = -1) {
}

void solution() {
  cin >> n;
  Fo(i,1,n) {
    cin >> a >> b;
    a--; b--;
    Adj[a].pb(b);
    Adj[b].pb(a);
  }

  dfs(0);
}
