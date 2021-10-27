class Solution {
public:
  int maxSubArray(vector<int>& A) {
    szn(n,A);
    int mx = A[0], cur = mx;
    Fo(i,1,n) {
      cur = max(A[i] + cur, A[i]);
      ckmax(mx, cur);
    }
    return mx;
  }
};