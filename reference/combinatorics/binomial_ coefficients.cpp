void solution() {
  rd(a >> b);
  ll o = fact[a];
  (o *= inv(fact[b])) %= mod;
  (o *= inv(fact[a-b])) %= mod;
  
  put(o);
}
