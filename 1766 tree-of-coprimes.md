给你一个 `n` 个节点的树（也就是一个无环连通无向图），节点编号从 `0` 到 `n - 1` ，且恰好有 `n - 1` 条边，每个节点有一个值。树的 **根节点** 为 0 号点。

给你一个整数数组 `nums` 和一个二维数组 `edges` 来表示这棵树。`nums[i]` 表示第 `i` 个点的值，`edges[j] = [uj, vj]` 表示节点 `uj` 和节点 `vj` 在树中有一条边。

当 `gcd(x, y) == 1` ，我们称两个数 `x` 和 `y` 是 **互质的** ，其中 `gcd(x, y)` 是 `x` 和 `y` 的 **最大公约数** 。

从节点 `i` 到 **根** 最短路径上的点都是节点 `i` 的祖先节点。一个节点 **不是** 它自己的祖先节点。

请你返回一个大小为 `n` 的数组 `ans` ，其中 `ans[i]`是离节点 `i` 最近的祖先节点且满足 `nums[i]` 和 `nums[ans[i]]` 是 **互质的** ，如果不存在这样的祖先节点，`ans[i]` 为 `-1` 。

**示例 1：**

**![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/02/20/untitled-diagram.png)**

```
输入：nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
输出：[-1,0,0,1]
解释：上图中，每个节点的值在括号中表示。
- 节点 0 没有互质祖先。
- 节点 1 只有一个祖先节点 0 。它们的值是互质的（gcd(2,3) == 1）。
- 节点 2 有两个祖先节点，分别是节点 1 和节点 0 。节点 1 的值与它的值不是互质的（gcd(3,3) == 3）但节点 0 的值是互质的(gcd(2,3) == 1)，所以节点 0 是最近的符合要求的祖先节点。
- 节点 3 有两个祖先节点，分别是节点 1 和节点 0 。它与节点 1 互质（gcd(3,2) == 1），所以节点 1 是离它最近的符合要求的祖先节点。
```

**示例 2：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/02/20/untitled-diagram1.png)

```
输入：nums = [5,6,10,2,3,6,15], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
输出：[-1,0,-1,0,0,0,-1]
```

 

**提示：**

- `nums.length == n`
- `1 <= nums[i] <= 50`
- `1 <= n <= 105`
- `edges.length == n - 1`
- `edges[j].length == 2`
- `0 <= uj, vj < n`
- `uj != vj`

思路：

建图，从0节点遍历，标记已经访问的节点。  
对每个节点dfs,处理自己的时候从栈里向上找到第一个valid的值，找不到就赋值为-1.

```cpp

#define spice
#ifdef spice
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vii;
#define all(c) c.begin(), c.end()
const int dx[4]{ 1,0,-1,0 }, dy[4]{ 0,1,0,-1 };
#define sz(a) int((a).size())
#define pb push_back
template<typename T> void un(T& n) { sort(all(n)); n.erase(std::unique(n.begin(), n.end()), n.end()); }
template<typename T>set<typename T::value_type> to_set(T t) { return set(t.begin(), t.end()); }
template<typename T>vector<typename T::value_type> set_to(T input) { vector<typename T::value_type> output; std::copy(input.begin(), input.end(), std::back_inserter(output)); return output; }
vector<int> get_insect(vector<int>n1, vector<int> n2) { vector<int> res; set_intersection(all(n1), all(n2), inserter(res, res.end())); return res; }
template<typename T>auto clear(queue<T>& q) { std::queue<T>empty; std::swap(q, empty); }
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
#define dbg(x) cout << #x << " is " << x << endl;
#define ed cout << endl;

//#define  sw cout<<res<<endl<<l<<" "<<r<<endl<<endl; //滑动窗口debug用。
//#define rt  return res;
#endif

class Solution{
  void preOrder(vii& g, vi& visited, stack<int> st, int n, vector<int> nums, vi& res)
  {
    if (visited[n])return;  //处理右孩子的时候跳过root和left child
    visited[n] = 1;
    st.push(n);
    for (auto i : g[n])
      preOrder(g, visited, st, i, nums, res);
    st.pop(); //弹出当前元素
    while (!st.empty()) //向上找到第一个valid的parent.
    {
      auto top = st.top(); st.pop();
      if (gcd(nums[top], nums[n]) == 1)
        res[n] = top;
    }
    if (res[n]== INT_MAX) //没找到
      res[n] = -1;
    return;
  }
public:
  vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& e) {
    vector<vector<int>> adj(nums.size());
    vector<int> visited(nums.size(), 0);
    for (auto& edge : e) {  
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);//单向边是不是更好，就不需要visited了。 为什么注释这个会导致大量INT_MAX.
    }
    vector<int> res(nums.size(),INT_MAX );
    stack<int> stk;
    //树的 根节点 为 0 号点
    preOrder(adj, visited, stk, 0, nums, res);
    return res;
  }
};
```

过了第一个例子，挂在

```bash
output：[-1,0,17,0,17,0,17,0,17,0,0,0,0,0,17,0,0,0,17,0,0,17,0,0,0,17,17,17,17,0,0,0,17,0,0,0,17,0,0,0,0,17,0,0,0,0,17]
excepted:[-1,21,17,43,10,42,7,13,29,44,17,31,39,10,10,29,32,0,40,23,12,39,12,40,25,35,15,38,40,40,17,24,5,1,19,14,17,21,25,24,14,17,40,25,37,17,10]

```

