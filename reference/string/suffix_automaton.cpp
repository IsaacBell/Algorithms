struct SuffixAuto {
  struct State {
    int len, link;
    int next[26];
    State(int _len = 0, int _link = -1) : len(_len), link(_link) {
      memset(next, -1, sizeof(next));
    }
  };
 
  vector<State> states;
  vl dp; 
  int last, K;
 
  SuffixAuto(const string &S) {
    dp.rsz(N);
    init(S);
  }
 
  inline int state(int len = 0, int link = -1) {
    states.emplace_back(len, link);
    return states.size() - 1;
  }

  ll numDistinctSubstrings() {
    return dfs(0) - 1;
  }

  string kthLexicographicallySmallestSubstr(ll K) {
    string str = "";
    dfs();
    dfsKthSmallestSubstr(K, str);
    return str;
  }

private:
  void init(const string &S) {
    states.reserve(2 * S.size());
    last = state();
    for (char c : S)
      extend(c);
  }
 
  void extend(char _c) {
    int c = _c - 'a'; // change for different alphabet
    int cur = state(states[last].len + 1), P = last; 
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
};


void solution() {
  rd(s >> k);
  SuffixAuto sa(s);
  put(sa.numDistinctSubstrings());
  put(sa.kthLexicographicallySmallestSubstr(k));
}
