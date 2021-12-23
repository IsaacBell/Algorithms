/* Change this value */
const ll BLOCK_SZ = 0;

void remove(ll i);  // TODO: remove value at idx from data structure
void add(ll i);     // TODO: add value at idx from data structure
ll get_answer();  // TODO: extract the current answer of the data structure

// Query
struct Q {
  ll l, r, i;

  Q(ll l_, ll r_): l(l_), r(r_), i(-1) {}
  Q(ll l_, ll r_, ll i_): l(l_), r(r_), i(i_) {}

  bool operator<(Q& rhs) const {
    return make_pair(l / BLOCK_SZ, r) <
           make_pair(rhs.l / BLOCK_SZ, rhs.r);
  }
};

bool cmp_qys(Q& lhs, Q& rhs) {
  ll lBlock = lhs.l / BLOCK_SZ,
     rBlock = rhs.l / BLOCK_SZ;
  if (lBlock != rBlock)
    return lBlock < rBlock;
  return (lBlock & 1) ? (lhs.r < rhs.r) : (lhs.r > rhs.r);
}

// mos = Mo's, qys = queries
vl mos(vector<Q> qys) {
  vl ans(qys.sz());
  sort(all(qys), cmp_qys);

  /* Init data struct here */

  ll l = 0, r = -1;
  trav(q, qys) {
    while (l > q.l) {
      l--;
      add(l);
    }
    while (r < q.r) {
      r++;
      add(r);
    }
    while (l < q.l) {
      remove(l);
      l++;
    }
    while (r > q.r) {
      remove(r);
      r--;
    }
    ans[q.i] = get_answer();
  }

  return ans;
}

void solution() {
  assert(BLOCK_SZ != 0);
  cin >> n >> m;
  A.rsz(n);
  fo(i,n) cin >> A[i];

  vector<Q> qys;

  fo(i,m) {
    ll l,r; cin >> l >> r;
    l--;r--;
    qys.emplace_back(l,r,i);
  }

  vl o = mos(qys);
  fo(i,m) put(o[i]);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  solution();

  return 0;
}
