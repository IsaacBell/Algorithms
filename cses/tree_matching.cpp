// #include<bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <complex>
#include <chrono>
#include <functional>
#include <climits>
#include <utility>
#include <limits>
#include <random>
#include <numeric>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define nl "\n"
#define cnl cout << nl
#define NL cnl
#define sz size
#define rsz resize
#define ret return
#define cont continue
#define IMAX INT_MAX
#define IMIN INT_MIN
#define gc getchar_unlocked
#define ll int64_t
#define PI 3.1415926535897932384626
#define INF 2000000000
#define szn(n, s) const ll n = s.sz()
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define br printf("\n")
#define trav(a, x) for (auto &a : x)
#define fo(i, n) for(ll i=0;i<n;i++)
#define ford(i, n) for(ll i = n - 1; i >= 0; i--)
#define ford1(i, n) for(ll i = n - 1; i; i--)
#define Fo(i, k, n) for(ll i = k; k < n ? i < n : i > n; k < n ? i += 1: i -= 1)
#define deb(x) cout << #x << " = " << x << endl;
#define deb2(x, y) cout << #x << " = " << x << ", " << #y << " = " << y << endl
#define deba(i, a, n) fo(i, n){cout << a[i] << " ";}
#define rd(x) cin >> x
#define readall(x) trav(elem, x) cin >> elem
#define print(x) cout << x
#define prints(x) cout << x << " "
#define put(x) cout << x << nl
#define puts(x) trav(elem, x) cout << elem << " ";
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second
#define FR front
#define BK back
#define qt(args...) auto [args] = q.top(); q.pop();
#define qta(arg...) auto arg = q.top(); q.pop();
#define qf(args...) auto [args] = q.front(); q.pop();
#define qp(args...) q.push(args)
#define qe q.empty()
#define wqe while(!q.empty())
#define stktop stk.top()
#define stkpush(args...) stk.push(args)
#define stkpop stk.pop()
#define stke stk.empty()
#define wse while(!stk.empty())
#define begend(x) all(x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, x) for(auto it = x.begin(); it != x.end(); it++)
#define trr(it, x) for(auto it = x.rbegin(); it != x.rend(); it+)
#define getunique(v) {sort(all(v)); v.erase(unique(all(v)), v.end());}
#define nextgreateridx(A, val) lower_bound(all(A), val)) - A.begin()
#define putNo put("NO"); ret
#define putYes put("YES"); ret
#define oo0 ll o = 0
#define oomx ll o = mod
#define oomn ll o = -mod
#define vlo vl o
#define vlon(n) vl o(n)
#define vlonx(n, x) vl o(n, x)
#define oov(n, x) vl o(n, x)
#define opb o.pb
#define osz o.sz()
#define posz put(o.sz())

typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef tuple<ll,ll,ll> tll;
typedef vector<tll> vtll;
typedef vector<vtll> vvtll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vl vll;
typedef vector<string> vstr;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vpl> vvpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<ld> vd;
typedef vector<cd> vcd;
typedef vector<uint32_t> vu32;
typedef vector<uint64_t> vu64;
typedef map<ll, ll> mll;
typedef map<ll, string> mls;
typedef map<string, ll> msl;

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
  uniform_int_distribution<int> uid(0,lim-1);
  return uid(rang);
}

const ll mod = 1e9 + 7;
const ll N = 3e5;

template<typename T=ll> using ql  = queue<ll>;
template<typename T=ll> using qp  = queue<pair<T,T>>;
template<typename T=ll> using qt  = queue<tuple<T,T>>;
template<typename T=ll> using qt3 = queue<tuple<T,T,T>>;
template<typename T=ll> using qt4 = queue<tuple<T,T,T,T>>;
template<typename T=ll> using pq  = priority_queue<T>;
template<typename T=ll> using mpq = priority_queue<T, vector<T>, greater<T>>;

using qll  = queue<ll>;
using qpl  = qp<ll>;
using qtl  = qt<ll>;
using qtl3 = qt3<ll>;
using qtl4 = qt4<ll>;
using qpd  = qp<double>;
using qtd  = qt<double>;
using qtd3 = qt3<double>;
using qtd4 = qt4<double>;

