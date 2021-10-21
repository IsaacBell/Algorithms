#include<bits/stdc++.h>

using namespace std;

#define ll int64_t

// General functions
template<class T=ll> T gcd(T a, T b) { return b ? gcd(b, a%b) : a; }
template<class T=ll> T lcm(T a, T b) { return a*(b/gcd(a,b)); }

// Runs in O(4√n) time. Here 4√n is the fourth root of n
ll rho(ll n, ll x0, ll z) {
  ll x = x0, y = x0;
  ll g = 1;

  while (g == 1) {
    x = ((x*x % n) + z) % n;
    y = ((y*y % n) + z) % n;
    y = ((y*y % n) + z) % n;
    g = gcd(abs(x-y), n);
  }

  return g;
}

void solution() {
  ll n; 
  cin >> n;
  cout << rho(n, 1, 1);
}
