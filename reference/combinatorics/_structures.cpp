// Factorial pre-processing
vl fact;
fact.rsz(2000001);
fact[0] = fact[1] = 1;
Fo(i,2,2000001) {
  fact[i] = (fact[i-1] * i) % mod;
}

// Modular inverse
ll inv(ll a, ll p = mod){
  return binpowmod(a, p-2, p);
}

// Derangements
void solution() {
  rd(n);
  vl d(n+1);
  d[2] = 1;
  Fo(i,3,n+1) d[i] = 
    multM<ll>(
      addM<ll>(d[i-1], d[i-2]),
      i - 1
    );
  put(d[n]);
}

// Combinations
ll nCk(ll n, ll k, ll p){
  return ((fact[n] * inv(fact[k], p) % p) * inv(fact[n-k], p)) % p;
}