// Modulo operators
template<typename T=ll> T M(T x) { return ((x % mod + mod) % mod);  }
template<typename T=ll> T addM(T a, T b)  { return M(M(a) + M(b)); }
template<typename T=ll> T subM(T a, T b)  { a -= b; return a < 0 ? a + mod : a; }
template<typename T=ll> T multM(T a, T b) { return M(M(a) * M(b)); }
template<typename T=ll> T powM(T x, T y) {
  T o = 1;
  x %= mod;
  while (y) {
    if (y & 1) (o *= x) %= mod;
    y >>= 1;
    (x *= x) %= mod;
  }
  return o;
}

// General functions
template<class T=ll> T gcd(T a, T b) { return b ? gcd(b, a%b) : a; }
template<class T=ll> T lcm(T a, T b) { return a*(b/gcd(a,b)); }
template<typename T=ll> bool ckmin(T& a, T b){ return b < a ? a = b, true : false; }
template<typename T=ll> bool ckmax(T& a, T b){ return b > a ? a = b, true : false; }

template<class T=ll> T maxpow2(T n) { return (n & (~(n - 1))); }
template<class T=ll> T count_digit(T number) { return T(log10(number) + 1); }
template<class T=ll> T sum_digit(T n) {
  T sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}

template<class T=ll>
T sum_digit_string(string str)
{
    T sum = 0;
    for (T i = 0; i < str.length(); i++)
    {
        sum = sum + str[i] - 48;
    }
    return sum;
}

template<class T=ll> string dec2bin(T n)
{
    const T size=sizeof(n)*8;
    string s = "00000000000000000000000000000000";
    for (T a=0;a<32;a++)
    {
        if(n==0)
            return s;
        else
        {
            if(n%2!=0)
                s[31-a]='1';
            n/=2;
        }
    }
    return s;
}

template<typename T = ll>
T fac(T x) { // factorial
  T o = 1;
  if (x > 0)
    for(T i = 1; i <= x; ++i)
        o = multM<T>(o,i);
  return o;
}

bool comp2nd(pl& A, pl& B) { return A.S < B.S; }

template <class T = ll>
T binpow(T a, T b) {
  T res = 1;
  while (b > 0) {
      if (b & 1)
          res = res * a;
      a = a * a;
      b >>= 1;
  }
  return res;
}

template <class T = ll>
T binpowmod(T a, T b, T modd = mod) {
  T res = 1;
  while (b > 0) {
      if (b & 1)
          res = (res * a) % modd;
      a = (a * a) % modd;
      b >>= 1;
  }
  return res;
}

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
bool ok(int n, int m, int x, int y) { return x >= 0 && y >= 0 && x < n && y < m; }
/* Grid traversal
fo(i,4) {
  newX = x + dx[i]; newY = y + dy[i];
  if (ok(n, m, newX, newY)) ...
}
*/

vvl adj;
vl inDeg(N);

/*
buildAdj(n,m,1); // DAG
buildAdj(n,m,0); // UAG

Sets adjacency list and inDegree counts
*/
void buildAdj(ll nn, ll mm, bool dag = false) {
  vvl A(nn+1, vl {});
  fo(i,mm) {
    pl p; rd(p.F >> p.S);
    A[p.F].pb(p.S);
    if (!dag) A[p.S].pb(p.F);
    
    if (!dag) inDeg[p.F]++; 
    inDeg[p.S]++;
  }
  adj = std::move(A);
}

ll msb (ll n) {
  ll k = 0;
  while((1 << (k + 1)) <= n - 1) ++k;
  return k;
}

/* Solution starts here */

// vl v(N);
// vl p(N, -1);
// vl szz(N);
// vl anc(N);
// bitset<N> vis;
// bitset<N> bs;

// ll timer = 0;
// vl tin, tout;

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

ll a, b, c, n, m, k, w;
string s, t;

void solution() {
  rd(n);
  bigraph<int> G(n);
  G.read();
  put(G.maximumMatching());
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  ll t = 1;
  // rd(t);

  while(t--)
    solution();

  return 0;
}
