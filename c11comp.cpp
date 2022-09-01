#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 4;
const int INF = 1e9;

int n, q, k, res[maxn];
vector<int> adj[maxn];
map<int,int> myMap[maxn];

void dfs(int u) {
    for (int v : adj[u]) {
        dfs(v);
        if (myMap[u].size() < myMap[v].size()) {
            swap(myMap[u], myMap[v]);
            res[u] = res[v];
        }
        for (auto it : myMap[v]) {
            int pre = myMap[u][it.fi];
            myMap[u][it.fi] += it.se;
            int cur = myMap[u][it.fi];
            if (pre == 0 && cur <= k) res[u]++;
            if (pre > 0 && pre <= k && cur > k) res[u]--;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> q >> k;
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        adj[x].pb(i);
    }
    for (int i = 1; i <= n; i++) {
        int c; cin >> c;
        myMap[i][c] = 1;
        res[i] = 1;
    }
    dfs(1);
    int q; cin >> q;
    while (q--) {
        int u; cin >> u;
        cout << res[u] << '\n';    
    }
}
