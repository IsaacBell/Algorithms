template <class T = ll>
struct SubArrayProcessor {
  using vt = vector<T>;

  vt data;
  const ll n;

  SubArrayProcessor(vt& in): data(in), n(in.sz()) {};

  template <class Fn>
  ll bsearch(Fn&& check) {
    ll lo = mod, hi = 0;
    fo(i,n) {
      hi += data[i];
      ckmin(lo, data[i]);
    }

    ll ans = -1;
    while (lo <= hi) {
      ll mid = (lo+hi) / 2;
      if (check(mid)) ans = mid, hi = mid - 1;
      else lo = mid + 1;
    }

    return ans;
  }

  ll getKMaxSumSubarrays(ll k) {
    auto check = [&](ll total) {
      ll tmp = 0, cnt = 1;
      fo(i,n)
        if (data[i] > total) return false;
        else if (data[i]+tmp <= total) tmp += data[i];
        else tmp = data[i], cnt++;
      return cnt <= k;
    };

    return bsearch(check);
  }

  // Count # subarrays where sum % k == 0
  // Value of k defaults to value of n
  ll numSubarraysWithSumDivisibleByK(ll k = -mod) {
    if (k == -mod) k = n; // default k to n

    ll sum = 0;
    vl modd(k);
    
    fo(i,k) {
    	sum += data[i];
      ll idx = ((sum%k)+k)%k;
      modd[idx]++;
    }

    ll res = 0;
    fo(i,k)
      if(modd[i] > 1)
        res += (modd[i] * (modd[i]-1) / 2);
    res += modd[0];
    
    return res;
  }

  // Count # subarrays w/ sum x.
  ll numSubarraysWithSumofK(ll sum) {
    map<ll,ll> mpp;
    ll cnt = 0, cur = 0;

    fo(i,n) {
      cur += data[i];
      if (cur == sum) cnt++;
      if (mpp.count(cur - sum))
        cnt += mpp[cur-sum];
      mpp[cur]++;
    }

    return cnt;
  }
};
