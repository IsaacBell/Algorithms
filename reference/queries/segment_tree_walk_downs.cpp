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
#define sz size
#define rsz resize
#define IMAX INT_MAX
#define IMIN INT_MIN
#define gc getchar_unlocked
#define ll int64_t
#define PI 3.1415926535897932384626
#define INF 2000000000
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
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, x) for(auto it = x.begin(); it != x.end(); it++)
#define trr(it, x) for(auto it = x.rbegin(); it != x.rend(); it+)

typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef tuple<ll,ll,ll> tll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vl vll;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<ld> vd;
typedef vector<cd> vcd;
typedef vector<uint32_t> vu32;
typedef vector<uint64_t> vu64;

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
  uniform_int_distribution<int> uid(0,lim-1);
  return uid(rang);
}

const ll mod = 1e9 + 7;
const ll N = 3e5;

template<class T=ll> using pq = priority_queue<T>;
template<class T=ll> using mpq = priority_queue<T, vector<T>, greater<T>>;

// Modulo operators
template<typename T> T M(T x) { return ((x % mod + mod) % mod);  }
template<typename T> T addM(T a, T b)  { return M(M(a) + M(b)); }
template<typename T> T subM(T a, T b)  { a -= b; return a < 0 ? a + mod : a; }
template<typename T> T multM(T a, T b) { return M(M(a) * M(b)); }
template <typename T=ll> T powM(T x, T y) {
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
T sum_digit_string(T str)
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

vl v(N);
vl par(N, -1);
vl szz(N);
vl anc(N);
bitset<N> vis;
bitset<N> bs;

ll timer = 0;
// vl tin, tout;

ll a, b, n, m, q, k, w;
string s;

/* Solution starts here */
vector<Node> tree;

struct Node {
  ll g, l, r, sum;
  Node operator+(Node& rhs) {
    return {
      max(max(g, rhs.g), r + rhs.l),
      max(l, sum + rhs.l),
      max(rhs.r, rhs.sum + r),
      sum + rhs.sum
    };
  }
};

void build(vl& A, ll l = 1, ll r = n, ll i = 1) {
	if (l == r) {
    tree[i] = {
      max(0ll, A[l]),
      max(0ll, A[l]),
      max(0ll, A[l]),
      A[l]
    };
  } else {
		ll mid = (l + r) / 2;
		build(A, l, mid, 2 * i);
		build(A, mid + 1, r, 2*i + 1);
		tree[i] = tree[i * 2] + tree[2*i + 1];
	}
}

void update(ll pos, ll val, ll l = 1, ll r = n, ll i = 1) {
	if (l == r) tree[i] = {max(0ll, val), max(0ll, val), max(0ll, val), val};
	else {
		ll mid = (l + r) / 2;
		if (pos > mid) update(pos, val, mid + 1, r, 2*i + 1);
		else update(pos, val, l, mid, i * 2);
		tree[i] = tree[i * 2] + tree[2*i + 1];
	}
}

// "lo, hi": Current range in view
// "a, b": Range of the inputted search query
ll query(ll i, ll lo, ll hi, ll a, ll b) {
  // If element is in our target search range, returns its value
  if (a <= lo && b >= hi) return tree[i];
  // If search range & our current range are disjoint (have no overlap), exit
  if (hi < a || b < lo) return 0;

  ll mid = (hi + lo) / 2;
  return query(2*i, lo, mid, a, b)
       + query(2*i+1, mid+1, hi, a, b);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  ll q; cin >> n >> q;
  vl A(n);
  fo (i, n) cin >> A[i];


  while (q--) {
    short int type;
    ll a, b;
    cin >> type >> a >> b;

    if (type == 1) // Update
      update(a, b);
    else // Sum Query
      // cout << query(1, 0, n-1, a-1, b-1) << nl;
      cout << tree[1].g << nl;
  }

  return 0;
}
