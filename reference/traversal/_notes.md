# Kth order statistic in O(n)

Given an array A of size N and a number K. The challenge is to find K-th largest number in the array, i.e., K-th order statistic.

The basic idea - to use the idea of quick sort algorithm.

This is implemented in the C++ standard.

template <class T> nth_element(std::vector<T> a, unsigned n, unsigned k)

# Kadane's in 2D

Iterate over all possible values of l1 and r1, and calculate the sums from l1 to l2 in each row of the matrix. Now we have the one-dimensional problem of finding the indices l2 and r2 in this array, which can already be solved in linear time.

# Binary Search

3 main templates:

Template 1 (standard):
  Initial Condition: left = 0, right = length-1
  Termination: left > right
  Searching Left: right = mid-1
  Searching Right: left = mid+1

  No post-processing

Template 2 (comparisons w/ right neighbor):
  Initial Condition: left = 0, right = length
  Termination: left == right
  Searching Left: right = mid
  Searching Right: left = mid+1

  Post-processing required. Loop/Recursion ends when you have 1 element left. Need to assess if the remaining element meets the condition.

Template 3 (comparisons w/ left & right neighbor):
  Initial Condition: left = 0, right = length-1
  Termination: left + 1 == right
  Searching Left: right = mid
  Searching Right: left = mid

  Use element's neighbors to determine if condition is met and decide whether to go left or right.

  Post-processing needed on final left, mid, and right vals. Check if they meet the needed condition.

