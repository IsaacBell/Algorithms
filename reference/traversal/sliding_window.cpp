template <class T = ll>
struct SlidingWindow {
  using vt = vector<T>;
  using Deq = deque<T>;
  vt data;
  const ll n;

  SlidingWindow<T>(vt& in): data(in), n(in.sz()) {};

  vt min_cost(T K) {
    vt ans;
    // ordered_set: policy-based, change comparator
    // if results have near misses
    ordered_set mst;
    fo (i,K) mst.insert(data[i]);
    ll d = 0, mid = *mst.find_by_order((K+1)/2-1);

    fo (i,K) d += abs(data[i] - mid);
    ans.pb(d);

    fo(i,n-K) {
      mst.erase(mst.find_by_order(mst.order_of_key(data[i])));
      mst.insert(data[i+K]);
      ll newmid = *mst.find_by_order((K+1)/2-1);
      d += abs(newmid - data[i+K]) - abs(mid - data[i]);
      if(!(K & 1)) d -= newmid - mid;
      mid = newmid;
      ans.pb(d);
    }

    return ans;
  }

  vt median(T K) {
    vt ans;
    // ordered_set: policy-based, change comparator
    // if results have near misses
    ordered_set mst;
    qll q;
    fo(i,n) {
      if (q.sz() == K) {
        if (K & 1) ans.pb(*mst.find_by_order(K/2));
        else ans.pb(*mst.find_by_order(K/2-1));

        mst.erase(mst.find_by_order(mst.order_of_key(q.front())));
        q.pop();
      }

      qp(data[i]);
      mst.insert(data[i]);
    }
    
    if (K & 1) ans.pb(*mst.find_by_order(K/2));
    else ans.pb(*mst.find_by_order(K/2-1));

    return ans;
  }

  // untested
  vt max(T K) {
    vt ans;
    Deq dq;
    fo(i,n) {
      if (!dq.empty() && dq.front() == i-K) dq.pop_front();
      while (!dq.empty() && data[dq.back()] < data[i])
        dq.pop_back();
      dq.pb(i);
      if (i >= K-1) ans.pb(data[dq.front()]);
    }
    return ans;
  }
};
