# General

- Any even number greater than 2 can be split into two prime numbers (no proof, not proven wrong)
- 𝑔𝑐𝑑(𝐹𝑛,𝐹𝑚)=𝐹𝑔𝑐𝑑(𝑛,𝑚), where 𝐹𝑥 is the 𝑥𝑡ℎ fibonacci numbers and first two terms are  0,1

# Number of ways between two vertices

https://www.youtube.com/watch?v=Q4gTV4r0zRs

# Odd #s in Range

ll x = (r-l+1) - (r/2 - (l-1)/2);

# Triangular Numbers

Sum of 1,2,...,N

Ex: 6 = 1+2+3

Formula: Tn = (n*(n+1)) / 2

## Sum of Reciprocals

Sum always = 2.

Ex: 1/1 + 1/3 + 1/6 + ... + 1/Tn = 2

# Oblong Numbers

Positive int of form n(n+1)

* nth oblong is sum of 1st n even #s
* Sum of odd ints is n^2
* 1 + a + a^2 + a^3 + a^(n-1) = (a^n - 1) / (a - 1)

# Deficient, Abundant, & Perfect Numbers

* Deficient: sum of n's factors < n
* Abundant: sum of n's factors > n
* Perfect #s: sum of n's factors = n
  * 6, 28, 496, 8128

# Mersenne Primes

* Even perfect #s all have form 2^(n-1) * (2^n - 1)

# Amicable Numbers

* for two ints a and b, the sum of factors of a = b and vice-versa

# Alternative Prime Check Technique

* To check if a # n is prime, see if it divides any # <= sqrt(n)

# Sum of 2 Squares

* Product of 2 sums of sqr #s is also the product of 2 sqr #s
* xy = (ac - bd)^2 + (ad + bc)^2 if x = (a^2 + b^2) & y = (c^2 + d^2)

# Sums

* n^3 = Sum of n consecutive odd #s from n^2 - n + 1 to n^2 - n + 2n - 1
* Sum of n oblong #s = (n * (n+1) * (n+2)) / 3
* Sum of 1st n triangular #s = (n * (n+1) * (n+2)) / 6

# Linear Diophantine Equations

Have the form: ax + by = c, where a and b and c are known in advance.

An Integral solution is a solution such that all the unknown variables take only integer values. They will exist if and only if, the GCD of coefficients of the two variables divides the constant term perfectly. In other words the integral solution exists if, GCD(a ,b) divides c.

if (c % euclid(a,b) == 0) put("Yes") else put("NO");

If a or b is 0, then the problem only has one solution.

...

a * m + b * n = gcd(a, b) for some integer m and n, they can be negative or zero.

# Kth order statistic in O(n)

Given an array A of size N and a number K. The challenge is to find K-th largest number in the array, i.e., K-th order statistic.

The basic idea - to use the idea of quick sort algorithm.

This is implemented in the C++ standard.

template <class T> nth_element(std::vector<T> a, unsigned n, unsigned k)

# Represent the set of all positive fractions from 1 to n

The Stern-Brocot tree accomplishes this. It generates all positive fractions from 0 to INF.

Pseudocode:

```
void build(int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
    int x = a + c, y = b + d;

    ... output the current fraction x/y at the current level in the tree

    build(a, b, x, y, level + 1);
    build(x, y, c, d, level + 1);
}
```

todo - make a template for the Stern-Brocot tree