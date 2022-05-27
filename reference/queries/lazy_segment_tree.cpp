/*
  Uses lazy propagation for updating ranges
  Ex: Queries which add a number k to each val in a range

	void solution() {
		ll q; rd(n >> q);
		LazySeg<ll> seg;
		seg.init(n);
		Fo(i,1,n+1) {rd(k); seg.update(i,i,k); }
		puts(seg.st); cnl;
		while (q--) {
			rd(w);
			if (w = 1) {
				rd(a>>b);
				// a--;
				seg.update(a, a, b);
			} else {
				rd(a);
				seg.update(1, n, a);
			}
			put(seg.query(1, n));
		}
	}
*/
template<class T> struct LazySeg {
	int sz; vector<T> st, lz;

  T null_qry_val() {
    // what should the query fn return when out-of-range?
    // Ex: 0 for sum/diff queries, -mod or mod for max/min queries
    return 0;
  }
	T comb(T a, T b) {
		return a + b;
	}
	void init(int n) {
		sz = 1; while (sz < n) sz <<= 1;
		st.assign(2 * sz, 0), lz.assign(2 * sz, 0);
	}
	void pull(int i) {
		st[i] = comb(st[i << 1], st[i << 1 | 1]);
	}
	void push(int i, int l, int r) {
		st[i] += lz[i];
		if (l != r) lz[i << 1] += lz[i], lz[i << 1 | 1] += lz[i];
		lz[i] = 0;
	}
	void update(int ql, int qr, T x, int i, int l, int r) {
		push(i, l, r); if (ql > r || qr < l) return;
		// Edit logic if needed, e.g.:
    // if (ql <= l && qr >= r) { lz[i] += x; return void(push(i, l, r)); }
    // or
    // if (ql <= l && qr >= r) { ckmax(lz[i], x); return void(push(i, l, r)); }
    
    if (ql <= l && qr >= r) { lz[i] += x; return void(push(i, l, r)); }
		
    int m = (l + r) >> 1; update(ql, qr, x, i << 1, l, m);
		update(ql, qr, x, i << 1 | 1, m + 1, r); pull(i);
	}
	void update(int ql, int qr, T x) {
		update(ql, qr, x, 1, 0, sz - 1);
	}
	T query(int ql, int qr, int i, int l, int r) {
		push(i, l, r); if (ql > r || qr < l) return null_qry_val();
		if (ql <= l && qr >= r) return st[i]; int m = (l + r) >> 1;
		return comb(query(ql, qr, i << 1, l, m), query(ql, qr, i << 1 | 1, m + 1, r));
	}
	T query(int ql, int qr) {
	  puts(st); cnl;
		return query(ql, qr, 1, 0, sz - 1);
	}
};
