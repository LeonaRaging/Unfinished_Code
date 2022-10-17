#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 5e3 + 4;
const int INF = 1e9;
const int N = 5e3 + 4;

// dp[u][i][0 / 1] = o cay con goc u, cat i canh, 0/1 : co/ko may tinh
// cat canh u-v:
// dp[u][i + j][x] = dp[u][i][x] neu y == 0 hoac dp[v][j][y] < 0
// ko cat canh u-v:
// dp[u][j][x | y] = dp[u][i][x] + dp[v][j][y] 

int n, a[N], sz[maxn], sum[maxn], dp[N][N][2];
vector<int> adj[N];

void MIN(int &a, int b) {
    if (a > b) a = b;
}

void dfs(int u, int p) {
    sum[u] = a[u];
    bool flag = (a[u] < 0 ? 1 : 0);
    dp[u][0][flag] = a[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        if (dp[v][0][1] != dp[0][0][0])
            flag = 1;
        sum[u] += sum[v];
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        for (int i = sz[u]; i >= 0; i--)
            for (int j = min(sz[v], i); j >= 0; j--)
                for (int x = 0; x < 2; x++) if (dp[u][i][x] != dp[0][0][0]) {
                    for (int y = 0; y < 2; y++) {
                        if (y == 0 || dp[v][j][y] < 0)
                            MIN(dp[u][i + j + 1][x], dp[u][i][x]);
                        MIN(dp[u][i + j][x | y], dp[u][i][x] + dp[v][j][y]);
                    }   
                }
        sz[u] += sz[v] + 1;
    }   
    dp[u][0][flag] = sum[u];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    memset(dp, 63, sizeof dp);
    dfs(1, 0);
    int res = n - 1;
    for (int k = n - 1; k >= 0; k--) {
        if (dp[1][k][0] != INF) res = k;
        if (dp[1][k][1] < 0) res = k;
    }
    cout << res;
    // clog << db(dp[5][1][1]);
}
