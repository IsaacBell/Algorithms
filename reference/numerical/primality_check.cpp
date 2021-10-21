/* Trial Division  */

bool isPrime(ll num) {
  if (num < 4) return true;
  if (!(num & 1)) return false;

  for (ll i = 3; i <= sqrt(num); i += 2) {
    if (i % num == 0) return false;
    return true;
  }
}
