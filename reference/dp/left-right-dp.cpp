/*
  https://codeforces.com/problemset/problem/1547/E

  Let's calculate two arrays 𝐿 and 𝑅, where:

  𝐿𝑖 is the temperature in cell 𝑖 if we take only air conditioners with numbers less than or equal to 𝑖;
  
  𝑅𝑖 is the temperature in cell 𝑖 if we take only air conditioners with numbers greater than or equal to 𝑖;
  
  Let's show how to calculate array 𝐿. We will calculate values from left to right using DP and next 
  formula: 𝐿𝑖=min(𝐿𝑖+1+1,𝑐𝑖), where 𝑐𝑖 is the temperature of air conditioner in cell 𝑖 
  (or infinity if there is no air conditioner in this cell). 
  
  Indeed, the value of 𝐿𝑖 is either determined by the air conditioner in this cell (i.e. equals 𝑐𝑖) 
  or by some air conditioner to the left, but this means that we should take the answer from the 
  previous cell and increase it by 1.
*/

bitset<N+1> vis;

ll a, b, c, n, m, k, w;
string s, t;

void solution() {
  const ll mod2 = 1e18;
  vis.reset();
  rd(n >> k);
  vl A(k), B(k), o(n); 
  readall(A); readall(B);

  vl L(n, mod2), R(n, mod2), wt(n, mod2);
  fo(i,k) wt[--A[i]] = B[i];

  ll prev = mod2;
  // min(𝑡𝑗+|𝑎𝑗−𝑖|), 1≤𝑗≤𝑘
  fo(i,n)   L[i] = prev = min(prev + 1, wt[i]);
  ford(i,n) R[i] = prev = min(prev + 1, wt[i]);

  fo(i,n) print( min(L[i], R[i]) ); cnl;
}
