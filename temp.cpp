class Solution {
  const long long mod = 1000000007;
  unordered_map<long long, long long> memo;
  long long decode(long long str, int len)
  {
    if (str == 0)return 1;
    if (str == 1)return 1;
    if (memo.find(str) != memo.end())return memo[str];
    long long cnt = 0;
    for (int i = 1; i <= len; ++i) {
      if (i > str)break;
      if (i == str) {
        cnt += decode(0, len);
        continue;
      }
      cnt += decode(str - i, len);
    }
    cnt = cnt % mod;
    memo[str] = cnt;
    return cnt;
  }
public:
  long long countTexts(string s) {
    long long curr = 1;
    long long res = 1;
    char ch = s[0];
    for (int i = 1; i < s.size(); ++i)
    {
      if (s[i] == ch) {
        ++curr;
      }
      else {
        int len = 0;
        if (ch == '7' || ch == '9')
          len = 4;
        else len = 3;
        res *= decode(curr, len);
        res %= mod;
        curr = 1;
        ch = s[i];
      }
    }
    int len = 0;
    if (ch == '7' || ch == '9')len = 4;
    else len = 3;
    res *= decode(curr, len);
    res %= mod;
    return res;
  }
};
