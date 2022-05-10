const int N = 3e5+10;

int n;
int fen[N];

void update(int i, int v){
  for(int j = i; j <= n; j += (j&(-j)))
    fen[j] += v;
}

int sum(int i){
  int res = 0;
  for(int j = i; j > 0; j -= (j&(-j)))
    res += fen[j];
  return res;
}

int query(int l, int r){
  return sum(r) - sum(l-1);
}

void Fenwick() {
  rd(n >> s);
  fo(i,n) {
    rd(A[i]);
    A[i]++;
  }

  ll res = 0;
  fo(i,n) {
    res += query(A[i], n);
    update(A[i], 1);
  }

  put(res);
}