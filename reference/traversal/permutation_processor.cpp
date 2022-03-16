template <class T = ll>
struct PermutationProcessor {
  using vt = vector<T>;

public:
  vt data;
  vt pfs; // prefix sums
  vt max_prefix_sum_offset; // see sumPrefixes()
  ll n;

  PermutationProcessor(ll n_): n(n_) {
    data.rsz(n_);
    max_prefix_sum_offset.rsz(n_, -mod), pfs.rsz(n_ + 1);
    iota(all(data), 1);
    sumPrefixes();
  }
  PermutationProcessor(vt data_): data(data_), n(data_.sz()) {
    max_prefix_sum_offset.rsz(n), pfs.rsz(n + 1);
    sumPrefixes();
  }

  void reverse() { reverse(all(data)); }

  template <typename Fn>
  void checkSwaps(Fn& callback) {
    ford1(i,n) {
      swap(data[i], data[i-1]);
      callback(data);
    }
  }

  // max subarray sum after addition transforms:
  // add 𝑥 to the elements on exactly 𝑘 distinct positions
  vt maxTransformedSubarrayWithAddition(ll x) {
    auto transform = [x](ll i, ll j) {
      return min(i,j+1) * x;
    };
    return maxTransformedSubarraySum(x, transform);
  }

  /* max subarray sum after running a transform f(x)
     e.g. adding 𝑥 to els on 𝑘 distinct positions

    returns max val of 𝑓(𝑘) for all 𝑘 from 0 to 𝑛
  */
  template <typename Fn>
  vt maxTransformedSubarraySum(ll x, Fn& transform) {
    vt ans(n+1);
    fo(i,n+1) {
      ll best = 0;
      fo(j,n)
        ckmax(
          best,
          max_prefix_sum_offset[j] + transform(i,j)
        );
      ans[i] = best;
    }
    
    return ans;
  }

private:
  void sumPrefixes() {
    max_prefix_sum_offset[0] = pfs[0] = 0;
    fo(i,n) pfs[i+1] = data[i] + pfs[i];

    fo(i,n) {
      ll best = -mod;
      Fo(j,0,n-i) ckmax(best, pfs[j+i+1] - pfs[j]);
      max_prefix_sum_offset[i] = best;
    }
  }
};
