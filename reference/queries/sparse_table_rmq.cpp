// Set constraints & parameters

const int mod = 1'000'000'007;
const int N = 1e6;

vi A;
vvi M;
vi logs;

// query formula
int solution(int L, int R) {
  int len = R - L + 1;
  int k = logs[len];
  // while ((1 << (k+1)) <= len)
  //   k++;
  return min(M[L][k], M[R - (1<<k) + 1][k]);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());

  // read input
  logs.resize(N);   // logarithms
  A.resize(N);   // array
  M.resize(N, vi( floor(log2(N)) ));  //sparse table ("M" for matrix)

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    M[i][0] = A[i];
  }

  // log
  logs[1] = 0;
  for (int i = 2; i <= n; i++)
    logs[i] = logs[i/2]+1;

  // pre-processing
  for (int j = 1; j < floor(log2(N)); j++)
    for (int i = 0; i + (1 << j) - 1 < n; i++)
      M[i][j] = min(M[i][j-1], M[i + (1 << (j-1))][j-1]);

  // answer queries
  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    int L, R;
    cin >> L >> R;
    cout << solution(L, R) << "\n";
  }

  return 0;
}
