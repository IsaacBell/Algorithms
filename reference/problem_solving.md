# Ideas, Questions, Thoughts for when you're stuck

- Problems involving minimizing a maximum often involve binary search
- Is parity important?
  - + ops: parity is inverted if 2nd arg is odd
  - XOR ops: parity is inverted if 2nd arg is odd
  - Ex: x and y are starting points. x is odd and y is even. We are doing XOR operations, so any odd numbers that we perform an XOR against (e.g. x^3 and y^3) will change the parity of our number. So if we XOR against an odd # of odd numbers (Ex: n = 1, A[0] = 3, x ^= 3 and y ^= 3) we know that x will now be even and y will now be odd.
- Can we rule out one or more starting points from the get-go?
- What can we immediately check to figure out which of two directions is valid?
- Are all the answers powers of 2?
- 