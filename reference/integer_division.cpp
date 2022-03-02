/*
  To calculate ⌈𝑥/𝑦⌉ in integers, you should divide 𝑥+𝑦−1 by 𝑦 using 
  integer division 
  
  (this will work provided that both 𝑥 and 𝑦 are non-negative, 
  and 𝑦≠0). 
  
  If you use real numbers, this may cause precision issues.
*/
ll int_div(ll x, ll y) {
  if (!x) return 0;
  return (x + y-1) / 2;
}

/*
  Division w/ Remainder
*/

ll div_rem(ll x, ll y) {
  ll diff = abs(x-y);
  if (!diff) return 0;
  ll rem = x % diff;
  ckmin(rem, diff - rem);
}
