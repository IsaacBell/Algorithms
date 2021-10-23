vl factorials;

void gen_factorials(ll MAXN) {
  factorials.rsz(MAXN);
  factorials[0] = 1;
  Fo(i,1,MAXN+1)
    factorials[i] = factorials[i - 1] * i % m;
}

ll binomial_coefficient(ll n, ll k) {
  vvl C(n+1, vl(k+1));
  fo(i,n+1)
    fo(j, min(i,k))
      if (!j || j == i)
        C[i][j] = 1;
      else
        C[i][j] = C[i-1][j-1] + C[i-1][j];
  return C[n][k];
}

ll nCr(ll n, ll r)
{
  // base case
  if (r > n)
      return 0;

  // C(n,r) = C(n,n-r)
  if (r > n - r)
      r = n - r;

  ll mod = 1000000007;

  // array of elements from n-r+1 to n
  ll arr[r];

  for (ll i = n - r + 1; i <= n; i++) {
      arr[i + r - n - 1] = i;
  }

  long ll ans = 1;
  // for numbers from 1 to r find arr[j],
  // such that gcd(i,arr[j])>1
  for (ll k = 1; k < r + 1; k++) {
    ll j = 0, i = k;
    while (j < r) {
      ll x = gcd(i, arr[j]);
      if (x > 1) {
        // if gcd>1, divide both by gcd
        arr[j] /= x;
        i /= x;
      }

      // if i becomes 1, no need to search arr
      if (i == 1)
        break;
      j += 1;
    }
  }

  // single pass to multiply the numerator
  for (ll i : arr)
    ans = (ans * i) % mod;
  return (ll) ans;
}