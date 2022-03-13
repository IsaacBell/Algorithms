/*
  Suffix Automaton
  Author: Isaac Bell

  Example Usage:

    void solution() {
      rd(s >> k);
      SuffixAuto sa(s);
      put(sa.numDistinctSubstrings());
      put(sa.kthLexicographicallySmallestSubstr(k));
      put(sa.kthLexicographicallySmallestNondistinctSubstr(k));

      sa.substringDistribution(1); // print to console, e.g.: cout << "1 1 2 2 3 4 5\n";
      vl example = sa.substringDistribution(); // store to var

    }
*/
struct SuffixAuto {
  struct State {
    int len, link;
    int next[26];
    State(int _len = 0, int _link = -1) : len(_len), link(_link) {
      memset(next, -1, sizeof(next));
    }
  };
 
  vector<State> states;
  vl dp;  // dp[u]: # non-distinct substrings starting at node u
  vl cnt; // # times a state appears in the string
  int last, K;
  const string str;
  const int n;
 
  SuffixAuto(const string &S_): str(S_), n(S_.sz()) {
    dp.rsz(N), cnt.rsz(N);
    init(S_);
  }
 
  inline int state(int len = 0, int link = -1) {
    states.emplace_back(len, link);
    return states.size() - 1;
  }

  ll numDistinctSubstrings() {
    return dfs(0) - 1;
  }

  string kthLexicographicallySmallestSubstr(ll K) {
    string str_ = "";
    //dp.clear();
    dfs();
    dfsKthSmallestSubstr(K, str_);
    return str_;
  }

  string kthLexicographicallySmallestNondistinctSubstr(ll K) {
    string str_ = "";
    //dp.clear();
    dfsCnt();
    dfsKthSmallestNondistinctSubstr(K, str_);
    return str_;
  }

  // For every i 1…n, get # distinct substrings of length i
  vl substringDistribution(bool shouldPrintResult = 0) {
    qll q;
    vl lb(3e6, -1), ans(n+1);
 
    qp(0);
    lb[0] = 0;
    wqe {
      auto u = q.front(); q.pop();
      auto d = lb[u];
      fo(i, 26) {
        auto v = states[u].next[i];
        if (v != -1 && lb[v] == -1) {
          lb[v] = d + 1;
          qp(v);
        }
      }
    }
 
    Fo(i, 1, states.size())
      ans[lb[i]]++, ans[states[i].len + 1]--;

    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        if (shouldPrintResult) print(ans[i]);
    }
    if (shouldPrintResult) cnl;
    return ans;
  }

private:
  void init(const string &S) {
    states.reserve(2 * S.size());
    last = state();
    for (char c : S)
      extend(c);

    preprocess();
  };

  void preprocess() {
    vpii v(states.size());
    for (int i = 0; i < states.size(); i++)
      v[i] = {states[i].len, i};
    sort(all(v), greater<pii>());
    for (auto [len, id] : v)
      if (states[id].link != -1)
      cnt[states[id].link] += cnt[id];
    cnt[0] = 1;
  }
 
  void extend(char _c) {
    int c = _c - 'a'; // change for different alphabet
    int cur = state(states[last].len + 1), P = last; 
    cnt[cur] = 1;
    while (P != -1 && states[P].next[c] == -1) {
      states[P].next[c] = cur;
      P = states[P].link;
    }
    if (P == -1)
      states[cur].link = 0;
    else {
      int Q = states[P].next[c];
      if (states[P].len + 1 == states[Q].len)
        states[cur].link = Q;
      else {
        int C = state(states[P].len + 1, states[Q].link);
        cnt[C] = 0;
        copy(states[Q].next, states[Q].next + 26, states[C].next);
        while (P != -1 && states[P].next[c] == Q) {
          states[P].next[c] = C;
          P = states[P].link;
        }
        states[Q].link = states[cur].link = C;
      }
    }
    last = cur;
  }

  ll dfs(int u = 0) {
    if (dp[u]) return dp[u];

    fo(i,26)
      if (states[u].next[i] != -1) 
        dp[u] += dfs(states[u].next[i]);
    return dp[u] += 1;
  }

  ll dfsCnt(int u = 0) {
    if (dp[u]) return dp[u];

    fo(i,26)
      if (states[u].next[i] != -1) 
        dp[u] += dfsCnt(states[u].next[i]);
    return dp[u] += cnt[u];
  }

  void dfsKthSmallestSubstr(ll& K, string& out, int u = 0) {
    if (!K) return;
    K--;
    //deb2(K,out);

    fo(i,26) {
      int v = states[u].next[i];
      //deb2(v, dp[v]);
      if (v > -1) {
        if (K >= dp[v]) K -= dp[v];
        else {
          out += (char)(i + 'a');
          return dfsKthSmallestSubstr(K, out, v);
        }
      }
    }
  }

  void dfsKthSmallestNondistinctSubstr(ll& K, string& out, int u = 0) {
    if (K < cnt[u]) return;
    K -= cnt[u];
    //deb2(K,out);

    fo(i,26) {
      int v = states[u].next[i];
      //deb2(v, dp[v]);
      if (v > -1) {
        if (K >= dp[v]) K -= dp[v];
        else {
          out += (char)(i + 'a');
          return dfsKthSmallestNondistinctSubstr(K, out, v);
        }
      }
    }
  }
};
