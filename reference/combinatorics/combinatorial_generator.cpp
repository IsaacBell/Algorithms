template <class T = ll>
struct CombinatorialGenerator {
  using vt = vector<T>;
public:
  vt data;
  T n, m, k;

  CombinatorialGenerator<T>() {};
  CombinatorialGenerator<T>(T n_): n(n_) {};
  CombinatorialGenerator<T>(T n_, T m_): n(n_), m(m_) {};
  CombinatorialGenerator<T>(T n_, T m_, T k_): n(n_), m(m_), k(k_) {};

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
private:
  // Modular inverse
  T inv(T a, T p = mod) {
    return binpowmod(a, p-2);
  }
};