// Factorials up to 10^18
vl fact {
  0,
  1,
  2,
  6,
  24,
  120,
  720,
  5040,
  40320,
  362880,
  3628800,
  39916800,
  479001600,
  6227020800,
  87178291200,
  1307674368000,
  20922789888000,
  355687428096000,
  6402373705728000,
  121645100408832000
};

ll powmod(ll a, ll b, ll p){
  a %= p;
  if (a == 0) return 0;
  ll product = 1;
  while(b > 0) {
    if (b&1) {    // you can also use b % 2 == 1
      product *= a;
      product %= p;
      --b;
    }

    a *= a;
    a %= p;
    b /= 2;    // you can also use b >> 1
  }

  return product;
}

ll inv(ll a, ll p){
  return powmod(a, p-2, p);
}

ll nCk(ll n, ll k, ll p){
  return ((fact[n] * inv(fact[k], p) % p) * inv(fact[n-k], p)) % p;
}
