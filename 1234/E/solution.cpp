    #include<bits/stdc++.h>
    using namespace std;
    using ll = long long;
     
    int a[200010];
    int b[200010];
     
    int main(){
     
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++) cin >> a[i];
     
        for(int i = 0; i < m-1; i++){
            int x = a[i];
            int y = a[i+1];
            if(x == y) continue;
            if(a[i] > a[i+1]) swap(x, y);
            int dif = y-x;
            b[1] += dif;
            b[x] -= dif;
            b[x] += y-1;
            b[x+1] -= y-1;
            b[x+1] += dif-1;
            b[y] -= dif-1;
            b[y] += x;
            b[y+1] -= x;
            b[y+1] += dif;
            //for(int i = 0; i < n; i++) cout << b[i+1] << " ";
            //cout << endl;
        }
     
        int sum = 0;
        for(int i = 1; i <= n; i++){
            sum += b[i];
            cout << sum << " ";
        }
     
        return 0;
    }