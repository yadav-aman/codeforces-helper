    #pragma GCC optimize("Ofast")
    #pragma GCC target("avx,avx2,fma")
    //#pragma GCC optimize("O3")
     
    #include<iostream>
    #include<algorithm>
    #include<string>
    #include<cmath>
    #include<cstdlib>
    #include<set>
    #include<vector>
    #include<sstream>
    #include<queue>
    #include <iomanip>
    #include<unordered_set>
    #include <stack>
    #include <unordered_map>
    #include <map>
    #include <limits>
    #include<numeric>
    #include<chrono>
    #include <fstream>
     
    constexpr auto INF = 9223372036854775807;
    typedef long long int ll;
    typedef unsigned long long int ull;
    typedef unsigned long int ul;
     
    #define pq_pair priority_queue <pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>>
    #define f(i,a,b) for(ll i=(ll)a;i<(ll)b;i+=1)
    #define rf(i,a,b) for(ll i=(ll)a;i>=(ll)b;i-=1)
    #define endl '\n'
    #define N 1000000007 // prime modulo value 
    #define all(x) x.begin(),x.end()
     
    using namespace std;
    struct custom_hash {
    	static uint64_t splitmix64(uint64_t x) {
    		// http://xorshift.di.unimi.it/splitmix64.c
    		x += 0x9e3779b97f4a7c15;
    		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    		return x ^ (x >> 31);
    	}
     
    	size_t operator()(uint64_t x) const {
    		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    		return splitmix64(x + FIXED_RANDOM);
    	}
    };
     
    inline ll gcd(ll a, ll b)
    {
    	// This is code taken from geeksforgeek
    	if (b == 0)
    		return a;
    	return gcd(b, a % b);
    }
    ll mod_power(ll x, ll y)
    {
    	// This is code taken from geeksforgeek
    	ll res = 1;
     
    	x = x % N;
    	if (x == 0) return 0;
    	while (y > 0)
    	{
    		if (y & 1)
    			res = (res * x) % N;
    		y = y >> 1;
    		x = (x * x) % N;
    	}
    	return res;
    }
     
     
    bool isprime(ll n)
    {
    	if (n == 2)
    		return true;
    	if (n % 2 == 0 || n == 1)
    	{
    		return false;
    	}
    	for (ll j = 3; j <= sqrt(n); j += 2)
    	{
    		if (n % j == 0)
    		{
    			return false;
    		}
    	}
    	return true;
    }
     
    bool valid(ll x, ll y,ll c1,ll c2,ll n)
    {
    	if(x+c1>=0 && x+c1<n)
    	{
    		if(y+c2>=0 && y+c2<n)
    		{
    			return true;
    		}
    	}
    	return false;
    }
     
     
    int main()
    {
    	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    	ll n,k;
    	cin>>n>>k;
    	vector<ll> arr(n,0);
    	f(i,0,n)
    	{
    		cin>>arr[i];
    	}
    	queue<ll> q;
    	unordered_set<ll> st;
    	f(i,0,n)
    	{
    		if(q.size()<k && st.find(arr[i])==st.end())
    		{
    			q.push(arr[i]);
    			st.insert(arr[i]);
    		}
    		else if(q.size()==k && st.find(arr[i])==st.end())
    		{
    			ll temp=q.front();
    			st.erase(st.find(temp));
    			q.pop();
    			st.insert(arr[i]);
    			q.push(arr[i]);
    		}
    	}
    	vector<ll> ans;
    	while(!q.empty())
    	{
    		ans.push_back(q.front());
    		q.pop();
    	}
    	cout<<ans.size()<<endl;
    	rf(i,ans.size()-1,0)
    	{
    		cout<<ans[i]<<" ";
    	}
    	cout<<endl;
    	return 0;
    }