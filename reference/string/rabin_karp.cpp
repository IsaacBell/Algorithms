// s = pattern, t = text
// Ex: s = "abc", t = "abcdefg"
vl rabin_karp(string const& s, string const& t) {
  const int p = 31; 
  const int m = 1e9 + 9;
  int S = s.size(), T = t.size();

  vl p_pow(max(S, T)); 
  p_pow[0] = 1; 
  for (int i = 1; i < (int)p_pow.size(); i++) 
    p_pow[i] = (p_pow[i-1] * p) % m;

  vl h(T + 1, 0); 
  for (int i = 0; i < T; i++)
    h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 

  ll h_s = 0; 
  for (int i = 0; i < S; i++) 
    h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

  vl occurences;
  for (int i = 0; i + S - 1 < T; i++) { 
    ll cur_h = (h[i+S] + m - h[i]) % m; 
    if (cur_h == h_s * p_pow[i] % m)
      occurences.pb(i);
  }

  return occurences;
}
