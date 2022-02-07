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