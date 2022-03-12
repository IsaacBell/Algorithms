vl fact(2000001);
fact.rsz(2000001);
fact[0] = fact[1] = 1;
Fo(i,2,2000001) {
  fact[i] = (fact[i-1] * i) % mod;
}