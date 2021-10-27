class Solution {
public:
  int maxArea(vector<int>& H) {
    szn(n,H);
    int l = 0, r = n - 1, mx = 0;
    while (l < r) {
      int cur = min(H[l], H[r]) * (r - l);
      ckmax(mx, cur);
      
      if (H[l] < H[r]) l++;
      else r--;
    }

    return mx;
  }
};