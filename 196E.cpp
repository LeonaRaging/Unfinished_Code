#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const ll mod = 1e9 + 7;
const int maxn = 3e5 + 4;
const ll INF = 1e16;
const int N = 505;
random_device rd;
mt19937 mt{rd()};

struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) {
        return w < other.w;
    }
};

struct Data {
    vector<int> par, Rank;
    Data (int n) {
        par.resize(n + 4);
        Rank.resize(n + 4);
        for (int i = 1; i <= n; i++) par[i] = i, Rank[i] = 1;
    }
    int find(int x) {
        if (x != par[x]) par[x] = find(par[x]);
        return par[x];
    }
    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return 0;
        if (Rank[u] < Rank[v]) swap(u, v);
        Rank[u] += Rank[v];
        par[v] = u;
        return 1;
    }
} Dsu(maxn);

int n, m, k, node[maxn];
vector<Edge> pre, edges;
pair<ll,int> dis[maxn];
vector<pair<int,int>> adj[maxn];

ll dijkstra(int src) {
    vector<ll> dis(maxn, INF);
    using T = pair<ll,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    dis[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        int u; ll d; tie(d, u) = pq.top(); pq.pop();
        if (dis[u] != d) continue;
        for (auto it : adj[u]) {
            int v; ll w; tie(v, w) = it;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
    ll ans = INF;
    for (int i = 1; i <= k; i++) ans = min(ans, dis[node[i]]);
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("test.INP", "r", stdin);
    //freopen("EraseSeqR.OUT", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        pre.pb({u, v, w});
    }
    using T = pair<pair<ll,int>,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    memset(dis, 63, sizeof dis);
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> node[i];
        dis[node[i]] = {0, node[i]};
        pq.push({dis[node[i]], node[i]});
    }
    while (!pq.empty()) {
        int u; pair<ll,int> d; tie(d, u) = pq.top(); pq.pop();
        if (dis[u] != d) continue;
        for (auto it : adj[u]) {
            int v, w; tie(v, w) = it;
            if (dis[u].fi + w < dis[v].fi) {
                dis[v].fi = dis[u].fi + w;
                dis[v].se = dis[u].se;
                pq.push({dis[v], v});
            }
        }
    }
    for (auto it : pre) {
        int u = it.u, v = it.v, w = it.w;
        if (dis[u].se != dis[v].se)
            edges.pb({u, v, w});
    }
    sort(edges.begin(), edges.end());
    ll ans = 0;
    for (auto it : edges) {
        int u = it.u, v = it.v; ll w = it.w;
        if (Dsu.join(u, v)) ans += w;
    }
    ans += dijkstra(1);
    cout << ans;
}
