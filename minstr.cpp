#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define all(val) val.begin(), val.end()
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 87178291199;
const int maxn = 1e5 + 4;
const int INF = 1e9;
const int N = 18;
const ll p = 331;

int n, m;
string s, t[maxn];
ll Pow[maxn], Inv[maxn], h[maxn];
    
ll Expo(ll a, int b) {
	if (b == 0) return 1;
	ll t = Expo(a, b / 2);
	t = t * t % mod;
	if (b & 1) t = t * a % mod;
	return t;
}
	    
map<ll,bool> mp;
	    
ll get(int i, int j, string &s) {
	return (h[j] - h[i - 1] + mod) % mod * Inv[i - 1] % mod;
}
	    
bool ok(int x) {
	mp.clear();
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j < (int)t[i].size(); j++) {
			h[j] = (h[j - 1] + (t[i] - 'a' + 1) * Pow[j] % mod) % mod;
			if (j >= x) mp[get(j - x + 1, j, t[i])] = 1;
		}
	}
	for (int i = 1; i <= 2 * n; i++) {
		h[i] = (h[i - 1] + (s[i] - 'a' + 1) * Pow[i] % mod) % mod;
		if (j >= x && mp.find(get(i - x + 1, i, s)) != mp.end())
			
	}
}
	    
int main()
{	
	ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    Pow[0] = 1;
    for (int i = 1; i <= 1e5; i++)
    	Pow[i] = Pow[i - 1] * p % mod;
    for (int i = 0; i <= 1e5; i++)
    	Inv[i] = Expo(Pow[i], mod - 2);
    cin >> n >> m >> s;
    s = ' ' + s + s;
    for (int i = 1; i <= m; i++) {
    	cin >> t[i];
    	t[i] = ' ' + t[i];
	}
	int L = 0, R = 1e4, res;
	while (L <= R) {
		int m = (L + R) / 2;
		if (ok(m)) {
			res = m;
			R = m - 1;
		}
		else L = m + 1;
	}
	cout << res;
}
