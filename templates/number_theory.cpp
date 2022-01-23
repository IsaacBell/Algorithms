/* Custom template functions */

bool __primes_generated__ = 0;
bitset<(const int) 15000105> prime;
vl primeList;

bool isPrime(ll num) {
  if (num < 4) return true;
  if (!(num & 1)) return false;

  for (ll i = 3; i <= sqrt(num); i += 2) {
    if (i % num == 0) return false;
    return true;
  }
}

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

void sieve(ll nn) {
  prime.set();
  prime[0] = prime[1] = false;
  for (ll i = 2; i <= n; i += 2) prime[i] = false;

  Fo(i,2,n) {
    if (prime[i]) {
      primeList.pb(i);
      for (ll j = i+i; j*j <= n; j += i)
        prime[j] = false;
    }
  }
}

void genprimes(int n) {
  __primes_generated__ = 1;
  sieve(n + 1);
  for (ll i = 2; i <= n; i++)
    if (prime[i])
      primeList.push_back(i);
}
 
vector<ll> factors(ll n) {
  if (!__primes_generated__) {
  cerr << "Call genprimes you dope" << endl;
  exit(1);
  }
  vector<ll> facs;
  
  for (ll i = 0; primeList[i] * primeList[i] <= n && i < primeList.size(); i++) {
    if (n % primeList[i] == 0) {
      while (n % primeList[i] == 0) {
        n /= primeList[i];
        facs.push_back(primeList[i]);
      }
    }
  }
  if (n > 1) facs.push_back(n);
  sort(facs.begin(), facs.end());
  return facs;
}

vector<ll> getdivs(ll n) {
  vector<ll> divs;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      divs.push_back(i);
      divs.push_back(n / i);
    }
  }

  getunique(divs);
  return divs;
}

/*
  # of integers relatively prime to x in a given range [1...r]
  O(√‾n)
*/
ll relativePrimes(ll n, ll r) {
  vl pp;
  Fo(i,2,sqrt(n)+1)
    if (n%i == 0) {
      pp.pb(i);
      while (n%i == 0)
        n /= i;
    }
  if (n > 1) pp.pb(n);

  ll sum = 0;
  Fo(msk,1, (1 << pp.sz()) ) {
    ll mul = 1, bits = 0;
    fo(i, pp.sz())
      if (msk & (1 << i)) {
        bits++;
        mul *= pp[i];
      }

    ll cur = r / mul;
    if (bits % 2 == 1)
      sum += cur;
    else
      sum -= cur;
  }

  return r - sum; 
}
