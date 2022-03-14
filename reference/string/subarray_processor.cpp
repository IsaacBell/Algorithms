template <class T = ll>
struct SubArrayProcessor {
  using vt = vector<T>;

  vt data;
  const ll n;

  SubArrayProcessor(vt& in): data(in), n(in.sz()) {};

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
