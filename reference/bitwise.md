# TOC

* [Formulas](#Formulas)
* [Essentials](#Essentials)
* [Hacks](#Hacks)
  * Compute modulus division by 1 << s without a division operator
  * Compute modulus division by (1 << s) - 1 without a division operator
  * Interleave bits (Morton #s)
  * Round up to the next highest power of 2
* [Problems](#Problems)

# Formulas

Properties:
a|b = a⊕b + a&b
a⊕(a&b) = (a|b)⊕b
b⊕(a&b) = (a|b)⊕a
(a&b)⊕(a|b) = a⊕b

Addition:
a+b = a|b + a&b
a+b = a⊕b + 2(a&b)

Subtraction:
a-b = (a⊕(a&b))-((a|b)⊕a)
a-b = ((a|b)⊕b)-((a|b)⊕a)
a-b = (a⊕(a&b))-(b⊕(a&b))
a-b = ((a|b)⊕b)-(b⊕(a&b))

# Essentials

## Beginner
x = (1 << y) ^ x — toggle a bit.

x = (1 << y) | x — addding a bit.

x = ~(1 << y) & x — removing a bit.

if (1 << y & x) — check whether y-th bit is set.

## Intermediate
-x = ~x + 1 — negative 𝑥 in two's complement representation.

x & (-x) — least significant bit, LSB

if (x && !((x-1) & x) — check whether x is a power of two

## Complex

### Bit swap
p = ((x >> a) ^ (x >> b)) & 1
x ^= (p << a)
x ^= (p << b)

### Number of set bits
aka population count. x = x & (x-1) removes least significant bit, Brian Kernighan method.

for (c = 0; x; c++)
    x = x & (x-1)

### Swapping values
b ^= a ^= b;
a ^= b;

### All submasks of mask
Excluding blank mask. Also, enumerating all masks and their submasks is O(3n)

for (int s = m; s; s = (s-1)&m)
	//do something

### Bit scan forward
BSF, null indexed position of LSB. 𝑥 should not be zero.

x = x & (-x);
int pos = 0;
if (x & 0xffff0000) pos += 16;
if (x & 0xff00ff00) pos += 8;
if (x & 0xf0f0f0f0) pos += 4;
if (x & 0xcccccccc) pos += 2;
if (x & 0xaaaaaaaa) pos += 1;

### Next permutation
Rearranges bit set of number into the lexicographically next greater permutation.

t = x | (x - 1);
x = (t + 1) | (((~t & -~t) - 1) >> (BSF(v) + 1));

# Hacks

### Compute modulus division by 1 << s without a division operator
```
const unsigned int n;          // numerator
const unsigned int s;
const unsigned int d = 1U << s; // So d will be one of: 1, 2, 4, 8, 16, 32, ...
unsigned int m;                // m will be n % d
m = n & (d - 1);
```

### Compute modulus division by (1 << s) - 1 without a division operator
```
unsigned int n;                      // numerator
const unsigned int s;                // s > 0
const unsigned int d = (1 << s) - 1; // so d is either 1, 3, 7, 15, 31, ...).
unsigned int m;                      // n % d goes here.

for (m = n; n > d; n = m)
{
  for (m = 0; n; n >>= s)
  {
    m += n & d;
  }
}
// Now m is a value from 0 to d, but since with modulus division
// we want m to be 0 when it is d.
m = m == d ? 0 : m;
```

### Interleave bits (Morton #s)
```
unsigned short x;   // Interleave bits of x and y, so that all of the
unsigned short y;   // bits of x are in the even positions and y in the odd;
unsigned int z = 0; // z gets the resulting Morton Number.

for (int i = 0; i < sizeof(x) * CHAR_BIT; i++) // unroll for more speed...
{
  z |= (x & 1U << i) << i | (y & 1U << i) << (i + 1);
}
Interleaved bits (aka Morton numbers) are useful for linearizing 2D integer coordinates, so x and y are combined into a single number that can be compared easily and has the property that a number is usually close to another if their x and y values are close.
```

### Round up to the next highest power of 2
```
unsigned int v; // compute the next highest power of 2 of 32-bit v

v--;
v |= v >> 1;
v |= v >> 2;
v |= v >> 4;
v |= v >> 8;
v |= v >> 16;
v++;
```

### Count the consecutive zero bits (trailing) on the right linearly
```
unsigned int v;  // input to count trailing zero bits
int c;  // output: c will count v's trailing zero bits,
        // so if v is 1101000 (base 2), then c will be 3
if (v)
{
  v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
  for (c = 0; v; c++)
  {
    v >>= 1;
  }
}
else
{
  c = CHAR_BIT * sizeof(v);
}
The average number of trailing zero bits in a (uniformly distributed) random binary number is one, so this O(trailing zeros) solution isn't that bad compared to the faster methods below.
```

### Count the consecutive zero bits (trailing) on the right by binary search
```
unsigned int v;     // 32-bit word input to count zero bits on right
unsigned int c;     // c will be the number of zero bits on the right,
                    // so if v is 1101000 (base 2), then c will be 3
// NOTE: if 0 == v, then c = 31.
if (v & 0x1) 
{
  // special case for odd v (assumed to happen half of the time)
  c = 0;
}
else
{
  c = 1;
  if ((v & 0xffff) == 0) 
  {  
    v >>= 16;  
    c += 16;
  }
  if ((v & 0xff) == 0) 
  {  
    v >>= 8;  
    c += 8;
  }
  if ((v & 0xf) == 0) 
  {  
    v >>= 4;
    c += 4;
  }
  if ((v & 0x3) == 0) 
  {  
    v >>= 2;
    c += 2;
  }
  c -= v & 0x1;
}
```

The code above is similar to the previous method, but it computes the number of trailing zeros by accumulating c in a manner akin to binary search. In the first step, it checks if the bottom 16 bits of v are zeros, and if so, shifts v right 16 bits and adds 16 to c, which reduces the number of bits in v to consider by half. Each of the subsequent conditional steps likewise halves the number of bits until there is only 1.

### Count the consecutive zero bits (trailing) on the right with multiply and lookup
```
unsigned int v;  // find the number of trailing zeros in 32-bit v 
int r;           // result goes here
static const int MultiplyDeBruijnBitPosition[32] = 
{
  0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
  31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};
r = MultiplyDeBruijnBitPosition[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
```

Converting bit vectors to indices of set bits is an example use for this. It requires one more operation than the earlier one involving modulus division, but the multiply may be faster. The expression (v & -v) extracts the least significant 1 bit from v. 

The constant 0x077CB531UL is a de Bruijn sequence, which produces a unique pattern of bits into the high 5 bits for each possible bit position that it is multiplied against. 

When there are no bits set, it returns 0. More information can be found by reading the paper [Using de Bruijn Sequences to Index 1 in a Computer Word](http://citeseer.ist.psu.edu/leiserson98using.html) by Charles E. Leiserson, Harald Prokof, and Keith H. Randall.

Because this is casted to a 32-bit uint, it can work with 64-bit ints.

# Problems

## Min XOR Sum of 2 Arrays

The XOR sum of the two integer arrays is (nums1[0] XOR nums2[0]) + (nums1[1] XOR nums2[1]) + ... + (nums1[n — 1] XOR nums2[n — 1]) (0-indexed).

For example, the XOR sum of [1,2,3] and [3,2,1] is equal to (1 XOR 3) + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4. Rearrange the elements of nums2 such that the resulting XOR sum is minimized.

```
int dp[14][1<<14];

int solve(int i, int mask, int &n_, vi &A, vi &B) {
  if (i == n_)
    return 0;

  if (dp[i][mask] != -1)
    return dp[i][mask];

  int answer = INT_MAX;
  fo(j,n)
    if (mask & (1 << j))
      ckmin(answer, (a[i] ^ b[j]) + solve(i + 1, (mask ^ (1 << j)), n, a, b));

  return dp[i][mask] = answer;
}

int minimumXORSum(vi &A, vi &B) {
  // fill(all(dp), -1);
  memset(dp, -1, sizeof dp);
  szn(n_, A);
  return solve(0, (1 << n_) - 1, n_, A, B);
}
```
