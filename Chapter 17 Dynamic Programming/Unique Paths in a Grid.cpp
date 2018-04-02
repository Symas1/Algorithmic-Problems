int unique_paths(const vector<vectro<int>>& arr){
       vector<vector<int>>paths(arr.size(),vector<int>(arr.front().size(),0));
    
    paths[0][0]=arr[0][0]==1?0:1;
    for(int col=1;col<arr.front().size();++col){
        if(arr[0][col]!=1){
            paths[0][col]+=paths[0][col-1];
        }
    }
    for(int row=1;row<arr.size();++row){
        if(arr[row][0]!=1){
            paths[row][0]+=paths[row-1][0];
        }
    }
    
    for(int row=1;row<arr.size();++row){
        for(int col=1;col<arr.front().size();++col){
            if(arr[row][col]!=1){
                paths[row][col]=paths[row-1][col]+paths[row][col-1];
            }
        }
    }
    return paths.back().back();
} // time O(n^2); space O(n^2)

int unique_paths_better(const vector<vectro<int>>& arr){
    bool vertical = arr.front().size() < arr.size();
	vector<int>paths(vertical ? arr.front().size(): arr.size(), 0);
	paths[0] = arr[0][0] == 1 ? 0 : 1;

	for (int iter = 0; iter < (vertical ? arr.size() : arr.front().size()); ++iter) {
		if (paths[0] != 0){
			paths[0] = arr[vertical ? iter : 0][vertical ? 0 : iter] == 1 ? 0 : 1;
		}

		for (int iter2 = 1; iter2 < paths.size(); ++iter2) {
			if (vertical) {
				if (arr[iter][iter2] != 1) {
					paths[iter2] += paths[iter2-1];
				}
				else {
					paths[iter2] =0;
				}
			}
			else {
				if (arr[iter2][iter] != 1) {
					paths[iter2] += paths[iter2 - 1];
				}
				else {
					paths[iter2] = 0;
				}
			}
		}
	}
	return paths.back();
} // time O(n^2); space O(min(n,m))
