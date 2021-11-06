class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    map<string, vstr> m;
    trav(str, strs) {
      string str2 = str;
      sortall(str2);
      m[str2].pb(str);
    }
    vvstr o;

    for (auto [k,v]: m) {
      o.pb(v);
    }

    return o;
  }
};
