int Solution::minDistance(string a, string b) {
    if(b.empty()){
        return a.size();
    }
    if(a.size()>b.size()){
        swap(a,b);
    }
    
    vector<int>dist(a.size()+1,0);
    iota(dist.begin(),dist.end(),0);
    for(int i=0;i<b.size();++i){
        int diag=dist[0];
        dist[0]=i+1;
        for(int j=1;j<dist.size();++j){
            int save_diag=dist[j];
            if(b[i]==a[j-1]){
                dist[j]=diag;
            }else{
                dist[j]=min({dist[j],dist[j-1],diag})+1;
            }
            diag=save_diag;
        }
    }
    return dist.back();
} // time O(nm); space O(min(n,m));