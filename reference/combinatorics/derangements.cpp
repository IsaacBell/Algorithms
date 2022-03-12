void solution() {
  rd(n);
  vl d(n+1);
  d[2] = 1;
  Fo(i,3,n+1) d[i] = 
    multM<ll>(
      addM<ll>(d[i-1], d[i-2]),
      i - 1
    );
  put(d[n]);
}