ll binpow(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
      if (b & 1)
          res = res * a;
      a = a * a;
      b >>= 1;
  }
  return res;
}
ll binpowmod(ll a, ll b) {
  if(b == 0){
        return 1;
    }
    ll ans = binpowmod(a,b/2);
    ans *= ans;
    ans %= mod;
    if(b % 2){
        ans *= a;
    }
    return ans % mod;
}