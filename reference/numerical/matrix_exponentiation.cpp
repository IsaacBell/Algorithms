template <class T=ll>
struct matrix{
  using vt = vector<T>;
  vt a;
  const int n;
  using DIM = n;
	
	// constructor. Make an empty array.
	matrix<T>(T n_ = 2): n(max(2,n_)) {
		a.rsz(n, vt(n));
	}
	
	// constant matrix<T> (M). Set value according to problem.
	void unit_matrix() {
		a[0][0] = 26; a[0][1] = 52;
		a[1][0] = 0; a[1][1] = 1;
	}
	
	matrix<T> operator* (matrix<T> b, T modd) {
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
