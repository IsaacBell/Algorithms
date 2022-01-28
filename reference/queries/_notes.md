# Binary Search on Segment Tree

Binary searching on segtree in general can be done without requiring the operation to be invertible.

When we query/update an interval [l, r) on the segment tree, the data structure split the interval into O(log N) non-overlapping precalculated subintervals [l_0 = l, r_0), [l_1 = r_0, r1), ..., [l_(k-1), r_(k-1) = r), which is the reason it takes O(log N) for those operations.

So if you wanna binary search from a point p, just split the range [p, N) into O(log N) subintervals the same way. One of those subintervals [s, t) must contain the desired answer. Find it by simply iterating over. Then just do prefix binary search on [s, t) in the usual way you do it in the case where p = 0.

