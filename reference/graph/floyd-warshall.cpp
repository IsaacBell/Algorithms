void floydWarshall() {
  const ll MAX = 1e18;
  ll q; rd(n>>m>>q);
  ll mat[n+1][n+1];

  Fo(i,1,n+1) {
    Fo(j,1,n+1) {
      mat[i][j] = MAX;
    }
    mat[i][i] = 0;
  }
  fo(i,m){
    rd(a>>b>>c);
    ckmin(mat[a][b],c);
    ckmin(mat[b][a],c);
  }

  int k;
  Fo(k,1,n+1)
    Fo(i,1,n+1)
      Fo(j,1,n+1)
        ckmin(mat[i][j], mat[i][k]+mat[k][j]);

  fo(i,q) {
    rd(a >> b);
    put( (mat[a][b] >= MAX ? -1 : mat[a][b]) );
  }
}
