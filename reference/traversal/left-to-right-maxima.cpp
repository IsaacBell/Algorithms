// Includes

template <class T>
struct min_monoid {
  typedef T value_type;
  value_type unit() const { return std::numeric_limits<T>::max(); }
  value_type mult(value_type a, value_type b) const { return std::min(a, b); }
};
template <class T>
struct max_monoid {
    typedef T value_type;
    value_type unit() const { return std::numeric_limits<T>::lowest(); }
    value_type mult(value_type a, value_type b) const { return std::max(a, b); }
};

/**
 * @brief Sparse Table (idempotent monoid)
 * @note the unit is required just for convenience
 * @note $O(N \log N)$ space
 */
template <class IdempotentMonoid>
struct sparse_table {
    typedef typename IdempotentMonoid::value_type value_type;
    std::vector<std::vector<value_type> > table;
    IdempotentMonoid mon;
    sparse_table() = default;

    /**
     * @note $O(N \log N)$ time
     */
    template <class InputIterator>
    sparse_table(InputIterator first, InputIterator last, const IdempotentMonoid & mon_ = IdempotentMonoid())
            : mon(mon_) {
        table.emplace_back(first, last);
        int n = table[0].size();
        int log_n = 32 - __builtin_clz(n);
        table.resize(log_n, std::vector<value_type>(n));
        REP (k, log_n - 1) {
            REP (i, n) {
                table[k + 1][i] = i + (1ll << k) < n ?
                    mon.mult(table[k][i], table[k][i + (1ll << k)]) :
                    table[k][i];
            }
        }
    }

    /**
     * @note $O(1)$
     */
    value_type range_get(int l, int r) const {
        if (l == r) return mon.unit();  // if there is no unit, remove this line
        assert (0 <= l and l < r and r <= (int)table[0].size());
        int k = 31 - __builtin_clz(r - l);  // log2
        return mon.mult(table[k][l], table[k][r - (1ll << k)]);
    }
};

/**
 * @brief Length of Left-to-right Maxima (前処理 $O(n \log n)$ + $O(1)$)
 * @description computes the lengths of the left-to-right maxima for the given interval
 * @note the left-to-right maxima for a sequence $a$ means the subsubsequence of the elements $a_i$ which satisfy $\forall j \lt i. a_j \lt a_i$.
 */
class left_to_right_maxima {
  vi depth;
  sparse_table<min_monoid<int> > table;

public:
  left_to_right_maxima() = default;

  int operator () (int l, int r) const {
    assert (0 <= l and l <= r and r <= (int)depth.size());
    if (l == r) return 0;
    return depth[l] - table.range_get(l, r) + 1;
  }

private:
  left_to_right_maxima(const vi& depth_)
      : depth(depth_), table(ALL(depth_)) {
  }

public:
  /**
   * @note this is just a constructor, but is needed to specify template arguments.
   */
  template <class T, class Comparator = std::less<T>, class RandomAccessIterator>
  static left_to_right_maxima construct(RandomAccessIterator first, RandomAccessIterator last, const Comparator & cmp = Comparator()) {
    int n = std::distance(first, last);

    // make a forest
    std::vector<int> parent(n, -1);
    std::stack<int> stk;
    fo(i, n) {
      while (not stk.empty() and cmp(*(first + stk.top()), *(first + i))) {
        parent[stk.top()] = i;
        stk.pop();
      }
      stk.push(i);
    }

    // calculate depths
    std::vector<int> depth(n);
    ford(i, n) {
      if (parent[i] != -1) {
        depth[i] = depth[parent[i]] + 1;
      }
    }

    return left_to_right_maxima(depth);
  }
};