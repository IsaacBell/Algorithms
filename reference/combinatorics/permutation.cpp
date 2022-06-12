template <class T = ll>
struct Permutation {
  using vt = vector<T>;

  vt A;
  const ll n;

  Permutation(vt& in): A(in), n(in.size()) {};

  /*
    Count inversions w/ modified merge sort

    If front of right (sorted) sublist is taken b4
    the left sublist, increment inv counter by size
    of current L sublist
  */
  ll inversionCount() {
    vt A2(all(A));
    return mergeSort(A, A2, 0, n - 1);
  }

  ll numBubbleSwapsToSort() { return inversionCount(); }

private:
  // merge two sorted subarrays `arr[low … mid]` and `arr[mid+1 … high]`
  ll merge(vl arr, vl aux, ll low, ll mid, ll high) {
    ll k = low, i = low, j = mid + 1;
    ll inversionCount = 0;

    // while there are elements in the left and right runs
    while (i <= mid && j <= high) {
      if (arr[i] <= arr[j])
        aux[k++] = arr[i++];
      else {
        aux[k++] = arr[j++];
        inversionCount += (mid - i + 1);
      }
    }

    // copy remaining elements
    while (i <= mid)
      aux[k++] = arr[i++];

    /* no need to copy the second half (since the remaining items
    are already in their correct position in the temporary array) */

    // copy back to the original array to reflect sorted order
    Fo(i, low, high+1)
      arr[i] = aux[i];

    return inversionCount;
  }

  // Sort array `arr[low…high]` using auxiliary array `aux`
  ll mergeSort(vl arr, vl aux, ll low, ll high) {
    if (high <= low) return 0;

    ll mid = (low + ((high - low) >> 1));
    ll inversionCount = 0;

    // split
    inversionCount += mergeSort(arr, aux, low, mid);
    inversionCount += mergeSort(arr, aux, mid + 1, high);

    // merge halves
    inversionCount += merge(arr, aux, low, mid, high);

    return inversionCount;
  }
};
