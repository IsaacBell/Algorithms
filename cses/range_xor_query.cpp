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
#include <set>
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

#define sz size
#define IMAX INT_MAX
#define IMIN INT_MIN
#define gc getchar_unlocked
#define ll long long
#define PI 3.1415926535897932384626
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define br printf("\n")
#define fo(i, n) for(i=0;i<n;i++)
#define Fo(i, k, n) for(i=k;k<n?i<n:i>n;k<n?i+=1:i-=1)
#define deb(x) cout << #x << " = " << x << endl;
#define deb2(x, y) cout << #x << " = " << x << ", " << #y << " = " << y << endl
#define deba(i, a, n) fo(i, n){cout << a[i] << " ";}
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, x) for(auto it = x.begin(); it != x.end(); it++)
#define trr(it, x) for(auto it = x.rbegin(); it != x.rend(); it+)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
  uniform_int_distribution<int> uid(0,lim-1);
  return uid(rang);
}

const int mod = 1'000'000'007;
const int N = 3e5;

vi v[N];
int a[N];
vi tree;

/* ========== YOUR CODE HERE ========= */
ll query(int node, int lo, int hi, int a, int b, int val) {
  if (a <= lo && hi <= b) {
    if (val != -1) {
      tree[node] ^= val;
    }
    return tree[node];
  }

  if (hi < a || b < lo) return 0;

  int mid = (lo + hi) / 2;

  return query(2 * node, lo, mid, a, b, val)
       ^ query(2* node + 1, mid + 1, hi, a, b, val);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  int n, q;
  cin >> n >> q;

  int A[n];
  for (int i = 0; i < n; i++) cin >> A[i];

  while (__builtin_popcount(n) != 1) n++;

  tree.resize(n);
  for (int i = 0; i < n; i++) tree[n + i] = A[i];
  for (int i = n - 1; i >= 1; i--) tree[i] = tree[2*i] ^ tree[2*i+1];

  for (int i = 0; i < q; i++) {
    int lo, hi;
    lo--;
    hi--;
    cin >> lo >> hi;
    cout << query(1, 0, n - 1, lo, hi, -1) << "\n";
  }

  return 0;
}
