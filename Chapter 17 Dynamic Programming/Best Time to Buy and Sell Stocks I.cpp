int Solution::maxProfit(const vector<int> &arr) {
    int res = 0;
    int m = numeric_limits<int>::max();
    for(int i=0;i<arr.size();++i){
        m = min(m,arr[i]);
        res = max(res, arr[i]-m);
    }
    return res;
} // O(n); space O(1)