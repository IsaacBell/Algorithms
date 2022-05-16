// Tested (todo - stress test)
struct DP {
  int n;

  DP(int n_): n(n_) {}

  int numPermutationsWithKInversions(int k) {
    vvi dp(n+1, vi(k+1));

    // for k = 0, # of permutations is 1 for every n
    Fo(i,1,n+1) dp[i][0] = 1;

    Fo(i,1,n+1)
      Fo(j,1,k+1) {
        int val = dp[i-1][j];
        if(j >= i) val -= dp[i-1][j-i];

        dp[i][j] = dp[i][j-1] + val;
      }

    int ans = dp[n][k];
    if(k >= 1)
        ans -= dp[n][k-1];
 
    return ans;
  }
};


// discard pile
struct DP {
  struct option {
    int t, p, id;
    option(int _t,int _p, int _id) : t(_t), p(_p), id(_id) {}
  };

  vector<option> v;
  const int n;

  DP(vi& in): v(in), n(in.sz()) {};

  // todo - what is this for again?
  vi get_ans() {
    vvi dp(101, vi(n+1, mod));
    dp[0][0] = 0;
    Fo(k,1,n+1) {
      auto [t,p,id] = v[k-1];
      dp[0][k] = 0;
      for (int i = 100; i > 0; i--) {
        int prev = max(0,i - p);
        dp[i][k] = dp[i][k-1];
        ckmin(dp[i][k], dp[prev][k-1] + t);
      }
    }
    vector<int> ans;
    int top = dp[100][n];

    if (top == mod) return {-1};
    for (int i = 100, k = n; k >= 1; k--) {
      if (dp[i][k] == dp[i][k-1]) {
        continue;
      }
      ans.emplace_back(v[k-1].id);
      i = max(0, i - v[k-1].p);
    }

    reverse(all(ans));
    ans.emplace_back(t);
    return ans;
  }
};

// discard pile
template<class T = ll>
struct ShortestPath {
  const int n;
  //
};