# Key Notes

  

- RECALL finding MEX w/ binary search
- LEARN how to represent carry operations programmatically.
- TODO write a SegTree template
  

# Problems

## A - Domino Disaster

### Strings, Implementation

  > Alice has a grid with  22  rows and  𝑛n  columns. She fully covers the grid using  𝑛n  dominoes of size  1×21×2 — Alice may place them vertically or horizontally, and each cell should be covered by exactly one domino.
Now, she decided to show one row of the grid to Bob. Help Bob and figure out what the other row of the grid looks like!

Solved successfully.

  

## B - MEXor Mixup

### Greedy, Math (XOR)

  

> Alice gave Bob two integers 𝑎 and 𝑏 (𝑎>0 and 𝑏≥0). Being a curious boy, Bob wrote down an array of non-negative integers with MEX value of all elements equal to 𝑎 and XOR value of all elements equal to 𝑏.

> What is the shortest possible length of the array Bob wrote?

> Recall that the MEX (Minimum EXcluded) of an array is the minimum non-negative integer that does not belong to the array and the XOR of an array is the bitwise XOR of all the elements of the array.

  

Attempted. Failed to determine the cases needed to obtain next needed array value.

  

> First consider the MEX condition: 
> the shortest array with MEX 𝑎 is the array [0,1,…,𝑎−1], which has length 𝑎. 
> Now we'll consider the XOR condition. 
> Let the XOR of the array [0,1,…,𝑎−1] be 𝑥. 
> We have three cases.
> -
> Case 1: 𝑥=𝑏. Then we don't need to add any elements to the array, so the answer is 𝑎.
Case 2: 𝑥≠𝑏 and 𝑥⊕𝑏≠𝑎. Then we can add the element 𝑥⊕𝑏 to the array since 𝑥⊕𝑏≠𝑎, so the MEX will still be 𝑎. The XOR of the array will then be 𝑥⊕𝑥⊕𝑏=𝑏. The answer is 𝑎+1.
Case 3: 𝑥≠𝑏 and 𝑥⊕𝑏=𝑎. Then we cannot add the element 𝑥⊕𝑏 to the end of the array. We can just add 𝑥⊕𝑏⊕1 and 1, so the XOR of the array will be 𝑥⊕𝑥⊕𝑏⊕1⊕1=𝑏. The answer is 𝑎+2.
Time complexity: (𝑛) precomputation and (1) per test case if you precalculate the XOR of the numbers from 0 to 𝑛−1, or (1) if you use the well-known formula for it.

## C. Carrying Conundrum

### DP, Combinatorics, Bitmasks

> Alice has just learned addition. However, she hasn't learned the concept of "carrying" fully — instead of carrying to the next column, she carries to the column two columns to the left.
For example, the regular way to evaluate the sum 2039+2976 would be as shown:
* add 9 and 6 to make 15, and carry the 1 to the column two columns to the left, i. e. to the column "0 9";
* add 3 and 7 to make 10 and carry the 1 to the column two columns to the left, i. e. to the column "2 2";
* add 1, 0, and 9 to make 10 and carry the 1 to the column two columns to the left, i. e. to the column above the plus sign;
* add 1, 2 and 2 to make 5;
* add 1 to make 1.
Thus, she ends up with the incorrect result of 15005.
Alice comes up to Bob and says that she has added two numbers to get a result of 𝑛. 
However, Bob knows that Alice adds in her own way. Help Bob find the number of ordered pairs of positive integers such that when Alice adds them, she will get a result of 𝑛. 
Note that pairs (𝑎,𝑏) and (𝑏,𝑎) are considered different if 𝑎≠𝑏.

Failed to solve.

## D. Expression Evaluation Error

### Greedy, Math

> On the board, Bob wrote 𝑛 positive integers in base 10 with sum 𝑠 (i. e. in decimal numeral system). 
Alice sees the board, but accidentally interprets the numbers on the board as base-11 integers and adds them up (in base 11).
What numbers should Bob write on the board, so Alice's sum is as large as possible?

Failed.

Need to learn how to represent carry operations programmatically.

## E. Non-Decreasing Dilemma

### Segment Tree

> Alice has recently received an array 𝑎1,𝑎2,…,𝑎𝑛 for her birthday! She is very proud of her array, and when she showed her friend Bob the array, he was very happy with her present too!
However, soon Bob became curious, and as any sane friend would do, asked Alice to perform 𝑞 operations of two types on her array:
-

> 1 𝑥 𝑦: update the element 𝑎𝑥 to 𝑦 (set 𝑎𝑥=𝑦).
2 𝑙 𝑟: calculate how many non-decreasing subarrays exist within the subarray [𝑎𝑙,𝑎𝑙+1,…,𝑎𝑟]. More formally, count the number of pairs of integers (𝑝,𝑞) such that 𝑙≤𝑝≤𝑞≤𝑟 and 𝑎𝑝≤𝑎𝑝+1≤⋯≤𝑎𝑞−1≤𝑎𝑞.
Help Alice answer Bob's queries!

Failed to calculate non-decreasing subarrays correctly during tree construction.

Need to write a SegTree template to save time on similar problems.

## F. One-Four Overload

### Grid, Graph, DSU

> Alice has an empty grid with 𝑛 rows and 𝑚 columns. Some of the cells are marked, and no marked cells are adjacent to the edge of the grid. (Two squares are adjacent if they share a side)
Alice wants to fill each cell with a number such that the following statements are true:

> - every unmarked cell contains either the number 1 or 4;
- every marked cell contains the sum of the numbers in all unmarked cells adjacent to it (if a marked cell is not adjacent to any unmarked cell, this sum is 0);
- every marked cell contains a multiple of 5.
Alice couldn't figure it out, so she asks Bob to help her. Help Bob find any such grid, or state that no such grid exists.

Didn't attempt.