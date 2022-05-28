
class BookMyShow {
  vector<vector<int>> seat;
  vector<int> rest; //每排剩余，以及第一个空座位的位置?不需要，向左看齐就好，第一个减法即可。
  int n_;
  int m_;
public:
  BookMyShow(int n, int m) {
    vector<vector<int>> t(n, vector<int>(m, 0));
    seat = t;
    rest.resize(n, m);
    n_ = n;
    m_ = m;
  }

  vector<int> gather(int k, int maxRow) { //是否忘了修改里面的值?
    if (k > m_)return {};
    int Begin = INT_MAX;
    int row = 0;
    for (int i = 0; i <=maxRow; ++i)
      if (rest[i] >= k && i <= maxRow) {
        Begin = m_ - rest[i];
        rest[i] -= k;
        row = i;
        break;
      }
    if (Begin == INT_MAX)return {};
    return vector<int>{row, Begin};
  }

  bool scatter(int k, int maxRow) {
    //在每排找空余，累加，看看满足k的时候是否小于maxRwo
    vi rest_ = rest;
    for (int i = 0; i <= maxRow; ++i)
    {
      k -= rest[i];
      rest_[i] = 0;
      if (k <= 0 && i <= maxRow)//说明当前行够了
      {
        rest_[i] -= k;
        rest = rest_;
        return true;
      }
    }
    return false;
  }
  BOOST_DESCRIBE_CLASS(BookMyShow, (), (gather, scatter), (), ());
};
