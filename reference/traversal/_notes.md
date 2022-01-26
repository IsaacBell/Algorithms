# Kth order statistic in O(n)

Given an array A of size N and a number K. The challenge is to find K-th largest number in the array, i.e., K-th order statistic.

The basic idea - to use the idea of quick sort algorithm.

This is implemented in the C++ standard.

template <class T> nth_element(std::vector<T> a, unsigned n, unsigned k)

# Kadane's in 2D

Iterate over all possible values of l1 and r1, and calculate the sums from l1 to l2 in each row of the matrix. Now we have the one-dimensional problem of finding the indices l2 and r2 in this array, which can already be solved in linear time.
