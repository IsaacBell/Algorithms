// Created by proofbycontradiction on 2019-01-24 13:42.
#include <bits/stdc++.h>
using namespace std;

class gauss {
  vi basis;

public:
  void add(int x) {
    for (int b: basis)  ckmin(x, x ^ b);
    for (int &b: basis) ckmin(b, x ^ b);
    if (x > 0) basis.pb(x);
  }

  bool can(int x) const {
    for (int b: basis) ckmin(x, x ^ b);
    return (x == 0);
  }

  int rank() const {
    return basis.size();
  }

  int maximum() const {
    int ans = 0;
    for (int b: basis) ans ^= b;
    return ans;
  }
};

int32_t main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int q; rd(n >> q);
  vi po2 = {1};
  fo(i,n) po2.pb((po2.back() * 2) % mod);
  vector<gauss> g(n);

  fo(i,n) {
    int x; rd(x);
    if (i > 0) g[i] = g[i-1];
    g[i].add(x);
  }

  fo(i,q) {
    int l, x; rd(l >> x);
    l--;
    if (g[l].can(x)) {
      int ans = l + 1 - g[l].rank();
      put(po2[ans]);
      continue;
    }
    put(0);
  }
}
