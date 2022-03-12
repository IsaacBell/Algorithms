/* 
  Standard Read

  Ex:
  5 4 3
  4 6 7
  9 3 0
*/
void solution() {
  rd(n >> m);
  ll M[n][m];
  fo(i,n) fo(j,m) rd(M[i][j]);
}

/* 
  Read 1-0 Grid as ints

  Ex:
  110
  101
  001
*/
void solution() {
  rd(n >> m);
  int M[n][m];
  char ch;
  fo(i,n) fo(j,m) { rd(ch); M[i][j] = ch == '1'; }
}
