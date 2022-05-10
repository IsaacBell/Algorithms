/*
  TOC:
    - General implementation
    - Alternative method in O(log n), using Extended Euclidean Algorithm
    - Modular inverse of all numbers in range [1,n] in O(n)

  Todo:
    - Mobius Fn

  References:
    - https://artofproblemsolving.com/community/c90633h1291397

*/

/*
  General implementation
*/

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

//======================
/*
Alternative method in O(log n)

Using Extended Euclidean Algorithm to get the inverse of a % m.
*/

int inv(int a, int m) {
    int temp=m, q, t, u=0, v=1;
    if(m==1) return 0;
    while(a>1)
    {
        q=a/m;
        t=m;
        m=a%m;
        a=t;
        t=u;
         u=v-q*u;
         v=t;
    }
    if(v<0) v+=temp;
    return v;
}

//======================
/*
  Fermat's Little Theorem gives a^(p-1) ~= 1 mod p if (a,p) = 1, where p is a prime.
  
  Therefore, we can calculate the modular inverse of a as a^(p-2), by fast exponentiation.
  
  Time Complexity is O(log p).
*/

//======================
/*
  Modular inverse of all numbers in range [1,n] in O(n)
*/

int inv[111111];
int main(void) {
    cin>>n;
    int i;
    inv[1]=1;
    for(i=2 ; i<=n ; i++)
    {
        inv[i]=((mod-mod/i)*inv[mod%i])%mod;
        cout<<inv[i]<<endl;
    }
}
