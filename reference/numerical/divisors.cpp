/* 
  Processor for divisor calculations.

  Be careful setting MAXN, beware out-of-bounds errors

  e.g. If the constraint is n <= 1e6, use 1e6+7 as MAXN
*/  

template <class T = ll>
struct Divisors {
  using vt = vector<T>;

  const T n; // MAXN
  vt A;

  Divisors(): n(1e5) {};
  Divisors(T n_) : n(n_) {
    A.rsz(n_);
  };

  void generate(T cnt = 1e5) {
  	if (!A.sz()) A.rsz(n);
    Fo(i,1,n)
      for(int j = i; j < cnt; j += i)
        A[j]++;
  }

  T num_divisors(T i) {
    assert(A[1] && "Run generate() before making calculations");
    return A[i];
  }

  // find max GCD between two #s in array
  T max_common_divisors(vt& arr) {
    vt cnt(n+1);
    fo(i, arr.sz()) cnt[arr[i]]++;

    // find largest divisor that divides >= 2 #s in array.
    // iterate from MAXN, and ++ divisor count if # present
    ford1(i, n) {
      T d = 0;
      for(int j = i; j <= n; j += i)
        d += cnt[j];
      if (d >= 2) return i;
    }

    return 0;
  }
};