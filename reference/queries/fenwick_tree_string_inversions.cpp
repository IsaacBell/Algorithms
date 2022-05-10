/*
  Calcs the min # swaps of neighboring elements of the string,
  needed to reverse the string.

  Solve by finding # of inversions for each prefix of the array.

  See: https://codeforces.com/contest/1430/problem/E
*/

const ll MAXSZ = 31; // max charset size

string revS;

vl fen(N);
vl cnt(MAXSZ);
vvl posS(MAXSZ, vl {});
vvl posT(MAXSZ, vl {});

void inc(int i, int v) {
  for (; i < n; i = (i | (i+1)))
    fen[i] += v;
}

int sum(int r) {
  int res = 0;
  for (; r >= 0; r = (r & (r+1)) - 1)
    res += fen[r];
  return res;
}

int query(int l, int r) {
  return sum(r) - sum(l-1);
}

void Fenwick() {
  rd(n >> s);
  revS = s;
  reverse(all(revS));

  fo(i, n) {
    posS[s[i] - 'a'].pb(i);
    posT[revS[i] - 'a'].pb(i);
  }

  ll ans = 0;
  fo(i,n) {
    // Find pos of revS[i] in original string's lookup table
    ll khar = revS[i] - 'a';
    ll cur = posS[khar][cnt[khar]];
    ll oldChar = cur;

    // Sum count of cur in the BIT
    cur += query(cur, n-1);
    ans += cur - i;

    // Increase count in lookup table
    inc(oldChar, 1);
    cnt[khar]++;
  }

  put(ans);
}

void solution() {
  Fenwick();
}