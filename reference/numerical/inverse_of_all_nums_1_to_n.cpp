vl inv(n + 1);
inv[1] = 1;
Fo(i,2,n+1)
  inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
