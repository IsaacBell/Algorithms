The Longest Common Prefix (LCP) algorithm involves comparing multiple strings and finding the longest common prefix shared by all of them. The implementation typically uses a trie data structure to store prefixes of the input strings, which is then traversed in order to find the LCP. In addition, it is possible to use sorting and binary search to find the LCP.

The most optimal way to implement is to use a Trie data structure or a binary search tree, as they both allow for efficient searches. The easiest way to write the code is to use a set to store all prefixes of each inverse, and then iterate over the length of the prefix.

Inverse of a permutation is a rearrangement of the elements such that the result is the identity permutation. The most optimal way to find the longest common prefix of two permutations is to sort the inverses of all the permutations, then use binary search to find the longest common prefix. The easiest approach is to store the inverses in a trie and traverse it with the given permutation until a dead end is reached.

### Problems

https://codeforces.com/contest/1792/problem/D

