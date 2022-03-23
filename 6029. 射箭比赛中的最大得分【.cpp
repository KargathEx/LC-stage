//就他妈离谱，所有例子都过了却超时，似乎就是在卡我自己。 
//坐等官方解答\
//https://leetcode-cn.com/problems/maximum-points-in-an-archery-competition/
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<char> vc;
typedef vector<vc> vcc;
#define all(c) c.begin(), c.end()
#define ed endl
#define present(container, element)(container.find(element) != container.end())
#define cpresent(container, element)(find(all(container), element) != container.end())
#define sz(a) int((a).size())
#define pb push_back
#define loop(x, n,step) for(int x = 0; x < n; x+=step)
#define dbg(x) cerr << #x << " is " << x << endl;
//#define un(n) n.erase(std::unique(n.begin(), n.end()), n.end()); 
template<typename T> void un(T& n) { n.erase(std::unique(n.begin(), n.end()), n.end()); }
//#define dbg(x);

class Solution {
  //0/1背包只有O(n^2)的形式吧？ 滚动也只降长度。
  int knapsack(int capacity, const std::vector<int>& W, const std::vector<int>& V, std::vector<int>& itemsSelected) {

    //if (W.size() == 0 || W.size() != V.size() || capacity < 0)
    //  throw std::invalid_argument("Invalid input");

    int N = W.size();

    // Initialize a table where individual rows represent items
    // and columns represent the weight of the knapsack
    std::vector<std::vector<int>> DP(N + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= N; i++) {

      // Get the value and weight of the item
      int w = W[i - 1], v = V[i - 1];

      for (int sz = 1; sz <= capacity; sz++) {

        // Consider not picking this element
        DP[i][sz] = DP[i - 1][sz];

        // Consider including the current element and
        // see if this would be more profitable
        if (sz >= w && DP[i - 1][sz - w] + v > DP[i][sz]) DP[i][sz] = DP[i - 1][sz - w] + v;
      }
    }

    int sz = capacity;

    // Using the information inside the table we can backtrack and determine
    // which items were selected during the dynamic programming phase. The idea
    // is that if DP[i][sz] != DP[i-1][sz] then the item was selected
    for (int i = N; i > 0; i--) {
      if (DP[i][sz] != DP[i - 1][sz]) {
        int itemIndex = i - 1;
        itemsSelected.push_back(itemIndex); //保存的是什么？应该是被选中的区域的index吧。
        sz -= W[itemIndex];
      }
    }

    // Return the maximum profit
    return DP[N][capacity];
  }
public:
  vector<int> maximumBobPoints(int n, vector<int>& a) {
    int A = 0;
    for (int i = 0; i < a.size(); ++i)
      if (a[i] != 0)A += i;
    for (auto& i : a)++i;
    vector<int> value(a.size(),0);
    iota(all(value), 0);
    vector<int> used;
    vector<int> res(a.size(),0);

    int b=knapsack(n, a, value, used);
    for (auto i : used) {
      res[i] = a[i];
    }
    int valid = accumulate(all(res), 0);
    if (valid < n) res[0] = n - valid;
    return res;
  }
};