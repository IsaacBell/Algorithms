/*
    Problem Description: https://codeforces.com/gym/102191/problem/E

    Here we use caterpillar method on grid points to calc
    # of uniq pts we've traversed

    Note that this is a variant of sliding window
*/

ll a, b, c, n, m, k, w;
string s, t;

pl dir(char ch) {
  pl p;
  if (ch == 'L') p = {-1,0};
  if (ch == 'R') p = {1,0};
  if (ch == 'U') p = {0,1};
  if (ch == 'D') p = {0,-1};
  return p;
}

void solution() {
  cin >> n >> s;
  ll o = 0, x = 0, y = 0;

  vpl pfs{ {x,y} };
  fo(i,n) {
    auto move = dir(s[i]);
    x += move.F, y += move.S;
    pfs.emplace_back(x,y);
  }
  assert(n == pfs.sz());

  auto start = 0;
  set<pl> st;

  fo(end, n) {
    while (st.count(pfs[end])) st.erase(pfs[start]), start++;
    st.insert(pfs[end]);
    ckmax(o, end - start);
  }

  put(o);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  solution();

  return 0;
}
