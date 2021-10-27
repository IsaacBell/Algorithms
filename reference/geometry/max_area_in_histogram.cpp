int maxArea(vector<int>& H) {
    szn(H);
    int mx = 0, l = 0, r = n - 1;
    while (l < r) {
      ckmax(mx, min(H[l], H[r]) * (r - l));
      if (H[l] < H[r]) l++;
      else r--;
    }
    return mx;
  }