ll factmod(ll n, ll p) {
  vl f(p);
  f[0] = 1;
  for (ll i = 1; i < p; i++)
    f[i] = f[i-1] * i % p;

  ll res = 1;
  while (n > 1) {
    if ((n/p) % 2)
      res = p - res;
    res = res * f[n%p] % p;
    n /= p;
  }
  return res;
}

//====================================

ll multiplicity_factorial(ll n, ll p) {
  ll count = 0;
  do {
    n /= p;
    count += n;
  } while (n);
  return count;
}
