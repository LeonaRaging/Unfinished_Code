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

int n, m, t, k, l = INF, dis[maxn], dp[maxn][105];
vector<pair<int,int>> adj[maxn], g[maxn];

void dijkstra(int src) {
    using T = pair<int,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    memset(dis, 63, sizeof dis);
    dis[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        int d, u; tie(d, u) = pq.top(); pq.pop();
        if (dis[u] != d) continue;
        for (auto it : g[u]) {
            int v, w; tie(v, w) = it;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

int Solve(int u, int p) {
    if (p + dis[u] > l || p < 0) return 0;
    if (dp[u][p] != -1)
        return dp[u][p];
    int res = 0;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        res += Solve(v, p  - w + dis[u] - dis[v]);
        res = min(res, k);
    }
    return dp[u][p] = res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> m >> t >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        g[v].pb({u, w});
        l = min(l, w);
    }
    for (int i = 1; i <= n; i++)
        sort(adj[i].begin(), adj[i].end());
    dijkstra(t);
    if (dis[1] == dis[0])
        return cout << -1, 0;
    l += dis[1];
    memset(dp, -1, sizeof dp);
    dp[t][0] = 1;
    int tot = 0;
    for (int p = 0; p <= l - dis[1]; p++) {
        tot += Solve(1, p);
        tot = min(tot, k);
    }
    if (tot < k) return cout << -1, 0;
    vector<int> res;
    int u = 1;
    while (true) {
        res.pb(u);
        if (u == t && k == 1) break;
        for (auto it : adj[u]) {
            int v, w; tie(v, w) = it;
            if (dis[v] == dis[0]) continue;
            int tot = 0;
            for (int p = 0; p <= l - w - dis[v]; p++) {
                tot += Solve(v, p);
                tot = min(tot, k);
            }
            if (tot >= k) {
                u = v; l -= w;
                break;
            }
            else k -= tot;
        }
    }
    cout << res.size() << '\n';
    for (auto i : res) cout << i << ' ';
}
