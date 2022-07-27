#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const ll mod = 1e9 + 7;
const int N = 205;
const int INF = 1e9;
const int maxn = 1e5;

struct Edge {
    int u, v, flow, capa, cost;
    Edge (int _u, int _v, int _capa, int _cost) {
        u = _u; v = _v; capa = _capa; cost = _cost; flow = 0;
    }
};

int inq[N], dis[N], trace[N], res[N];
vector<int> adj[N], myVec[N];
vector<Edge> edges;

void addedge(int u, int v, int w, int c) {
    adj[u].pb(edges.size());
    edges.pb(Edge(u, v, w, c));
    adj[v].pb(edges.size());
    edges.pb(Edge(v, u, 0, -c));
}

bool FindPath(int src, int snk) {
    memset(inq, false, sizeof inq);
    memset(dis, 63, sizeof dis);
    queue<int> q;
    q.push(src);
    dis[src] = 0; inq[src] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for (auto idx : adj[u]) {
            int v = edges[idx].v, w = edges[idx].cost;
            if (edges[idx].flow < edges[idx].capa && dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                trace[v] = idx;
                if (!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return (dis[snk] != dis[0]);
}

pair<int,int> MinCost(int src, int snk) {
    int flow = 0, cost = 0;
    while (FindPath(src, snk)) {
        int delta = INF;
        for (int u = snk; u != src; u = edges[trace[u]].u)
            delta = min(delta, edges[trace[u]].capa - edges[trace[u]].flow);
        for (int u = snk; u != src; u = edges[trace[u]].u) {
            edges[trace[u]].flow += delta;
            edges[trace[u] ^ 1].flow -= delta;
            cost += delta * edges[trace[u]].cost;
        }
        flow += delta;
    }
    return {flow, cost};
}

int n, m, id[N][N], vis[N][N];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int src = 2 * n + 1, snk = 2 * n + 2, idx = 2 * n + 2;
    int sum = 0;
    for (int t = 1; t <= m; t++) {
        int u, v, r, c, x; cin >> u >> r >> v >> c >> x;
        idx++;
        for (int i = u; i <= v; i++)
            addedge(i, idx, 1, 0);
        idx++;
        for (int i = r; i <= c; i++)
            addedge(idx, i + n, 1, 0);
        addedge(idx - 1, idx, x, -1);
        for (int i = u; i <= v; i++)
            for (int j = r; j <= c; j++)
                vis[i][j] = vis[j][i] = 1;
        sum += x;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) if (!vis[i][j])
            addedge(i, j + n, 1, 0);
    for (int i = 1; i <= n; i++) {
        addedge(src, i, 1, 0);
        addedge(i + n, snk, 1, 0);
    }
    auto ans = MinCost(src, snk);
    for (auto it : edges)
        cout << it.u << ' ' << it.v << ' ' << it.cost << '\n';
    cout << ans.se << ' ';
    if (ans.fi != n || ans.se != -sum) return cout << "NO", 0;
    cout << "YES" << '\n';
    for (auto it : edges) {
        int u = it.u, v = it.v;
        if (it.flow == 1) {
            if (u <= n && v <= 2 * n) res[u] = v - n;
            if (u <= n && v > 2 * n) myVec[v].pb(u);
            if (u > 2 * n && v > n && v <= 2 * n) myVec[u].pb(v - n);
        }
    }
    for (int i = 2 * n + 3; i <= idx; i += 2) {
        for (int k = 0; k < int(myVec[i].size()); k++)
            res[myVec[i][k]] = myVec[i + 1][k];
    }
    for (int i = 1; i <= n; i++) cout << res[i] << ' ';
}
