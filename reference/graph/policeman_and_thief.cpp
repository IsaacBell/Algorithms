struct State {
  int P, T;
  bool Pstep;
};

// [P][T][Pstep]
vector<State> adj_rev[100][100][2];

bool winning[100][100][2];
bool losing[100][100][2];
bool visited[100][100][2];
int degree[100][100][2];

const int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};

void dfs(State v) {
  visited[v.P][v.T][v.Pstep] = true;
  for (State u : adj_rev[v.P][v.T][v.Pstep]) {
    if (!visited[u.P][u.T][u.Pstep]) {
      if (losing[v.P][v.T][v.Pstep])
        winning[u.P][u.T][u.Pstep] = true;
      else if (--degree[u.P][u.T][u.Pstep] == 0)
        losing[u.P][u.T][u.Pstep] = true;
      else
        continue;
      dfs(u);
    }
  }
}

int main() {
  rd(n >> m);
  vstr A(n);
  readall(A);

  fo(P,n*m) {
    fo (T,n*m) {
      fo(Pstep,2) {
        int Px = P/m, Py = P%m, Tx = T/m, Ty = T%m;
        if (A[Px][Py]=='*' || A[Tx][Ty]=='*')
          continue;

        bool& win = winning[P][T][Pstep];
        bool& lose = losing[P][T][Pstep];
        if (Pstep) {
          win = Px==Tx && Py==Ty;
          lose = !win && A[Tx][Ty] == 'E';
        } else {
          lose = Px==Tx && Py==Ty;
          win = !lose && A[Tx][Ty] == 'E';
        }
        if (win || lose)
          continue;

        State st = {P,T,!Pstep};
        adj_rev[P][T][Pstep].push_back(st);
        st.Pstep = Pstep;
        degree[P][T][Pstep]++;

        fo(d, (Pstep ? 8 : 4)) {
          int PPx = Px, PPy = Py, TTx = Tx, TTy = Ty;
          if (Pstep) {
            PPx += dx[d];
            PPy += dy[d];
          } else {
            TTx += dx[d];
            TTy += dy[d];
          }

          if (PPx >= 0 && PPx < n && PPy >= 0 && PPy < m && a[PPx][PPy] != '*' &&
            TTx >= 0 && TTx < n && TTy >= 0 && TTy < m && a[TTx][TTy] != '*')
          {
            adj_rev[PPx*m+PPy][TTx*m+TTy][!Pstep].push_back(st);
            ++degree[P][T][Pstep];
          }
        }
      }
    }
  }

  fo(P,n*m)
    fo (T,n*m)
      fo(Pstep,2)
        if ((winning[P][T][Pstep] || losing[P][T][Pstep]) && !visited[P][T][Pstep])
          dfs({P, T, (bool)Pstep});

  int P_st, T_st;
  fo(i,n)
    fo(j,m)
      if (a[i][j] == 'P')
        P_st = i*m+j;
      else if (a[i][j] == 'T')
        T_st = i*m+j;

  if (winning[P_st][T_st][true])
    put("Police catches the thief");
  else if (losing[P_st][T_st][true])
    put("The thief escapes");
  else
    put("Draw");
  }
}