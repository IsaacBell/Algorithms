# MEX of an array

## Quick Mex for small array vals (A[i] < 1e6)

Just use a set.

```
ll mex(vl& V) {
  set<ll> st; //(all(V));
  fo(i, V.sz()) st.insert(V[i]);

  fo(i, 1000001)
    if(!st.count(i))
      return i;

  // ret -1;
}
``

Optionally, use coordinate compression.

## Sorting approach in O(N log(N)) time

```
sortall(A);
int mex = 1;
trav(e, A) {
	if (e == mex) {
		mex++;
	}
}
```

## More sophisticated approach

1. Go through the array and remove elements from it that are greater than N
2. Use sorting for O (N) + unique O(N)
3. Traverse the seq and look at the first one that does not correspond to the number in the array

Example: n = 9, 0 3 5 7 2 4 1 10 19

delete (>= n) 0 3 5 7 2 4 1

sorting 0 1 2 3 4 5 7

analysis of 0-index

0 in 0 position, 1 in 1 position ... 5 in 5 position, 7 in 6 position

then the answer is 6

# Mex Queries

## Frequency Map Approach

O(N log(N)) precomp time

Each query takes O(1) time

Updates take (log(N)) time

In C++ :-
Precomputation:
- Create a set and a frequency map(or array).
- Fill the set with all numbers from 0 to n+1.
- Now, traverse in the array, if the element is within [0, n+1] remove it from the set, and keep updating the frequency map(or array). It takes at worst O(NlogN) time.
- Now, for any state, the set.begin() will give the MEX of the current array.
For updates:
- If the element to be replaced, is within [0, n+1] then update its frequency in the frequency map(or array) and if after updating, the frequency of that element becomes zero, insert it into our set. It takes O(logN) time.
- Now if the element which is placed in that position is within [0, n+1] then update its frequency in the frequency map(or array) and remove it from our set(if its present). It takes O(logN) time.
- And yet again, after any update, set.begin() will give us the current MEX in O(1).

(todo - adapt into a template)
```
ll n;
cin >> n;
vl a(n);
ain(a, n);
bool sorted = 1;
set<ll> mex;
loop(i, n + 1)	mex.insert(i);
map<ll, ll> f;
loop(i, n)	++f[a[i]];
loop(i, n)
{
  if (mex.find(a[i]) != mex.end())
    mex.erase(a[i]);
}
ll currmex = *(mex.begin()), iter = 0;
vl ans;
loop(i, n - 1)
{
  if (a[i] > a[i + 1])
  {
    sorted = 0;
    break;
  }
}
// cout << "Sorted : " << sorted << END;
while (iter < 2 * n && sorted == false)
{
  // cout << currmex << END;
  if (currmex == n)
  {
    loop(i, n)
    {
      if (a[i] != i)
      {
        ans.pb(i);
        --f[a[i]];
        if (f[a[i]] == 0)
          mex.insert(a[i]);
        a[i] = currmex;
        ++f[currmex];
        mex.erase(currmex);
        break;
      }
    }
  }
  else
  {
    ans.pb(currmex);
    --f[a[currmex]];
    if (f[a[currmex]] == 0)
      mex.insert(a[currmex]);
    a[currmex] = currmex;
    ++f[currmex];
    mex.erase(currmex);
  }
  currmex = *(mex.begin());
  bool ok = 1;
  loop(i, n - 1)
  {
    if (a[i] > a[i + 1])
    {
      ok = 0;
      break;
    }
  }
  sorted = ok;
  ++iter;
}
// cout << "Sorted : " << sorted << END;
cout << ll(ans.size()) << END;
go(ans, itr)	cout << *itr + 1 << " ";
cout << END;
```