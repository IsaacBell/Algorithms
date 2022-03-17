// Reverses sequences of operations to get orig permutation
// Orig seq is described in every fn's comment header
template <class T>
struct OperationReverser {
  using vt = vector<T>;
  OperationReverser<T>() {};

  // At 𝑖-th op, choose 1st 𝑖 els of array and cyclically
  // shift them to the right an arbitrary number of times
  vt reverse_cyclic_shift(vt& A) {
    szn(n,A);
    vt ans(n);
    ford1(i,n+1) {
      ll idx = 0;
      fo(j,i) idx = A[j] == i ? j : idx;
      vt B(i);
      fo(j,i) B[(i - 1 - idx + j) % i] = A[j];
      fo(j,i) A[j] = B[j];
      ans[i - 1] = i != 1 ? (idx + 1) % i : 0;
    }

    return ans;
  }
};
