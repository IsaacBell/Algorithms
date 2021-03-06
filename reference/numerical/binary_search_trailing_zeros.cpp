#undef F
template <class F = ll>
F trailing_zeros(F x)
{
	F cnt=0;
	while(x)
	{
		cnt += x / 5;
		x /= 5;
	}
	return cnt;
}

template <class F = ll>
F bsearch_trailing_zeros(F n_, F maxn)
{
	 F left = 0;
   F right = maxn;
	 F mid = -1, ans = 0;
	 while (left <= right)
	 {
	 	 mid = left + (right-left) / 2;
	 	 if(trailing_zeros(mid) >= n_)
	 	 {
	 	 	right = mid-1;
	 	 	//ans = mid;
	 	 }
	 	 	  
	 	 else
	 	 	left = mid+1;
	 }
	 return left;
}
#define F first