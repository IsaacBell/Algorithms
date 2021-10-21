vl prime_factorization(ll num) {
  vl out;
  static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};

  /* Manually handle the most common divisors */
  for (ll x: {2, 3, 5}) {
    while (num % x == 0) {
      out.pb(x);
      num /= x;
    }
  }

  /* From here, prime factors follow a common pattern.
     We can take advantage of this by incrementing the current
     index by alternating amounts
     */
  ll i = 0;

  for (ll i = 7; i*i <= num; i += increments[i++]) {
    while (num % i == 0) {
      out.pb(i);
      num /= i;
    }
    if (i == 8) i = 0;
  }

  if (num > 1) out.pb(num);
  return out;
}