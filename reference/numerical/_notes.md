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


