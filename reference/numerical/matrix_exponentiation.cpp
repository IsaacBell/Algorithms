

#define DIM 2 // default to 2. Set value according to problem.
struct matrix{
  ll a[DIM][DIM];
	
	// constructor. Make an empty array.
	matrix() {
		memset(a, 0, sizeof(ll) * DIM * DIM);
	}
	
	// constant matrix (M). Set value according to problem.
	void unit_matrix() {
		a[0][0] = 26; a[0][1] = 52;
		a[1][0] = 0; a[1][1] = 1;
	}
	
	matrix operator* (matrix b) {
		matrix c;
		for (int k = 0; k < DIM; ++ k) { 
			for (int i = 0; i < DIM; ++i) {
				for (int j = 0; j < DIM; ++j) {
					c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % mod;
				}
			}
		}
		return c;
	}
};
 
matrix pow_matrix(matrix a, ll n) {
	if (n == 1) return a;
	
	matrix b = pow_matrix(a, n / 2);
	b = b * b;
	if (n & 1) b = b * a;
	
	return b;
}