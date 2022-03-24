template <class T=ll>
struct matrix{
  using vt = vector<T>;
  using vvt = vector<vt>;
  using DIM = n;

public:
  vvt a;
  const int n;
	
	matrix<T>(vvt& in): a(in), n(in.sz()) {}
	matrix<T>(T n_ = 2): n(max(2,n_)) {
		a.rsz(n, vt(n));
	}

  void readAdjMatrix(int m) {
    while(m--) {
      ll i,j; rd(i >> j);
      i--, j--;
      a[i][j]++;
    }
  }
	
	// constant matrix<T> (M). Set value according to problem.
	void unit_matrix() {
		a[0][0] = 26; a[0][1] = 52;
		a[1][0] = 0;  a[1][1] = 1;
	}

  void build_identity_matrix() {
    for (int i = 0; i < n; i++) a[i][i] = 1;
  }

  matrix<T> operator^ (matrix<T> x, T pw) {
    if (!pw) {
      matrix<T> r(n);
      r.build_identity_matrix();
      return r;
    }
    auto u = x ^ pw/2;
    u *= u;
    if (pw & 1) u *= x;
    return u;
  }
	
	matrix<T> operator* (matrix<T> b, T modd = mod) {
		matrix<T> c;
		for (int k = 0; k < DIM; ++ k) { 
			for (int i = 0; i < DIM; ++i) {
				for (int j = 0; j < DIM; ++j) {
					(c.a[i][j] += a[i][k] * b.a[k][j]) %= modd;
				}
			}
		}
		return c;
	}
};
