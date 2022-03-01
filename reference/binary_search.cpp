/*
    Code Snippets

*/

/* Include these in your header.
   DO NOT include after the "Solution starts here" line
   or you could overwrite the "n" global var.

   Also refer to reference/traversal/_notes.md for details
   on implementation & use cases.
*/
/*==============================*/

// Standard binary search
template <class T>
T bsearch(vector<T>&A, T x) {
  szn(n,s);
  if (!n) return -1;

  T l = 0, r = n-1;
  while (l <= r) {
    auto mid = l + (r-l) / 2;
    if (A[mid] == x) return mid;
    else if (A[mid] < x) l = mid+1;
    else r = mid - 1;
  }
  
  return -1;
}

/*==============================*/

/* 
  Search for an element or condition which requires 
  accessing the current index and its immediate right 
  neighbor's index in the array.

  We could use a lambda to genericize the check, but
  it's easier to just do it manually in your impl.
*/
template <class T>
T bsearch2(vector<T>& A, T x) {
  szn(n,s);
  auto l = 0, r = n;
  while (l < r) {
    auto mid = l + (r-l) / 2;
    if (A[mid] < x) l = mid+1;
    else r = mid;
  }

  if (l != n && A[l] == x) return l;
  return -1;
}

/*==============================*/

/*
  Std way of doing this.
  Use if you just want to do a lower_bound check.
*/
template <class T>
T find_first_non_smaller(vector<T>& A, T x) {
  return lower_bound(all(A), x);
}

// Same functionality as above, but this one can be modified
template <class T>
T find_first_non_smaller(vector<T>& A, T x) {
  szn(n,s);
  if (!n || A.back() < x) return n;

  auto l = 0, r = n-1;
  while (l < r) {
    auto mid = l + (r-l)/2;
    if (A[mid] < x) l = mid+1;
    else r = mid;
  }

  return l;
}

// Modify according to prob at hand
template <class T>
pair<T,T> searchRange(vector<T> &A, T x) {
  return {
    find_first_non_smaller(A, x),
    find_first_non_smaller(A, x+1) - 1
  };
}
template <class T>
T searchRangeLength(vector<T> &A, T x) {
  auto p = searchRange(A, x);
  return p.S - p.F;
}

/*==============================*/
/*
  Ex: 
  auto f = [&](T i) {
    return a[i] < x;
  };
  find_first_false(0, n, f);
*/
template <class T, class F>
T find_first_false(T l, T r, F&& f) {
  --l;
  ++r;
  while (r - l > 1) {
    T m = l + (r - l) / 2; // prefer std::midpoT in C++20
    if (f(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  return r;
}

// l is the position of the last true in the corresponding array b
template <class T>
T find_position(const vector<T>& a, T x) {
  auto f = [&](T i) { return a[i] < x; };
  szn(n,s);
  T pos = find_first_false<T>(0, n - 1, f);
  if (pos == n || a[pos] != x) return n;
  return pos;
}
