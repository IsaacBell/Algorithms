// Prefer this version
template<typename T>
vector<int> z_function(const T &s) {
  int n = s.size();
  vector<int> z(n, 0);
  int r = 0;
  int l = 0;
  for (int i = 1; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

/*
  Quick Z-Algorithm

  Returns a vector that corresponds to the Z-array
*/
vl z_function(string s) {
  szn(n,s);
  vl z(n);
  for (ll i = 1, l = 0, r = 0; i < n; ++i) {
  if (i <= r)
    z[i] = min(r - i + 1, z[i - l]);
  while (i + z[i] < n && s[z[i]] == s[i + z[i]])
    ++z[i];
  if (i + z[i] - 1 > r)
    l = i, r = i + z[i] - 1;
  }
  return z;
}
