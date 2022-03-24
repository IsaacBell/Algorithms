// Reverses sequences of operations to get orig permutation
// Orig seq is described in every fn's comment header
template <class T>
struct OperationReverser {
  using vt = vector<T>;
  OperationReverser<T>() {};

  // At 𝑖-th op, choose 1st 𝑖 els of array and cyclically
  // shift them to the right an arbitrary number of times
  // 𝑂(𝑛2) 
  vt reverse_cyclic_shift(vt& A) {
    szn(n,A);
    vt ans(n);

    // On 𝑖-th (𝑖=𝑛, 𝑛−1, …, 2, 1) op select first 𝑖 els and
    // rotate them left 𝑑[𝑖] times
    // (els with #s 𝑖+1 and more remain in their places)
    ford1(i,n+1) {
      ll idx = 0;
      fo(j,i) idx = A[j] == i ? j : idx;

      // For each 𝑖 from right to left, performing a left 
      // cyclic shift operation, we move the # 𝑖 at index 𝑖.
      // So we move 𝑂(𝑛) numbers 𝑛 times
      vt B(i);
      fo(j,i) B[(i - 1 - idx + j) % i] = A[j];
      fo(j,i) A[j] = B[j];
      
      ans[i - 1] = i != 1 ? (idx + 1) % i : 0;
    }

    return ans;
  }
};
