#undef F

template <class F = ll>
struct FenwickTree {
  using vf = vector<F>;
  vf bit;  // binary indexed tree
  F n;

  FenwickTree(F n) {
      this->n = n;
      bit.assign(n, 0);
  }

  FenwickTree(vf a) : FenwickTree(a.size()) {
    for (auto i = 0; i < a.size(); i++)
      add(i, a[i]);
  }

  F sum(F r) {
    F ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];
    return ret;
  }

  F sum(F l, F r) {
    return sum(r) - sum(l - 1);
  }

  void add(F idx, F delta) {
    for (; idx < n; idx = idx | (idx + 1))
      bit[idx] += delta;
  }
};

template <class F = ll>
struct FenwickTreeOneBasedIndexing : FenwickTree {
  using vf = vector<F>;
    vector<F> bit;  // binary indexed tree
    F n;

    FenwickTreeOneBasedIndexing(F n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<F> a)
        : FenwickTreeOneBasedIndexing(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    F sum(F idx) {
        F ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    F sum(F l, F r) {
        return sum(r) - sum(l - 1);
    }

    void add(F idx, F delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }
};

// Increasing ranges and querying for single values
// Uses 1-based indexing
template <class F = ll>
struct  FenwickTreeRangePoint {
  using vf = vector<F>;
  vf bit;  // binary indexed tree
  int n;

  void add(F idx, F val) {
    for (++idx; idx < n; idx += idx & -idx)
        bit[idx] += val;
  }

  void range_add(F l, F r, F val) {
      add(l, val);
      add(r + 1, -val);
  }

  F poF_query(F idx) {
      F res = 0;
      for (++idx; idx > 0; idx -= idx & -idx)
          res += bit[idx];
      return res;
  }
  
  FenwickTreeRangePoint(F n) {
      this->n = n;
      bit.assign(n, 0);
  }

  FenwickTreeRangePoint(vf& a) : FenwickTreeRangePoint(a.size()) {
    for (auto i = 0; i < a.size(); i++)
      add(i, a[i]);
  }

  F sum(F r) {
    F res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      res += bit[r];
    return res;
  }

  F sum(F l, F r) {
    return sum(r) - sum(l - 1);
  }
};
template <class F = ll>
struct FenwickTree2D {
  using vf = vector<F>;
  using vvf = vector<vf>;
  vvf bit;
  F n, m;

  // init(...) { ... }

  F sum(F x, F y) {
      F ret = 0;
      for (F i = x; i >= 0; i = (i & (i + 1)) - 1)
          for (F j = y; j >= 0; j = (j & (j + 1)) - 1)
              ret += bit[i][j];
      return ret;
  }

  void add(F x, F y, F delta) {
      for (F i = x; i < n; i = i | (i + 1))
          for (F j = y; j < m; j = j | (j + 1))
              bit[i][j] += delta;
  }
};

template <class F = ll>
struct FenwickTreeMin {
  using vf = vector<F>;
    vf bit;
    F n;
    const F INF = (F) 1e9;

    FenwickTreeMin(F n) {
        this->n = n;
        bit.assign(n, INF);
    }

    FenwickTreeMin(vector<F> a) : FenwickTreeMin(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    F getmin(F r) {
        F ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(F idx, F val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }
};

