/*
  The basic idea is to apply the Inclusion-Exclusion Principle by enumerating every number 
  2 <= i <= m that contains no repeated factors exactly once, and for each such i, 
  counting the number of numbers in the input that are divisible by i and either adding 
  or subtracting this from the total. 
  
  The key difference is that we can do the counting part "stupidly", simply by testing 
  whether each possible multiple of i appears in the input, and this still takes just 
  O(m log m) time.

  How many times does the innermost line c += data[j].freq; in countCoprimes() repeat? 

  The body of the outer loop is executed once for each number 2 <= i <= m that contains 
  no repeated prime factors; this iteration count is trivially upper-bounded by m. 
  
  The inner loop advances i steps at a time through the range [2..m], so the number of 
  operations it performs during a single outer loop iteration is upper-bounded by m / i. 
  
  Therefore the total number of iterations of the innermost line is upper-bounded by the sum 
  from i=2 to m of m/i. The m factor can be moved outside the sum to get an upper bound of

  =>  m * sum{i=2..m}(1/i)
  
  That sum is a partial sum in a harmonic series, and it is upper-bounded by log(m), 
  so the total number of innermost loop iterations is O(m log m).
*/

#include <iostream>
#include <vector>

using namespace std;

// Entry<ll> initialElem = { 0, 0, 1 };
template<class T = ll>
struct Entry {
  T freq;       // Frequency that this number occurs in the input list
  T parity;     // 0 for even number of factors, 1 for odd number
  T prod;       // Product of distinct prime factors

  Entry<T>(): freq(0), parity(0), prod(1) {};
};

// Sequence<ll> seq(n); seq.read(); seq.build();
// n: input array size, m: number limit
template<class T = ll>
struct Sequence {

public:
  vector<T> input;
  vector< Entry<T> > data;
  T n, m;
  Sequence<T>(T n_, T m_ = (T) 3e6+1): n(n_), m(m_) {
    data.rsz(m_), input.rsz(n_);
  }

  void build() { extendedEratosthenes(); }
  void printNumCoprimes() { put(countCoprimes()); }
  void read()  {
    trav(num, input) {
      rd(num);
      data[num].freq++;
    }
  }
  
  ll getNumCoprimes() { return countCoprimes(); }

private:
  ll countCoprimes() {
    ll total = static_cast<ll> (n) * (n - 1) / 2;
    Fo (i, 2, m + 1) {
      if (data[i].prod) {
        // i must have no repeated factors.

        ll c = 0;
        for (ll j = i; j <= m; j += i) {
          c += data[j].freq;
        }

        total -= (data[i].parity * 2 - 1) * static_cast<ll> (c) * (c - 1) / 2;
      }
    }
    
    ret total;
  }

  void extendedEratosthenes() {
    ll i;
    for (i = 2; i * i <= m; ++i) {
      if (data[i].prod == 1) {
        for (ll j = i, k = i; j <= m; j += i) {
          if (--k) {
            data[j].parity ^= 1;
            data[j].prod *= i;
          } else {
            // j has a repeated factor of i: knock it out.
            data[j].prod = 0;
            k = i;
          }
        }
      }
    }

    // Fix up numbers with a prime factor above their square root.
    for (; i <= m; ++i) {
      if (data[i].prod && data[i].prod != i) {
        data[i].parity ^= 1;
      }
    }
  }
};

void solution() {
  rd(n);
  Sequence<ll> seq(n); seq.read(); seq.build();

  seq.printNumCoprimes();
}
