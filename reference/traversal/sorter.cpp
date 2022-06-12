template <class T = ll>
struct Sorter {
  using vt = vector<T>;
public:
  vt data;
  vt sorted;
  const ll n;

  Sorter(): n(0) {};
  Sorter(vt &in): data(in), n(in.sz()) {
    sorted.rsz(in.sz());
    std::copy(all(in), sorted.begin());
  };

  void resize(ll n_ = -1) {
    if (n_ == -1) n_ = n;
    data.resize(n_);
    sorted.resize(n_);
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

  /*
  	Sorter<ll> sorter(A);
    put(sorter.kthSmallestEl(k)
  */
  T kthSmallestEl(ll k) { return kthSmallestEl(0, n-1, k); }

  /*
    Linear time O(n+k) stable sort
    Needs small value ranges e.g. [1..99]

    auto sorted = countingSort(1, 99);
  */
  vt countingSort(ll L, ll R) {
    ll k = R - L + 1;
    vt out(n);
    vt freq(k);
    fo(i,n) freq[data[i] - L]++;
    Fo(i,1,k) freq[i] += freq[i-1];
    ford(i,n) {
      out[freq[data[i]-L]] = data[i];
      freq[data[i] - L]--;
    }
    return out;
  }

  // Ex: max # movies you can watch given start & end times
  ll maxNumNonOverlappingIntervals(vt& StartTimes, vt& EndTimes) {
    vpl p(n);
    fo(i,n)
      // rd(p[i].F >> p[i].S);
      p.pb({StartTimes[i], EndTimes[i]});

    sort(all(p), [](pl& StartTimes, pl& EndTimes) {
      return StartTimes.S < EndTimes.S;
    });

    ll i = 0, o = 0, last = -1;
    while (i < n) {
      if (StartTimes[i].F >= last) {
        o++;
        last = StartTimes[i].S;
      }
      i++;
    }
    return o;
  }
  
  // Ex: Max # occupants in room given entry and exit times
  ll maxOccupants(vt& StartTimes, vt& EndTimes) {
    vpl p;
    fo(i,n) {
      p.pb({StartTimes[i], 1});
      p.pb({EndTimes[i], -1});
    }
    sortall(p);
    ll o = 0, best = 0;
    trav(a,StartTimes) {
      o += a.S;
      ckmax(best,o);
    }
    return best;
  }

  /*
    For each customer, gives the price that they will pay
    if a sale is made, else -1

    Sellers: price of each item/sale
    Consumers: max price per customer in order they arrive
  */
  vt matchBuyersToSellers(vt& Sellers, vt& Consumers) {
    vt output;
    szn(n,Sellers); szn(m,Consumers);
    multiset<T> Ti;
    T tmp;
    for(T seller : Sellers) Ti.insert(seller);

    fo(i,m) {
      auto it = Ti.upper_bound(Consumers[i]);
      if (it == Ti.begin())
        put(-1);
      else {
        output.pb(*(--it)); // thought - how to make this offline?
        Ti.erase(it);
      }
    }
  }

  // Each container can hold maxWeightPerContainer items
  T minContainersNeeded(T maxWeightPerContainer) {
    ll o = 0, l = 0, r = n-1;
    while (l <= r)
      if (sorted[l] + sorted[r] <= maxWeightPerContainer)
        o++, l++, r--;
      else
        o++, r--;

    return o;
  }

  /*
    Example Use Case:

    Distribute the apartments so that as many 
    applicants as possible will get an apartment.

    A: Desired apt sizes per applicant
    B: Actual apt sizes
  */
  T distributeMaxPossible(vt A, vt B, ll k) {
    szn(nn, A);
    szn(mm, B);
    sortall(A);
    sortall(B);

    ll a = 0, b = 0, o = 0;
    while (a<nn && b<mm) {
      if (abs(A[a] - B[b]) <= k) a++, b++, o++;
      else {
        // If apt size too big, move apt pointer
        if (A[a] - B[b] > k) b++;
        // If apt too small, skip that applicant
        else a++;
      }
    }

    return o;
  }

private:
  T kthSmallestEl(ll L, ll R, ll k) {
    if (L == R) return sorted[L];
    ll q = randPartition(L, R);
    // deb(q);
    if (q + 1 == k) return sorted[q];
    if (q + 1 > k) return kthSmallestEl(L, q-1, k);
    return kthSmallestEl(q+1, R, k);
  }

  ll randPartition(ll low, ll high) {
  	ll i = low, x = sorted[high];
    Fo(j, low, high) {
      if (sorted[j] <= x) {
        swap(sorted[i], sorted[j]);
        i++;
      }
    }
    swap(sorted[i], sorted[high]);
    return i;
  }
};
