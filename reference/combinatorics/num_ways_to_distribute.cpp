/*
  There are n children and m apples that will be distributed to them. 
  
  Your task is to count the number of ways this can be done, modulo 10^9+7.

  For example, if n=3 and m=2, there are 6 ways:
  [0,0,2], [0,1,1], [0,2,0], [1,0,1], [1,1,0] and [2,0,0]

  Formula:
  f(n,m) = fact[n+m-1] * inv(fact[n-1])) * inv(fact[m]))
*/

vl fact;

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

ll inv(ll a, ll p = mod){
  return powmod(a, p-2, p);
}

void solution() {
  rd(n >> m);

  ll o = (fact[n+m-1] * inv(fact[n-1])) % mod;
  (o *= inv(fact[m])) %= mod;
  put(o);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  ll t = 1;
  // rd(t);
  fact.rsz(2000001);
  fact[0] = fact[1] = 1;
  Fo(i,2,2000001) {
    fact[i] = (fact[i-1] * i) % mod;
  }

  while(t--)
    solution();

  return 0;
}
