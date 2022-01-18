#include<bits/stdc++.h>
using namespace std;
#define SZ 200005
 
int n, m, k, x, SQRT, ans, u, v;
vector<int> arr;
vector<int> adj[SZ];
int col[SZ];
int start[SZ];
int finish[SZ];
int t = -1;
 
int freq[SZ];
int query_ans[SZ];

struct node{
	int L,R,i;
} query[SZ];
 
void dfs_flatten(int u, int p) {
	start[u] = ++t;
	arr.push_back(col[u]);
	for(int v: adj[u]) {
		if(v-p)
		dfs_flatten(v, u);
	}
	finish[u] = t;
}
 
void map_colors(int col[]) {
	map<int, int> prev_to_new;
	vector<int> copy_col(col+1, col+1+n);
	sort(copy_col.begin(), copy_col.end());
	for(int i = 0; i < n; i++) {
		prev_to_new[copy_col[i]] = i;
	}
	for(int i = 1; i <= n ; i++) {
		col[i] = prev_to_new[col[i]];
	}
}
 
bool cmp(node a,node b) {
	if (a.L/SQRT != b.L/SQRT)
	return a.L < b.L;
	return a.R < b.R;
}
 
void add(int pos) {
	freq[arr[pos]]++;
	if(freq[arr[pos]]==1)
	ans++;
}
 
void remove(int pos) {
	freq[arr[pos]]--;
	if(freq[arr[pos]]==0)
	ans--;
}
 
void mos_algorithm() {
	sort(query+1, query+1+n, cmp);
	int currentL = 0, currentR = 0, L, R;
	add(0);
	
	for(int i=1; i<=n; i++){
		L=query[i].L;
		R=query[i].R;
		
		while(currentL < L) 
		remove(currentL++);
		
		while(currentL > L) 
		add(--currentL);
		
		while(currentR < R) 
		add(++currentR);
		
		while(currentR > R) 
		remove(currentR--);
				
		query_ans[query[i].i]=ans;
	}
}
 
int main() {
	cin >> n;
	SQRT=floor(sqrt(n));
 
	for(int i = 1; i <= n; i++) {
		cin >> col[i];
	}
	map_colors(col);
	
	for(int i = 0; i < n-1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs_flatten(1, 0);
 
	for(int i = 1; i <= n; i++) {
		query[i].L = start[i];
		query[i].R = finish[i];
		query[i].i = i;
	}
 
	mos_algorithm();
 
	for(int i=1; i<=n; i++)
	cout << query_ans[i] << " ";
}