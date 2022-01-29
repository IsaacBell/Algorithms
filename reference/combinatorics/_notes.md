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
