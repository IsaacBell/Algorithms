/*
  Note - tree indexing is 1-based

  Usage:
    idx    0, 1, 2, 3, 4, 5, 6, 7;
    A is {18,17,13,19,15,11,20,oo};

    st.RMQ(1, n));       // 11
    st.update(5, 5, 77); // update A[5] to 77
*/
template <class T>
struct SegmentTree {
  using vt = vector<T>;

public:
  vt A, st, lazy;

  int n;

  T l(int p) { return p << 1; }
  T r(int p) { return (p << 1) + 1; }

  SegmentTree(int n_, ll fillValue = 0): n(n_), st(4*n_, fillValue), lazy(4*n_, -1) {}
  SegmentTree(vt &in, ll fillValue = 0): n(in.sz()) {
    auto n_ = in.sz();
    A.rsz(n_);
    st.rsz(4*n_, fillValue);
    lazy.rsz(4*n_, -1);
    std::copy(all(in), A.begin());
    build(1, 0, n-1);
  }
  
  int RMQ(int p, int L, int R, int i, int j) {
    propagate(p, L, R);
    if (p > j) return -1;
    if ((L >= i) && R <= j) return st[p];
    int mid = (L+R) / 2;
    auto left = RMQ(l(p), L, mid, i, min(mid, j));
    auto right = RMQ(r(p), mid + 1, R, max(i, mid+1), j);
    return merge(left, right);
  }


private:

  void build(int i, int L, int R) {
    if (L == R) st[i] = A[L];
    else {
      int mid = (L+R) / 2;
      build(l(i), L, mid);
      build(r(i), mid+1, R);
      st[i] = merge(st[l(i)], st[r(i)]);
    }
  }

  T merge(int a, int b) {
    static_assert(
      0,
      "Did you update the merge fn as needed?"
    );
    
    // Edge Case
    if (a == -1) return b;
    if (b == -1) return a;

    return min(a,b);
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {
      st[p] = lazy[p];
      if (L != R) lazy[l(p)] = lazy[r(p)] = lazy[p];
      else A[L] = lazy[p];
      lazy[p] = -1;
    }
  }

  void update(int p, int L, int R, int i, int j, int val) {
    propagate(p, L, R);
    if (p > j) return;
    if ((L >= p) && (R <= j)) {
      lazy[p] = val;
      propagate(p, L, R);
    } else {
      int mid = (L+R) / 2;
      update(l(p), L, mid, i, min(mid,j), val);
      update(r(p), mid+1, R, max(i, mid+1), j, val);
      int lSubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rSubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
      st[p] = (lSubtree <= rSubtree) ? st[l(p)] : st[r(p)];
    }
  }
};
