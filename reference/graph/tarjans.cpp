typedef vector<int> vi;
typedef vector<vi> vvi;
#define pb push_back
#define MAX 100005
// C++ implementation of tarjan's algorithm for SCC
// foundat: analogous to time at which the vertex was discovered
// disc: will contain the foundat value of ith vertex(as in input graph)
// low: will contain the lowest vertex(foundat value) reachable from ith vertex(as in input graph)
// onstack: whether the vertex is on the stack st or not
// scc: will contain vectors of strongly connected vertices
// which can be iterated using
// for(auto i:scc){ // here i is a set of strongly connected component
//     for(auto j:i){ 
//         // iterate over the vertices in i
//     }
// }
ll foundat=1;
vvl Adj,scc;
vl disc,low; // init disc to -1
vb onstack(MAXN); //init to 0 

void tarjan(ll u){
    static stack<ll> st;

    disc[u]=low[u]=foundat++;
    st.push(u);
    onstack[u]=true;
    for(auto i:Adj[u]){
        if(disc[i]==-1){
            tarjan(i);
            low[u]=min(low[u],low[i]);
        }
        else if(onstack[i])
            low[u]=min(low[u],disc[i]);
    }
    if(disc[u]==low[u]){
        vi scctem;
        while(1){
            ll v=st.top();
            st.pop();onstack[v]=false;
            scctem.pb(v);
            if(u==v)
                break;
        }
        scc.pb(scctem);
    }
}

int main() {
  assert(!!MAXN);
  fo(i,n)
    if(disc[i+1]==-1)
      tarjan(i+1);

}