https://leetcode.cn/problems/WInSav/
这个做法不对，有三件事可以做：  
1.说清楚错在哪里   
2.翻一翻Tree部分的问题    
3.找一个能看得懂的答案    

```cpp

class Solution {
  vii levelOrder(TreeNode* r)
  {
    vii res;
    queue<TreeNode*> q;
    q.push(r);
    while (!q.empty())
    {
      int len = q.size();
      vi out;
      while (len-- > 0)
      {
        auto curr = q.front(); q.pop();
        if (!curr) {
          out.push_back(0);
          continue;
        }
        out.push_back(curr->val);
        q.push(curr->left);
        q.push(curr->right);
      }
      res.push_back(out);
    }
    res.pop_back();
    return res;
  }
public:
  int getMaxLayerSum(TreeNode* root) {
    auto res = levelOrder(root);
    int val = accumulate(all(res.back()), 0);
    dbg(res);
    for (int i = 0; i < res.size() - 1; ++i)
    {
      int diff = 0;
      for (int j = 0; j < res[i].size()-1; ++j)
        diff = max(diff, max(res[i + 1][j], res[i + 1][j + 1]) - res[i][j]);
      int sum = accumulate(all(res[i]), 0) + diff;
      val = max(val, sum);
    }
    return val;
  }
};

```
