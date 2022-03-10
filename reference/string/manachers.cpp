vl manacher_odd(string src) {
  szn(nn,src);
  src = "$" + src + "^";
  vl p(nn + 2);
  ll l = 0, r = -1;
  Fo(i,1,nn+1) {
    p[i] = max(0, min(r - i, p[l + (r - i)]));
    while(src[i - p[i]] == src[i + p[i]])
      p[i]++;
    if(i + p[i] > r)
      l = i - p[i], r = i + p[i];
  }
  return vl(begin(p) + 1, end(p) - 1);
}

vl manacher(string src) {
  string str;
  trav(ch, src) str += string("#") + ch;
  auto res = manacher_odd(str + "#");
  return vl(begin(res) + 1, end(res) - 1);
}
