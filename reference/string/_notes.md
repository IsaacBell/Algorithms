# Aho-corasick Visualization
http://jovilab.sinaapp.com/visualization/algorithms/strings/aho-corasick

# KMP Visualization
http://jovilab.sinaapp.com/visualization/algorithms/strings/kmp

# Manacher's Algorithm

Longest Palindromic Substring in O(n)

# Suffix Trees

- ST: orgs all suffixes of a str together
- STs can be used to find Longest Common Substring in O(N)
  - DFS & STs to find biggest common subtree
  - Bottom-up DFS

# Ziv-Level Data Compression

- Prior[i] = longest prefix of S that's also a substr of S[0..i-1]
  - Ex: S = "abaxcabaxabz", Prior[7] = "bax"
    - "bax" is a substring of S[0..6]
- For pos i in S, Li = Prior[i].length
  - For Li > 0, Si = start pos of leftmost copy of Prior[i]
    - Ex: If S = "abaxcabaxabz", L7 = 3 and S7 = 2
- Useful in DNA Sequencing, bcs there's lots of repetition
- Implementation
  - Using Suffix Trees
    1. Build a Suffix Tree T for str S
    2. For each node v, find smallest idx of any leaf in v's subtree. Meaning, leftmost starting pos c(v), in the substr labelling the path from root to v
    3. To get (Si, Li), traverse the uniq path in T that matches a prefix of S[i..m], until at pt where no more matches are possible. Or, the string-depth of pt p + c(v) == i, where v is 1st node at or below p

# Ukkonen's

- Linear-time suffix tree
- Manages 4 vars
  - Active Point:
    - Node (#), Edge (char), Length(#)
  - Remainder
    - amount of repeated chars added implicitly
      - ++ for each matched, repeated char
      - -- for each split and internal node added
      - Move on to extend next char when remainder = 0
  - Split/Add Node
    - While (Rem > 0)
      - Split Active Edge
      - If active node is root, -- active length
      - Else
        - Follow suffix link to a new active node
        - If no suffix link, set active node to root
- Suffix Links
  - If split edge, or if internal node inserted is not the 1st node created in current step
    - Connect previously inserted node and new node w/ suffix link
  - Enable reset active point

# Longest Common Substring
  - Plagiarism Detection
  - Linear time w/ 2 Generalized Suffix Trees
    - Each leaf is a suffix from 1 or both strings
    - Mark nodes w/ 1 or 2 if there's a leaf in its subtree representing a suffix from S1 to S2
    - Longest path-label of any interval node marked both 1 and 2 is the longest common substring


