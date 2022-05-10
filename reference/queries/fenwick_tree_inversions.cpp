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

  /*
    For each k=0,1,2,…,N−1, find the inversion number of the sequence 
    B=[b0,b1,b2,…,b N−1] defined as b[i] ​= a[i+k%N].

    The inversion number of a sequence A=[a0,a1,a2,…,a N−1​] is the number of
    pairs of indices (i,j) such that i<j and ai>aj.
  */
  fo(k, n-1) {
    res -= A[k] - 1;
    res += n-1 - (A[k] - 1);
    put(res);
  }
}