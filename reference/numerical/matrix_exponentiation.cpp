struct Matrix {
  vvl data(MAX_N, vl(MAX_N));

  Matrix(ll nn, ll mm) {
    data.rsz(nn, vl(mm));
  }
};

Matrix matMul(Matrix a, Matrix b) { // O(n^3)
  Matrix ans; ll i, j, k;

  fo(i,MAX_N)
    fo(j,MAX_N)
      for (ans.mat[i][j] = k = 0; k < MAX_N; k++) // if necessary,
        ans.mat[i][j] += a.mat[i][k] * b.mat[k][j]; // do modulo arithmetic here
  return ans;
}

Matrix matPow(Matrix base, ll p) { // O(n^3 log p)
  Matrix ans; ll i, j;

  fo(i, MAX_N) fo(j, MAX_N) ans.mat[i][j] = (i == j); // identity matrix

  while (p) { // iterative version of Divide & Conquer exponentiation
    if (p & 1) ans = matMul(ans, base);
    base = matMul(base, base); // square the base
    p >>= 1;
  }

  return ans;
}