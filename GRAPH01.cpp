#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define pf push_front
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e6 + 4;
const int INF = 1e9;

int n, m, a[maxn], dis[maxn][2];
vector<pair<int,int>> adj[maxn];

void bfs(int src) {
    using T = tuple<int,int,int>;
    deque<T> dq;
    memset(dis, 63, sizeof dis);
    dis[src][0] = a[src];
    dq.pb({a[src], 0, src});
    while (!dq.empty()) {
        int u, pre, d; tie(d, pre, u) = dq.front(); dq.pop_front();
        // clog << u << ' ' << d << '\n';
        if (dis[u][pre] != d) continue;
        for (auto it : adj[u]) {
            int v, w; tie(v, w) = it;
            if (w != (a[u] ^ pre) && u != 1) continue;
            if (dis[u][pre] + w + a[v] < dis[v][w]) {
                dis[v][w] = dis[u][pre] + w + a[v];
                if (w == 0) dq.pf({dis[v][w], w, v});
                else dq.pb({dis[v][w], w, v});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("GRAPH01.INP", "r", stdin);
    freopen("GRAPH01.OUT", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    bfs(1);
    if (dis[n][0] == dis[0][0] && dis[n][1] == dis[0][0])
        cout << -1;
    else cout << min(dis[n][0], dis[n][1]);
}
