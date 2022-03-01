auto MSB = [&](ll x) {
  // if using 32-bit int:
  // return 31 - __builtin_clzll(x);
  return 63 - __builtin_clzll(x);
};
