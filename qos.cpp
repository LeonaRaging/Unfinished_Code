#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
const ll mod = 1e9 + 7;
const int maxn = 1e3 + 4;
const int INF = 1e9;
const int N = 105;

int n, m, t, k, dis[maxn], dp[maxn][N], cnt[maxn];
vector<pair<int,int>> adj[maxn];
vector<int> res;

void dijkstra(int src) {
    memset(dis, 63, sizeof dis);
    dis[src] = 0;
    using T = pair<int,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        int d, u; tie(d, u) = pq.top(); pq.pop();
        if (dis[u] != d) continue;
        for (auto it : adj[u]) {
            int v, w; tie(v, w) = it;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

int Solve(int u, int l) {
    if (l < dis[u]) return 0;
    if (dp[u][l - dis[u]] != -1)
        return dp[u][l - dis[u]];
    int res = 0;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        res += Solve(v, l - w);
        res = min(res, INF);
    }
    return dp[u][l - dis[u]] = res;
}

void query(int u, int num) {
    res.pb(u);
    if (u == t) return;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (cnt[v] >= num) {
            query(v, num);
            return;
        }
        num -= cnt[v];
    }
}

int main()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> m >> t >> k;
    int cmin = INF;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        cmin = min(cmin, w);
    }
    dijkstra(t);
    memset(dp, -1, sizeof dp);
    dp[t][0] = 1;
    int num = 0;
    for (int i = 0; i <= cmin; i++) {
        num += Solve(1, i + dis[1]);
        num = min(num, INF);
    }
    if (num < k) return cout << -1, 0;
    for (int i = 1; i <= n; i++)
        sort(adj[i].begin(), adj[i].end());
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= cmin; j++) {
            cnt[i] += dp[i][j];
            cnt[i] = min(cnt[i], INF);
        }
    query(1, k);
    cout << res.size() << '\n';
    for (auto i : res) cout << i << ' ';
}
