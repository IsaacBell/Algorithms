vl cat;

void catalan(ll nn) {
  cat.clear(); cat.rsz(nn+1);
  cat[0] = cat[1] = 1;
  Fo(i,2,nn+1) {
    cat[i] = 0;
    fo(j,i) {
      cat[i] += (cat[j] * cat[i-j-1]) % mod;
      if (cat[i] >= mod) cat[i] -= mod;
    }
  }
}
