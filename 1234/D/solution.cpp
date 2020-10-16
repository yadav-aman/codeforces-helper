#include <bits/stdc++.h>
using namespace std;
 
#define st first
#define nd second
#define pb push_back
#define popb pop_back
#define mp make_pair
#define all(x) x.begin(),x.end()
#define sortall(x) sort(all(x));
#define deb(x) cout << #x << " = " << x << endl
#define debv(x) cout << #x << ": "; for (int i = 0; i < (x).size(); i++) cout << (x)[i] << ' '; cout << endl
#define PI 3.1415926535897932384626
typedef pair< int ,int >                pii;
typedef pair< long long, long long >    pll;
typedef vector< pii >                   vii;
typedef vector< pll >                   vll;
typedef long long                       ll;
typedef map< int, int >                 mii;
typedef set< pii >                      sii;
typedef set< int >                      si;
typedef vector< int >                   vi;
typedef vector< ll >                    vl;
typedef long double                     ld;
typedef pair< ld, ld >                  pld;
typedef vector< pld >                   vpld;
 
const ll mod = 1e9 + 7;                 /// 1 000 000 007
const ll mod2 = 119 << 23 | 1;          /// 998244353
const ll mod3 = 467'093'870'598'391;    /// big prime
int inf = 1e9 + 7;
ll INF = 1e14 + 9;
 
///tagliatelle here
 
template<typename T>
class SegTree{                  ///(0,1,...n-1)
private:
    vector<T> Tree;
    int leafcount = 1;
public:
    void add(T val, int pos){
        pos += leafcount;
        while(pos){
            Tree[pos] += val;
            pos /= 2;
        }
    }
 
    T rangequery(int l, int r, int from = 0, int to = - 1, int akt = 1){
        if(to == -1)
            to += leafcount;
        if(l > r)
            return 0;
        if(from == l && r == to){
            return Tree[akt];
        }else if(from <= l && r <= to){
            int mid = from + (to - from) / 2;
            if(r <= mid)
                return rangequery(l, r, from, mid, 2 * akt);
            if(mid + 1 <= l)
                return rangequery(l, r, mid + 1, to, 2 * akt + 1);
            return rangequery(l, mid, from, mid, 2 * akt) + rangequery(mid + 1, r, mid + 1, to, 2 * akt + 1);
        }
    }
 
    SegTree(const vector<T> &tab){
        while(leafcount < tab.size())
            leafcount *= 2;
        Tree.resize(2 * leafcount);
        for(int i = 0; i < 2 * leafcount; i++)
            Tree[i] = 0;
        for(int i = 0; i < tab.size(); i++)
            add(tab[i], i);
        for(int i = tab.size(); i < leafcount; i++)
            add(0, i);                   ///filling the rest of leaves
    }
 
    SegTree(int _n){
        while(leafcount < _n)
            leafcount *= 2;
        Tree.resize(2 * leafcount);
        for(int i = 0; i < 2 * leafcount; i++)
            Tree[i] = 0;
    }
 
};
 
///
 
ll power (ll x, ll y);
ll inv (ll x);
bool isPrime (ll x);
ll gcd (ll x, ll y);
 
//================================================================================
 
const int nax = 1e5 + 13;
 
 
void prep(){
 
}
 
void solve(){
    int n, q;
    string s;
    cin >> s;
    cin >> q;
    n = s.size();
    vector<SegTree<int>> cnt(26, SegTree<int>(n));
    for(int i = 0 ; i < n; i++){
        cnt[s[i] - 'a'].add(1, i);
    }
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int pos;
            char c;
            cin >> pos >> c;
            pos--;
            cnt[s[pos] - 'a'].add(-1, pos);
            cnt[c - 'a'].add(1, pos);
            s[pos] = c;
        }else{
            int l, r;
            cin >> l >> r;
            l--, r--;
            int ile = 0;
            for(int i = 0; i < 26; i++){
                if(cnt[i].rangequery(l, r)){
                    ile++;
                }
            }
            cout << ile << endl;
        }
    }
 
}
 
int main(){                             ///use cin and printf
    ios_base::sync_with_stdio(false); cin.tie(); cout.tie(); srand(time(NULL)); cout << fixed << setprecision(1);
    int T = 1;
    prep();
    //cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}
 
ll power (ll x, ll y) {
    ll res = 1ll;
    x %= mod;
    if (x == 0)
        return 0;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % mod;
        y = y >> 1ll;
        x = (x * x) % mod;
    }
    return res;
}
 
ll inv (ll x) {
    ll r = 1ll, t = x, k = mod - 2ll;
    while (k) {
        if (k & 1ll) r = r * t % mod;
        t = (long long) t * t % mod;
        k >>= 1;
    }
    return r;
}
 
bool isPrime (ll x) {
    if (x == 1)
        return false;
    for (ll i = 2ll; i * i <= x; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}
 
ll gcd (ll x, ll y) {
    if (!y)
        return x;
    return gcd (y, x % y);
}