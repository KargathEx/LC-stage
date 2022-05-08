class Solution {
  const long long mod = 1000000007;
  unordered_map<string, long long> memo;
  //len为当前字符串最大解码可用子串长度.
  long long decode(string str, int len)
  {
    if (str.empty())return 1;
    if (str.size() == 1)return 1;
    if (memo.find(str) != memo.end())return memo[str];
    long long cnt = 0;
    for (int i = 1; i <= len; ++i){
      if (i > str.size())break;
      if (i == str.size()) {
        cnt += decode("", len);
        continue;
      }
      cnt += decode(str.substr(i), len);
    }
    cnt = cnt % mod;
    memo[str] = cnt;
    return cnt;
  }
public:
  long long countTexts(string s) {
    string curr(1, s[0]);
    long long res = 1;
    for (int i = 1; i < s.size(); ++i)
    {
      if (s[i] == curr.back()) {
        curr.push_back(s[i]);
      }
      else {
        int len = 0;
        if (curr.back() == '7' || curr.back() == '9')len = 4;
        else len = 3;
        res *= decode(curr, len);
        res %= mod;
        curr = string(1, s[i]);
      }
    }
    int len = 0;
    if (curr.back() == '7' || curr.back() == '9')len = 4;
    else len = 3;
    res *= decode(curr, len);
    res %= mod;
    return res;
  }
};
