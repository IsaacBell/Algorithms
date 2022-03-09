vl fact(1e6);
fact[0] = fact[1] = 1;
Fo(i,2, 1e6) fact[i] = (fact[i-1] * i) % mod;