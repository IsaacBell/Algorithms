template<typename Acc, typename Pred>
int search(int node, int b, int e, int l, int r, Acc& acc, Pred&& pred) {
  if (e <= l) return -1;
  if (b >= r) return b;
  if (b >= l && e <= r && pred(acc + T[node]) == 0) {
    acc = acc + T[node];
    return -1;
  }
  if (b + 1 == e) return b;

  int m = (b + e) / 2;
  int res = search(node * 2, b, m, l, r, acc, pred);
  if (res != -1) return res;
  return search(node * 2 + 1, m, e, l, r, acc, pred);
}
