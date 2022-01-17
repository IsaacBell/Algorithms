ll a, b, c, n, m, q, w;
string s;

vvl Ch; // children of node
vl dp;
vl f(N), // # subtrees at i
   g(N); // # subtrees w/o i
vl d(N);

/* Solution starts here */
constexpr const ll MAXN = 2e5;
constexpr const ll LOG = log2(MAXN);
vvl up(LOG+1, vl(MAXN));

void solution() {
  ll q; rd(n >> q);
  Ch.rsz(n+1, vl {});
  // f.rsz(n+1), g.rsz(n+1), dp.rsz(n+1);

  Fo(i,2,n+1) {
    ll ch; rd(ch);
    Ch[i].pb(ch);
    up[0][i] = ch;
  }

  fo(i,LOG) fo(j,n) up[i+1][j+1] = up[i][up[i][j+1]];

  const auto jmp = [](ll x, ll k) {
    fo(i,LOG+1) if ((k >> i) & 1) x = up[i][x];
    return x ?: -1; // -1 if not found
  };

  while (q--) {
    rd(a >> b);
    put( jmp(a,b) );
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  solution();

  return 0;
}
