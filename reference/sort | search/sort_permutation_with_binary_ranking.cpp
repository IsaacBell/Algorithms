/*

Find permutation where every higher-ranked record has a
greater value than lower-ranked records.

Rankings are given in the form of a string made of "1"s and "0"s.

Minimize the value of ∑𝑖=1,𝑛 abs(𝑝𝑖−𝑞𝑖) in the output permutation.

Inputs:
n
A[]
s -> 1 for higher rank, 0 for lower rank
     e.g. "liked" and "disliked" records

*/
void solution() {
  rd(n);
  vtll p(n);
  vl A(n); readall(A);
  rd(s); szn(m,s);
  
  fo(i,n) p[i] = {s[i], A[i], i};
  sortall(p);
  
  vl o(n);
  fo(i,n) 
    o[ get<2>(p[i]) ] = i + 1;
  puts(o);
  cnl;
}