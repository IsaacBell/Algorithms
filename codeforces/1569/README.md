# Problems

## A. Balanced Substring

### String, Impl.

> You are given a string 𝑠, consisting of 𝑛 letters, each letter is either 'a' or 'b'. The letters in the string are numbered from 1 to 𝑛.
> 𝑠[𝑙;𝑟] is a continuous substring of letters from index 𝑙 to 𝑟 of the string inclusive.
> A string is called balanced if the number of letters 'a' in it is equal to the number of letters 'b'. For example, strings "baba" and "aabbab" are balanced and strings "aaab" and "b" are not.
> Find any non-empty balanced substring 𝑠[𝑙;𝑟] of string 𝑠. Print its 𝑙 and 𝑟 (1≤𝑙≤𝑟≤𝑛). If there is no such substring, then print −1 −1.

Failed on 2nd test case.

Attempted to use a dynamic sliding window to traverse the string greedily. dsddIn hindsight, this over-complicated the problem and led to missed edge cases.

A better solution would have been a fixed sliding window w/ size of 2. Finding any pair "a" and "b" would have sufficed.

## B. Chess Tournament

> A chess tournament will be held soon, where 𝑛 chess players will take part. Every participant will play one game against every other participant. 
Each game ends in either a win for one player and a loss for another player, or a draw for both players.
Each of the players has their own expectations about the tournament, they can be one of two types:
> > a player wants not to lose any game (i. e. finish the tournament with zero losses);
> > a player wants to win at least one game.
> You have to determine if there exists an outcome for all the matches such that all the players meet their expectations. If there are several possible outcomes, print any of them. If there are none, report that it's impossible.

Failed.

Didn't come up with a sufficient approach.

## C. Jury Meeting

### Combinatorics

> 𝑛 people gathered to hold a jury meeting of the upcoming competition, the 𝑖-th member of the jury came up with 𝑎𝑖 tasks, which they want to share with each other.
First, the jury decides on the order which they will follow while describing the tasks. Let that be a permutation 𝑝 of numbers from 1 to 𝑛 (an array of size 𝑛 where each integer from 1 to 𝑛 occurs exactly once).
Then the discussion goes as follows:
> > If a jury member 𝑝1 has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
> > If a jury member 𝑝2 has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
> > ...
> > If a jury member 𝑝𝑛 has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
> > If there are still members with tasks left, then the process repeats from the start. Otherwise, the discussion ends.
> > A permutation 𝑝 is nice if none of the jury members tell two or more of their own tasks in a row.
> Count the number of nice permutations. The answer may be really large, so print it modulo 998,244,353.

Attempted to derive a permutation formula.

Got the implementation details correct, but processed the wrong formula in code.

