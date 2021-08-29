// #include<bits/stdc++.h>
#include <iostream>
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
#define ll long long
#define PI 3.1415926535897932384626
#define INF 2000000000
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define br printf("\n")
#define traverse(a, x) for (auto &a : x)
#define fo(i, n) for(int i=0;i<n;i++)
#define ford(i, n) for(int i = n - 1; i >= 0; i--)
#define ford1(i, n) for(int i = n - 1; i; i--)
#define Fo(i, k, n) for(int i = k; k < n ? i < n : i > n; k < n ? i += 1: i -= 1)
#define deb(x) cout << #x << " = " << x << endl;
#define deb2(x, y) cout << #x << " = " << x << ", " << #y << " = " << y << endl
#define deba(i, a, n) fo(i, n){cout << a[i] << " ";}
#define pb push_back
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

template<class T> using pq = priority_queue<T>;
template<class T> using mpq = priority_queue<T, vector<T>, greater<T>>;

const int mod = 1'000'000'007;
const int N = 3e5;

vi v[N];
int a[N];
bitset<10007> bs;

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }
bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

void dfs(int i, vi A, int n, int k) {
  if (!k) return;
  A.erase(A.begin() + i);
  int x = n;
  fo(i, min(k - 1, (int) A.sz())) {
    x -= A[i] * pow(10, i);
    if (bs[x]) cout << A.sz() << nl << x << nl;
    dfs(i, A, n, k - 1);
    x += A[i] * pow(10, i);
  }
}

void solution() {
  int n, k; cin >> n >> k;
  int x = n;
  vi A;
  while (x) {
    int rem = x % 10;
    x /= 10;
    A.pb(rem);
  }
  int y = 0;
  if (bs[n]) {
    cout << A.sz() << nl << n << nl;
  }
  fo(i, A.sz()) {
    dfs(i, A, n, k - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  int t; cin >> t;

  fo(i,10007) {
    bs[i] = true;
    if (i > 1) {
      while (i*i < 10007) {
        i *= i;
        bs[i] = true;
      }

    }
  }

  while(t--)
    solution();

  return 0;
}
