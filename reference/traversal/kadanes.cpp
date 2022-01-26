/*
  Standard Kadane's. Only calcs the sum
*/

int ans = a[0], sum = 0;

fo(r, n) {
    sum += a[r];
    ans = max(ans, sum);
    sum = max(sum, 0);
}

/*
  This version maintains the indexes of the boundaries of 
  the corresponding segment
*/

int ans = a[0], ans_l = 0, ans_r = 0;
int sum = 0, minus_pos = -1;

fo (r, n) {
    sum += a[r];
    if (sum > ans) {
        ans = sum;
        ans_l = minus_pos + 1;
        ans_r = r;
    }
    if (sum < 0) {
        sum = 0;
        minus_pos = r;
    }
}
