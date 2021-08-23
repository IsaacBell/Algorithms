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

/* ===================================================*/

// Set constraints & parameters

const int mod = 1'000'000'007;
const int N = 1e6;

vi A;
vvi M;
vi logs;

// query formula
int solution(int L, int R) {
  int len = R - L + 1;
  int k = logs[len];
  // while ((1 << (k+1)) <= len)
  //   k++;
  return min(M[L][k], M[R - (1<<k) + 1][k]);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());

  // read input
  logs.resize(N);   // logarithms
  A.resize(N);   // array
  M.resize(N, vi( floor(log2(N)) ));  //sparse table ("M" for matrix)

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    M[i][0] = A[i];
  }

  // log
  logs[1] = 0;
  for (int i = 2; i <= n; i++)
    logs[i] = logs[i/2]+1;

  // pre-processing
  for (int j = 1; j < floor(log2(N)); j++)
    for (int i = 0; i + (1 << j) - 1 < n; i++)
      M[i][j] = min(M[i][j-1], M[i + (1 << (j-1))][j-1]);

  // answer queries
  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    int L, R;
    cin >> L >> R;
    cout << solution(L, R) << "\n";
  }

  return 0;
}
