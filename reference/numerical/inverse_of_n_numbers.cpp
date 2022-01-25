ll qpow(ll a, ll b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

vl pre(1000010), suf(1000010); // prefix, suffix, product
ll pr = 1;

void solution() {
	pre[0] = suf[n + 1] = 1;
	Fo(i,1,n+1) rd(A[i]);
	Fo(i,1,n+1) {
		pre[i] = pre[i - 1] * a[i] % mod;
		suf[n + 1 - i] = suf[n + 2 - i] * a[n + 1 - i] % mod;
		pr = pr * a[i] % mod;
	}
	pr = qpow(pr, mod - 2);
	Fo(i,1,n+1)
		put(pre[i - 1] * suf[i + 1] % mod) * pr % mod);
	}
}