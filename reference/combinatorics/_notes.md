# Selections

### Order significant, repetition allowed: 
We get to make k choices, and there are n names to choose at each step. So there are n^k possibilities.

### Order significant, repetition not allowed: 
This time, there are n names to choose at the first step; n − 1 at the second step (since we discarded the first name after we chose it); n−2 at the third step; . . . and n−k +1 at the k-th step.
Multiplying these numbers gives the answer.

### Order not significant, repetition not allowed: 
We simply choose a set with k elements from the n elements in the hat. The number of ways of doing this is nCk, by definition. Alternatively choose with order significant, and repetition allowed, and note that each unordered sample has k! different orderings; so the answer is (n)k/k!.