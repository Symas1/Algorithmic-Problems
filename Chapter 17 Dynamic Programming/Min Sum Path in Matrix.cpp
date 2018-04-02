int Solution::minPathSum(vector<vector<int> > &arr) {
    for(int col=1;col<arr.front().size();++col){
        arr.front()[col]+=arr.front()[col-1];
    }
    for(int row=1;row<arr.size();++row){
        arr[row].front()+=arr[row-1].front();
    }
    
    
    for(int row=1;row<arr.size();++row){
        for(int col=1;col<arr[row].size();++col){
            arr[row][col]+=min(arr[row-1][col],arr[row][col-1]);
        }
    }
    
    return arr.back().back();
} // time O(n^2); space O(n^2)