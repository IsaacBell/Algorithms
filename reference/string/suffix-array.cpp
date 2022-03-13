/*
  Example: Longest Repeating Substring (or "-1" if not found)
  void solution() {
    rd(s);
    SuffixArray<string> sa(s);
    put(sa.longestRepeatingSubstring("-1"));
  }
*/
template <typename T = string>
struct SuffixArray {
  const int n;
  const T s;
  vi sa, lcp;

  SuffixArray<T>(T &s_): n(s_.sz()), s(s_) {
  	build_suffix_array();
    build_lcp();
  };

  T longestRepeatingSubstring(T fallback = "") {
    vi pos_in_sa(n);
    fo(i,n) pos_in_sa[sa[i]] = i;

    auto o = *max_element(all(lcp));
    if (!o) { ret fallback; }
    
    ll i = 0; while (lcp[i] != o) i++;
    return s.substr(sa[i], lcp[i]);
  }

private:
  void build_suffix_array(int char_bound = 256) {
    vi a(n);
    if (!n) return;
    if (char_bound != -1) {
      vi aux(char_bound, 0);
      for (int i = 0; i < n; i++) {
        aux[s[i]]++;
      }
      int sum = 0;
      for (int i = 0; i < char_bound; i++) {
        int add = aux[i];
        aux[i] = sum;
        sum += add;
      }
      for (int i = 0; i < n; i++) {
        a[aux[s[i]]++] = i;
      }
    } else {
      iota(all(a), 0);
      sort(all(a), [&](int i, int j) { return s[i] < s[j]; });
    }
    
    vi sorted_by_second(n);
    vi ptr_group(n);
    vi new_group(n);
    vi group(n);
    group[a[0]] = 0;
    for (int i = 1; i < n; i++) {
      group[a[i]] = group[a[i - 1]] + (!(s[a[i]] == s[a[i - 1]]));
    }
    int cnt = group[a[n - 1]] + 1;
    int step = 1;
    while (cnt < n) {
      int at = 0;
      for (int i = n - step; i < n; i++) {
        sorted_by_second[at++] = i;
      }
      for (int i = 0; i < n; i++) {
        if (a[i] - step >= 0) {
          sorted_by_second[at++] = a[i] - step;
        }
      }
      for (int i = n - 1; i >= 0; i--) {
        ptr_group[group[a[i]]] = i;
      }
      for (int i = 0; i < n; i++) {
        int x = sorted_by_second[i];
        a[ptr_group[group[x]]++] = x;
      }
      new_group[a[0]] = 0;
      for (int i = 1; i < n; i++) {
        if (group[a[i]] != group[a[i - 1]]) {
          new_group[a[i]] = new_group[a[i - 1]] + 1;
        } else {
          int pre = (a[i - 1] + step >= n ? -1 : group[a[i - 1] + step]);
          int cur = (a[i] + step >= n ? -1 : group[a[i] + step]);
          new_group[a[i]] = new_group[a[i - 1]] + (pre != cur);
        }
      }
      swap(group, new_group);
      cnt = group[a[n - 1]] + 1;
      step <<= 1;
    }
    sa = std::move(a);
  }
  
  void build_lcp() {
    assert((int) sa.sz() == n);
    vi pos(n);
    fo(i,n) pos[sa[i]] = i;
    vi lcp_( max(n - 1, 0) );
    int k = 0;
    for (int i = 0; i < n; i++) {
      k = max(k - 1, 0);
      if (pos[i] == n - 1) k = 0;
      else {
        int j = sa[pos[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
          k++;
        }
        lcp_[pos[i]] = k;
      }
    }
    lcp = std::move(lcp_);
  }
};
