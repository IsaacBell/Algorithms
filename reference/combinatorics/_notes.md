# Quick Examples

## Integral Solutions

Given N and K. The task is to count the number of the integral solutions of a linear equation having N variable as given below: 

x1 + x2+ x3…+ xN-1+…+xN = K
- ### non-negative integral solutions of eqn x1 + x2 + …… + xn = k 

Given by (n+k-1)! / (n-1)!*k!

- ### positive integral solutions of eqn x1 + x2 + ….. + xn = k

Given by (k-1)! / (n-1)! * (k-n)!

- # paths on a 2D grid (Dirs: U+R). Can't cross diagonal

= (n*m) C (n)

- # paths on a 2D grid (Dirs: U+R)

= (2n) C (n)

- # paths on a 3D grid (U+R+F)

= (n*m*p)!/(n!m!p!)

- # ways to distribute n candies to r ppl

= (n+r-1) C (r-1)

- # ways to distribute n candies to r ppl. Each prsn needs >= k candies

= (n - r*k + r-1) C (r-1)

- How many ways to arrange this set of letters: AAABBBBCCC
  (3 A's, 4 B's, 3 C's)

  = 10!/(3! * 4! * 3!)

- Permutation (nPr):
  N objs are present. We'll select any ordering of R objs. Order matters

  = n * (n-1) * (n-2) * ... * (n-r+1)
  = n!/(n-r)!

- Combination (nCr):
  N objs present, select any r objs. Order doesn't matter.

  = n!/((n-r)!*r!)

- nCr % m (where m is prime, and n,m <= 10^6)
  nCr % m = (n! % m) * inv((n-r)!) * inv(r!)

  Fermat's Theorem for finding inverse:
  inv(n % m) = n^(m-2) % m

  Total TC: O(log m)

- nCr % m (where m is prime, and n,r <= 10^12, m <= 10^5)
  Lucas Theorem: Write r and n in base m
                 n = n{k-1} * n{k-2} * ... n0

                 Recursively divide by m to get base m #.
                 Think of it like converting a # to binary. 

- Internal angles of regular polygons:
  - ∆: 60°
  - Square: 90°
  - Pentagon: 108°
  - Hexagon: 120°
  - Octagon: 135°
  - Decagon: 144°
  - Dodecagon: 150°

# Selections

### Order significant, repetition allowed: 
We get to make k choices, and there are n names to choose at each step. So there are n^k possibilities.

### Order significant, repetition not allowed: 
This time, there are n names to choose at the first step; n − 1 at the second step (since we discarded the first name after we chose it); n−2 at the third step; . . . and n−k +1 at the k-th step.
Multiplying these numbers gives the answer.

### Order not significant, repetition not allowed: 
We simply choose a set with k elements from the n elements in the hat. The number of ways of doing this is nCk, by definition. Alternatively choose with order significant, and repetition allowed, and note that each unordered sample has k! different orderings; so the answer is (n)k/k!.

# Ordered Selections

## W/ Repetition

n^x selections, where k = # items to pick

## Arrangements

n selections

## W/O Repetitions

n * (n-1) * (n-2) ... (n - k + 1)

AKA Permutation: P(n,k)

# Unordered Selections

- P(n,k) /k! = C(n,k) = n!/k!(n-k)!
- AKA combination: C(n,k)
- The product of any K consec positive ints divides k!
- C(n,k) = C(n-1,k) + C(n-1,k-1)
- 2^n = C(n,0) + C(n,1) + C(n,2) ... + C(n,n)
- Unordered Selections w/ Repetition: C(n+k-1, k)
- Box Principle: if > k*n objs placed in boxes, some box must get >1 obj
