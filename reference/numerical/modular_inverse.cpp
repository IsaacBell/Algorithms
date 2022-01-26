ll xgcd(ll A, ll b, ll &x, ll &y) {
	if(!A) { x = 0, y = 1; return b; }
	ll x1, y1;
	ll d = xgcd(b % A, A, x1, y1);
	x = y1 - (b / A) * x1;
	y = x1;
	return d;
}
 
ll modular_inverse(ll A, ll m) {
	ll x, y;
	ll g = xgcd(A, m, x, y);
	if(g != 1)
		return -1;
	else {
		x = (x % m + m) % m;
		return x;
	}
}