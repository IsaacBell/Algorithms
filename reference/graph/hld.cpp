// HLD (Heavy-light decomposition) start
int in[MAXN],out[MAXN],tmr=-1;
int prt[MAXN],sz[MAXN],dep[MAXN];
int top[MAXN];

void dfs_sz(int u, int p)
{
	sz[u] = 1;
	prt[u] = p;
	if(adj[u].size()>1 && adj[u][0]==p) swap(adj[u][0], adj[u][1]);
	
	for(auto &v: adj[u])
	{
		if(v == p) continue;
		dep[v] = dep[u] + 1;
		dfs_sz(v, u);
		sz[u] += sz[v];
		if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
	}
}
void dfs_hld(int u, int p)
{
	if(p == -1) top[u] = u;
	in[u] = ++tmr;
	for(int v: adj[u])
	{
		if(v == p) continue;
		top[v] = (v == adj[u][0]) ? top[u] : v;
		dfs_hld(v, u);
	}
	out[u] = tmr;
}
inline void init_hld(int rt){ dfs_sz(rt, -1); dfs_hld(rt, -1); }
inline ll merge_hld(ll x, ll y){ return x + y; }
ll Query(int u, int v)
{
	ll ans = 0; // dummy value
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ans = merge_hld(ans, st.query(in[top[u]], in[u]));
		u = prt[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	return merge_hld(ans, st.query(in[v], in[u]));
}
// For lazy segtree, untested (I can't find problems to test)
void Update(int u, int v, ll val)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		st.update(in[top[u]], in[u], val);
		u = prt[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	st.update(in[v], in[u], val);
}

// init_hld(root) -> update/queries
// Point update: st.update(in[u],w);
// Update, Query: Range update/query on the path between u, v
// HLD (Heavy-light decomposition) end