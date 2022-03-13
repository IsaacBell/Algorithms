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
#define print(x) cout << x << " "
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
#define begend(x) all(x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, x) for(auto it = x.begin(); it != x.end(); it++)
#define trr(it, x) for(auto it = x.rbegin(); it != x.rend(); it+)
#define getunique(v) {sort(all(v)); v.erase(unique(all(v)), v.end());}
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
  if(b == 0) return 1;
  T ans = binpowmod(a,b/2,modd);
  ans *= ans;
  ans %= modd;
  if(b % 2) ans *= a;
  return ans % modd;
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

/* Solution starts here */

struct SuffixAuto {
  struct State {
    int len, link;
    int next[26];
    State(int _len = 0, int _link = -1) : len(_len), link(_link) {
      memset(next, -1, sizeof(next));
    }
  };
 
  vector<State> states;
  vl dp;  // dp[u]: # non-distinct substrings starting at node u
  vl cnt; // # times a state appears in the string
  int last, K;
  const string str;
  const int n;
 
  SuffixAuto(const string &S_): str(S_), n(S_.sz()) {
    dp.rsz(N), cnt.rsz(N);
    init(S_);
  }
 
  inline int state(int len = 0, int link = -1) {
    states.emplace_back(len, link);
    return states.size() - 1;
  }

  ll numDistinctSubstrings() {
    return dfs(0) - 1;
  }

  string kthLexicographicallySmallestSubstr(ll K) {
    string str_ = "";
    //dp.clear();
    dfs();
    dfsKthSmallestSubstr(K, str_);
    return str_;
  }

  string kthLexicographicallySmallestNondistinctSubstr(ll K) {
    string str_ = "";
    //dp.clear();
    dfsCnt();
    dfsKthSmallestNondistinctSubstr(K, str_);
    return str_;
  }

  // For every i 1…n, get # distinct substrings of length i
  vl substringDistribution(bool shouldPrintResult = 0) {
    qll q;
    vl lb(3e6, -1), ans(n+1);
 
    qp(0);
    lb[0] = 0;
    wqe {
      auto u = q.front(); q.pop();
      auto d = lb[u];
      fo(i, 26) {
        auto v = states[u].next[i];
        if (v != -1 && lb[v] == -1) {
          lb[v] = d + 1;
          qp(v);
        }
      }
    }
 
    Fo(i, 1, states.size())
      ans[lb[i]]++, ans[states[i].len + 1]--;

    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        if (shouldPrintResult) print(ans[i]);
    }
    if (shouldPrintResult) cnl;
    return ans;
  }

private:
  void init(const string &S) {
    states.reserve(2 * S.size());
    last = state();
    for (char c : S)
      extend(c);

    preprocess();
  };

  void preprocess() {
    vpii v(states.size());
    for (int i = 0; i < states.size(); i++)
      v[i] = {states[i].len, i};
    sort(all(v), greater<pii>());
    for (auto [len, id] : v)
      if (states[id].link != -1)
      cnt[states[id].link] += cnt[id];
    cnt[0] = 1;
  }
 
  void extend(char _c) {
    int c = _c - 'a'; // change for different alphabet
    int cur = state(states[last].len + 1), P = last; 
    cnt[cur] = 1;
    while (P != -1 && states[P].next[c] == -1) {
      states[P].next[c] = cur;
      P = states[P].link;
    }
    if (P == -1)
      states[cur].link = 0;
    else {
      int Q = states[P].next[c];
      if (states[P].len + 1 == states[Q].len)
        states[cur].link = Q;
      else {
        int C = state(states[P].len + 1, states[Q].link);
        cnt[C] = 0;
        copy(states[Q].next, states[Q].next + 26, states[C].next);
        while (P != -1 && states[P].next[c] == Q) {
          states[P].next[c] = C;
          P = states[P].link;
        }
        states[Q].link = states[cur].link = C;
      }
    }
    last = cur;
  }

  ll dfs(int u = 0) {
    if (dp[u]) return dp[u];

    fo(i,26)
      if (states[u].next[i] != -1) 
        dp[u] += dfs(states[u].next[i]);
    return dp[u] += 1;
  }

  ll dfsCnt(int u = 0) {
    if (dp[u]) return dp[u];

    fo(i,26)
      if (states[u].next[i] != -1) 
        dp[u] += dfsCnt(states[u].next[i]);
    return dp[u] += cnt[u];
  }

  void dfsKthSmallestSubstr(ll& K, string& out, int u = 0) {
    if (!K) return;
    K--;
    //deb2(K,out);

    fo(i,26) {
      int v = states[u].next[i];
      //deb2(v, dp[v]);
      if (v > -1) {
        if (K >= dp[v]) K -= dp[v];
        else {
          out += (char)(i + 'a');
          return dfsKthSmallestSubstr(K, out, v);
        }
      }
    }
  }

  void dfsKthSmallestNondistinctSubstr(ll& K, string& out, int u = 0) {
    if (K < cnt[u]) return;
    K -= cnt[u];
    //deb2(K,out);

    fo(i,26) {
      int v = states[u].next[i];
      //deb2(v, dp[v]);
      if (v > -1) {
        if (K >= dp[v]) K -= dp[v];
        else {
          out += (char)(i + 'a');
          return dfsKthSmallestNondistinctSubstr(K, out, v);
        }
      }
    }
  }
};

// vl v(N);
// vl p(N, -1);
// vl szz(N);
// vl anc(N);
// bitset<N> vis;
// bitset<N> bs;

// ll timer = 0;
// vl tin, tout;

ll a, b, c, n, m, k, w;
string s, t;

void solution() {
  rd(s >> k);
  SuffixAuto sa(s);

  put(sa.kthLexicographicallySmallestNondistinctSubstr(k));
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
