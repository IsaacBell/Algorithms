template <class T = ll>
struct CombinatorialGenerator {
  using vt = vector<T>;
public:
  vt data;
  T n, m, k;
  map<T,T> f; // recursion map for fibonnaci #s

  CombinatorialGenerator<T>() {};
  CombinatorialGenerator<T>(T n_): n(n_) {};
  CombinatorialGenerator<T>(T n_, T m_): n(n_), m(m_) {};
  CombinatorialGenerator<T>(T n_, T m_, T k_): n(n_), m(m_), k(k_) {};
  
  T fib(T n) {
    if(f.count(n)) return f[n];
    if(n==0) return 0;
    if(n==1 || n==2) return 1;
    if(n%2==0) {
        T k=n/2;
        T ret1=fib(k-1),ret2=fib(k);
        return f[n]=((((2*ret1)%mod+ret2)%mod)*ret2)%mod;
    } else {
        T k=(n+1)/2;
        T ret1=fib(k-1),ret2=fib(k);
        return f[n]=( (ret1*ret1)%mod + (ret2*ret2)%mod)%mod;
    }
}

  // Ex: necklaces that consist of n pearls and each pearl has m possible colors
  // (Pass n and m as initializer args, or pass m as a fn arg)
  T burnsidesLemma(T m_ = -1e18) {
  	// deb2(n,m);
  	if (m_ != -1e18) m = m_;
    T ans = 0;
    fo(i,n) {
        T temp = binpowmod(m, gcd(i,n));
        // deb2(temp, m); deb(inv(n));
        temp *= inv(n);
        temp %= mod;
        ans += temp;
        ans %= mod;
    }
    return ans;
  }

  // the # of different n×n grids whose each square is black or white
  // Grid A != Grid B if impossible to rotate A such that they match
  // (Pass n and m as initializer args)
  T burnsidesLemmaGrid() {
    T A = n * n;
    T B = (A+3 * (n&1)) / 4;
    T C = (A + (n&1)) / 2;
    return ((binpowmod<T>(2, A)+2*binpowmod<T>(2, B)+binpowmod<T>(2, C))*binpowmod<T>(4,mod-2))%mod;
  }
private:
  // Modular inverse
  T inv(T a, T p = mod) {
    return binpowmod(a, p-2);
  }
};
