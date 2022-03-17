struct StringProcessor {
  string S;
  const ll n;

  StringProcessor(string& str): S(str), n(str.sz()) {};

  ll numStringsWithRemovals() {
    vl idx(26), dp(1e6);
    dp[0] = 1;

    Fo(i,1,n+1) {
      dp[i] = 2 * dp[i-1];
      if (idx[s[i-1]-'a'] >= 0)
        dp[i] -= dp[idx[s[i-1]-'a']];

      dp[i] = (dp[i] + md)%md;
      idx[s[i-1]-'a'] = i-1;
    }

    put(dp[n]-1+md)%md);
  }
}