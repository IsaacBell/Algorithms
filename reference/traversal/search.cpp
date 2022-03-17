template <class T = ll>
struct Search {
  using pt = pair<T>;
  using vt = vector<T>;
  using vpt = vector<pt>;
public:
  vt data;
  vt sorted;
  vpt indexed_data; // {data[i], i+1}
  const ll n;

  Search(): n(0) {};
  Search(vt &in):
    data(in),
    sorted(in),
    n(in.sz())
  {
    fo(i,n) indexed_data.pb({data[i], i+1});
    sortall(sorted), sortall(indexed_data);
  };

  pt twoSum(ll k) {
    ll l = 0, r = n-1;
    while (l < r) {
      ll cur = indexed_data[l].F + indexed_data[r].F;
      if (cur > k) r--;
      else if (cur < k) l++;
      else if (cur == k)
        return { indexed_data[l].S, indexed_data[r].S };
    }

    return -1;
  }

  T mex() {
    T last_x = 0;  // only for debug
    T y = 0;
    auto first = data.begin(), last = data.end();

    while (first != last) {
      auto x = *first;
      assert (last_x <= x);
      last_x = x;
      if (y < x) break;
      if (y == x) ++ y;

      first++;
    }

    return y;
  }

  // smallest sum we can't create using a subset of arr els
  void smallestMissingSubsetSum() {
    ll o = 1;
    fo(i,n)
      if (o < A[i]) break;
      else o += A[i];

    return o;
  }

  T maxSubarraySum() {
    ll best = -mod, cur = 0;
    trav(a, data) {
      cur = max(cur+a, a);
      ckmax(best,cur);
    }
    return best;
  }
  T kadanes() { return maxSubarraySum(); }
};
