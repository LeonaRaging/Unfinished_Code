#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
#define mp make_pair
using namespace std;
const int maxn = 4e5 + 4;
const int INF = 1e9;
const ll mod = 1e9 + 7;
const int N = 1e4 + 3;

int n, k, s, dp[N][N], g[N][N], sz[N];
vector<pair<int,int>> adj[maxn];

void dfs(int u, int p) {
    dp[u][1] = g[u][1] = 0;
    sz[u] = 1;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        for (int j = min(sz[u], k); j > 1; j--)
            for (int t = 1; t <= min(sz[v], j); t++) {
                g[u][j] = min({g[u][j], dp[u][j - t] + w + g[v][t], g[u][j - t] + 2 * w + dp[v][t]});
                dp[u][j] = min(dp[u][j], dp[u][j - t] + 2 * w + dp[v][t]);
            }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("TOURIST.INP", "r", stdin);
    freopen("TOURIST.OUT", "w", stdout);
    cin >> n >> k >> s;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INF;
            g[i][j] = INF;
        }
    dfs(s, 0);
    cout << g[s][k];
}
