/*
   Check Palindrome

   Could the chars in string str form a palindrome?
*/
bool checkPal(const string str) {
  szn(sn, str);

  // 64-bit mask for <=64 letters
  ll mask = 0;

  // Map each char to an idx, flipping
  // from 1 to 0 back & forth
  trav(ch,str) mask ^= (1 << (ch - 'a'));

  // Is there more than 1 char w/ an odd # of occurences?
  return __builtin_popcount(mask) < 2;
}

/*
   Is Palindrome?

   Is string str a palindrome?
*/
bool isPal(const string str) {
  szn(sn,str);
  fo(i,(sn / 2))
    if (str[i] != str[sn-i-1]) return false;
  return true;
}

/*
   Palindrome Pairs

   (tested)
   
   You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").
*/
void solution() {
  rd(n);
  ll ans = 0;
  map<ll, ll> cnt; // Don't mix hashmaps with bitmaps!

  fo(i,n) {
    // 32-bit mask for 26 letters
    int mask = 0;
    rd(s);

    // Map each char to an idx, flipping
    // from 1 to 0 back & forth
    trav(ch,s) mask ^= (1 << (ch - 'a'));
    ans += cnt[mask];

    // Check if there's a match when we
    // use current letter as middle char
    fo(flip,26) {
      mask ^= (1 << flip);
      ans += cnt[mask];
      mask ^= (1 << flip);
    }

    cnt[mask]++;
  }
  
  put(ans);
}