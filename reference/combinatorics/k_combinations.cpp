/*
  Generate next lexicographical K-combination

  Find the rightmost element that has not yet reached its highest possible value. 
  
  Once finding this element, we increment it, and assign the lowest valid value to all subsequent elements
*/
bool next_combination(vl& A, ll nn) {
  szn(kk,A);
  ford(i,kk) {
    if (A[i] < nn - kk + i + 1) {
      A[i]++;
      Fo(j, i + 1, kk)
        A[j] = A[j - 1] + 1;
      return true;
    }
  }
  return false;
}

/*
  Generate all -combinations such that adjacent combinations differ by one element
*/

vector<int> ans;

void gen(int n, int k, int idx, bool rev) {
    if (k > n || k < 0)
        return;

    if (!n) {
        for (int i = 0; i < idx; ++i) {
            if (ans[i])
                cout << i + 1;
        }
        cout << "\n";
        return;
    }

    ans[idx] = rev;
    gen(n - 1, k - rev, idx + 1, false);
    ans[idx] = !rev;
    gen(n - 1, k - !rev, idx + 1, true);
}

void all_combinations(int n, int k) {
    ans.resize(n);
    gen(n, k, 0, false);
}
