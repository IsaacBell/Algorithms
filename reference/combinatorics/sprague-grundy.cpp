// Globals
const ll LIMIT = 2000;
vl dp;

ll mex(vl& V) {
  set<ll> st; //(all(V));
  fo(i, V.sz()) st.insert(V[i]);

  fo(i, 1000001)
    if(!st.count(i))
      return i;

  // ret -1;
}

void preprocessGrundyValues() {
  dp.rsz(LIMIT);

  Fo(i,3,LIMIT) {
    vl state;
    for(int j=1;2*j<i;j++)
      state.pb(dp[j] ^ dp[i-j]);
    dp[i] = mex(state);
  }
}

void solution() {
  rd(n);
  if (n >= LIMIT) { put("first"); ret; }
  if (!n) { put("second"); ret; }

  if (dp[n] != 0) put("first");
  else put("second");
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());

  preprocessGrundyValues();
  ll t = 1;
  rd(t);

  while(t--)
    solution();

  return 0;
}
