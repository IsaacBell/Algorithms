ll compute_hash(string const& s) {
  const ll p = 31;
  const ll m = 1e9 + 9;
  ll hash_value = 0;
  ll p_pow = 1;
  trav(ch : s) {
    hash_value = (hash_value + (ch - 'a' + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash_value;
}

/* 
  Search for duplicate strings in an array of strings
  Returns a vector of matching indexes
*/
vvl group_identical_strings(vstr const& strs) {
  szn(nn,strs);
  vpl hashes(nn);
  fo(i,nn) hashes[i] = {compute_hash(strs[i]), i};

  sortall(hashes);

  vvl groups;
  fo(i,nn) {
    if (!i || hashes[i].F != hashes[i-1].F)
      groups.emplace_back();
    groups.back().pb(hashes[i].S);
  }
  return groups;
}

//==========================

/*
Determine the number of different substrings in a string

Problem: Given a string  of length, consisting only of lowercase English 
letters, find the number of different substrings in this string.
*/

ll count_unique_substrings(string const& s) {
  szn(nn,s);

  const ll p = 31;
  const ll mm = 1e9 + 9;
  vl p_pow(nn);
  p_pow[0] = 1;
  fo(i,nn) p_pow[i] = (p_pow[i-1] * p) % mm;

  vl h(nn + 1, 0);
  fo(i,nn) h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % mm;

  ll cnt = 0;
  Fo(l, 1, nn+1) {
    set<ll> hs;
    fo(i,nn - l + 1) {
      ll cur_h = (h[i + l] + mm - h[i]) % mm;
      (cur_h *= p_pow[nn-i-1]) %= mm;
      hs.insert(cur_h);
    }
    cnt += hs.size();
  }
  return cnt;
}
