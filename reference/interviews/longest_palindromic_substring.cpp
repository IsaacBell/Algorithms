class Solution {
public:
  string longestPalindrome(string s) {
    szn(n,s);
    if (!n) return "";
    vector<vector<bool>> dp(n+1, vector<bool>(n+1));

    // i,j => len,end
    ll end = 1, len = 1;

    fo(i,n+1) dp[0][i] = dp[1][i] = 1;
    Fo(i, 2, n+1)
      Fo(j,i,n+1)
        if (s[j-i] == s[j-1] && dp[i-2][j-1] == 1)
          dp[i][j] = 1, len = i, end = j;

    string o;
    Fo(i, end - len + 1, end+1)
      o += s[i-1];
    
    return o;
  }
};
