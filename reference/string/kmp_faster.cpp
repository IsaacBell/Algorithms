ll a, b, c, n, m, k, w;
string s, t;
vl nxt, bak;

void getNext(string& p){
  ll i = 0, j = -1;
  nxt[0] = -1;
  while (i < p.sz()) {
    if (j == -1 || p[i] == p[j]) {
      ++i;
      ++j;
      nxt[i] = j;
    }
    else j = nxt[j];
  }
}

void kmpPreProc(string& text) {
  ll lt = text.sz();
  ll i = 0, j = 0;
  getNext(text);
}

ll KMP(string& text, string& pattern) {
  ll lt = text.sz(), lp = pattern.sz();
  ll i = 0, j = 0;

  while (i < lt && j < lp) {
    if (j == -1 || text[i] == pattern[j]) {
      i++;
      j++;
    }
    else j = nxt[j];
  }
  if (j == lp) return i - j;
  return -1;
}


void solution() {
  rd(t >> n);

  // Use a reset table to pre-process pattern string
  bak.rsz(t.sz());
  nxt.rsz(t.sz());
  kmpPreProc(t);

  while (n--) {
    rd(s);
    if (KMP(t,s) == -1) put("NO");
    else put("YES");
  }
}