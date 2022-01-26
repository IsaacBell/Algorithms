# Kth order statistic in O(n)

Given an array A of size N and a number K. The challenge is to find K-th largest number in the array, i.e., K-th order statistic.

The basic idea - to use the idea of quick sort algorithm.

This is implemented in the C++ standard.

template <class T> nth_element(std::vector<T> a, unsigned n, unsigned k)
