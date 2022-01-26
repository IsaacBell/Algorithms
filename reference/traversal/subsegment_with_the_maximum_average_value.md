/*
  Finding a subsegment with the maximum average value
  http://e-maxx.ru/forum/viewtopic.php?id=410
*/

In linear time it is possible with a stack. Namely, we calculate partial sums of two types. Let L be the minimum length of the segment of interest to us. Then S1(i) = a(0) + ... + a(i) and S2(i) = a(0) + ... + a(i - L). Note, then, that for a segment ending at i and j (i >= j), the arithmetic mean will be X = (S1(i) - S2(j + L - 1)) / (i - j + 1) . Let's make the change t = j + L - 1, then we get: X = (S1(i) - S2(t)) / (i - t + L). We need to maximize X. Now we no longer have a limit on the minimum length of the segment, but we no longer consider the arithmetic mean.

Multiplying both parts by the denominator, we have: S1(i) - X * (i + L) = S2(t) - X * t (*).

On the left and on the right are the equations of lines, where X is an independent variable. For a fixed i, we need to find a t such that the intersection point resp. line lies as far to the right as possible. It can be seen that both slope coefficients are negative, and for the straight line on the left side it is strictly smaller than for the straight line on the right side. 

This means that if we store the lower envelope of the set of lines on the left side (lower envelope), then the optimal intersection point will be reached when the line S1(i) - X * (i + L) intersects with one of the lines belonging to this set. 

By maintaining all the lines on the stack, it is possible in O(H) to calculate this point of intersection for each of the lines. It suffices to know that the problem of finding the lower envelope of a set of lines of the form y = kx + l is equivalent to finding the lower chain of the convex hull of points of the form (k, l).


This method is also generalized for the following problem: given an array of N numbers, as well as the number L. Requests are received like: "Given a segment of numbers from this array, you need to give online a subsegment of this segment, of length at least L, with the maximum arithmetic mean" . To generalize the algorithm, several observations need to be made:

1. As mentioned above, if we fix the right end of the segment and remember the lower envelope of the set of all lines from the right side of the equality (*), corresponding to the numbers that lie to the left of the right end, then to find the optimal segment with this right end, it is enough to intersect resp. the straight line from the left side of the equality (*) with this lower envelope set.
2. Similarly, for the case when the left end of the segment is fixed and there is an upper envelope of the set of all lines from the left side of the equality (*), resp. numbers to the right of this end.
3. If the segment is divided into 2 parts, for the left one find the lower envelope of the set of lines from the right side (*), and for the right ones - the upper envelope of the set of lines from the left side (*), and also assume that the right end lies in the right half, and the left one is in the left one, then the optimal ends can be found if these 2 sets of lines are intersected. The intersecting lines will correspond to the ends of the optimal segment. It can be shown that the intersection point will always be the same.

It is possible to traverse such sets in O(log^2(N)) by doing 2 nested binary searches: one by x and the second by number resp. segment or ray in each of the sets.

Let's return to the original problem. Before starting to answer queries, let's build 2 segment trees: one will store lines from the left side of the equality (*), the second - from the right. Both of them will take O(NlogN) memory. It will take the same amount of time to build. For each vertex of these DOs, we find the optimal segment lying in them.

When answering the query, we will divide the segment given to us into O(logN) subsegments, which correspond to the vertices in the segment trees. First, let's find the best subsegment that lies entirely inside one of these segments. Then, you can intersect all pairs of segments from different trees using the method described above, and compare the answer with the one already found.

The last step takes O(log^4(N)) time. But if, instead of crossing all pairs, we fix one subsegment, and then sequentially go from it to the right and merge the entire envelope of the set into one (it is possible implicitly), then the total will be O(log^3(N)) time.

The algorithm turned out to be rather complicated. I gave almost the same task for the summer training camp in Petrozavodsk 2011, so if something is not clear, you can look there in the analysis.