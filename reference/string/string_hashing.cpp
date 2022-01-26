ll compute_hash(string const& s) {
  const int p = 31;
  const int m = 1e9 + 9;
  ll hash_value = 0;
  ll p_pow = 1;
  for (char c : s) {
  hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
  p_pow = (p_pow * p) % m;
  }
  return hash_value;
}

//====================

// Search for duplicate strings in an array of strings
vector<vector<int>> group_identical_strings(vector<string> const& s) {
  int n = s.size();
  vector<pair<ll, int>> hashes(n);
  for (int i = 0; i < n; i++)
  hashes[i] = {compute_hash(s[i]), i};

  sort(hashes.begin(), hashes.end());

  vector<vector<int>> groups;
  for (int i = 0; i < n; i++) {
  if (i == 0 || hashes[i].first != hashes[i-1].first)
    groups.emplace_back();
  groups.back().push_back(hashes[i].second);
  }
  return groups;
}

//==========================

// Determine the number of different substrings in a string
/*
Problem: Given a string  of length , consisting only of lowercase English 
letters, find the number of different substrings in this string.
*/

int count_unique_substrings(string const& s) {
  int n = s.size();

  const int p = 31;
  const int m = 1e9 + 9;
  vl p_pow(n);
  p_pow[0] = 1;
  for (int i = 1; i < n; i++)
    p_pow[i] = (p_pow[i-1] * p) % m;

  vl h(n + 1, 0);
  for (int i = 0; i < n; i++)
    h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

  int cnt = 0;
  for (int l = 1; l <= n; l++) {
    set<ll> hs;
    for (int i = 0; i <= n - l; i++) {
      ll cur_h = (h[i + l] + m - h[i]) % m;
      cur_h = (cur_h * p_pow[n-i-1]) % m;
      hs.insert(cur_h);
    }
    cnt += hs.size();
  }
  return cnt;
}
