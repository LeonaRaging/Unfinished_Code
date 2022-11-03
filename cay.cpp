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
const int N = 18;

struct Query {
    int s, e;
    ll t;
    bool dire;
    Query(int s = 0, int e = 0, ll t = 0, bool dire = 0): s(s), e(e), t(t), dire(dire) {}
};

int n, q, tin[maxn], tout[maxn], h[maxn], up[maxn][20], mx[maxn][20];
ll dis[maxn], sum[maxn][20];
vector<pair<int,int>> adj[maxn];

void dfs(int u, int p) {
    tin[u] = ++tin[0];
    for (int j = 1; j <= N; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
        mx[u][j] = max(mx[u][j - 1], mx[up[u][j - 1]][j - 1]);
        sum[u][j] = sum[u][j - 1] + sum[up[u][j - 1]][j - 1];
    }
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == p) continue;
        up[v][0] = u;
        mx[v][0] = w;
        sum[v][0] = w;
        h[v] = h[u] + 1;
        dis[v] = dis[u] + w;
        dfs(v, u);
    }
    tout[u] = tin[0];
}

bool isPar(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    if (isPar(v, u)) return v;
    for (int j = N; j >= 0; j--)
        if (!isPar(up[u][j], v))
            u = up[u][j];
    return up[u][0];
}

int jump(int u, int v) {
    // clog << u << ' ' << v;
    if (isPar(v, u))
        return v;
    for (int j = N; j >= 0; j--)
        if (!isPar(up[u][j], v))
            u = up[u][j];
    return up[u][0];
}

int get(int u, int p) {
    int res = 0;
    for (int j = N; j >= 0; j--)
        if (!isPar(up[u][j], p)) {
            res = max(res, mx[u][j]);
            u = up[u][j];
        }
    res = max(res, mx[u][0]);
    return res;
}

// ca hai di len
bool Solve1(Query a, Query b) {
    if (h[a.e] > h[b.e])
        swap(a, b);
    else if (h[a.s] < h[b.s])
        swap(a, b);
    if (!isPar(a.e, b.e))
        return 0;
    if (!isPar(a.s, b.s))
        return 0;
    if (a.s == b.e) 
        return 0;
    int node = jump(a.s, b.s);
    int _t1 = a.t + dis[a.s] - dis[node], _t2 = b.t + dis[b.s] - dis[node];
    return (abs(_t2 - _t1) < get(a.s, b.e));
}

// ca hai di xuong
bool Solve2(Query a, Query b) {
    if (h[a.s] > h[b.s])
        swap(a, b);
    else if (h[a.e] > h[b.e])
        swap(a, b);
    if (!isPar(a.s, b.s))
        return 0;
    if (!isPar(b.s, a.e))
        return 0;
    if (a.e == b.s || (a.s == b.s && !isPar(a.e, b.e)))
        return 0;
    int _t1 = a.t + dis[b.s] - dis[a.s], _t2 = b.t;
    return (abs(_t1 - _t2) < get(a.e, b.s));
}

bool check(int u, ll w) {
    for (int j = N; j >= 0; j--)
        if (sum[u][j] <= w)
            w -= sum[u][j];
    return (w != 0);
}

// mot len mot xuong
bool Solve3(Query a, Query b) {
    if (h[a.s] > h[b.s])
        swap(a, b);
    if (!isPar(a.s, b.s))
        return 0;
    if (!isPar(b.e, a.e))
        return 0;
    if (a.e == b.e)
        return 0;
    int node = jump(a.e, b.s);
    int L = dis[node] - dis[b.e];
    int _t1 = a.t + dis[b.e] - dis[a.s], _t2 = b.t + dis[b.s] - dis[node];
    if (abs(_t1 - _t2) >= L) return 0;
    int t = (L + _t1 + _t2) / 2;
    return check(node, t);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    int o; cin >> o;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    dfs(1, 0);
    tin[0] = 0, tout[0] = n + 1;
    vector<Query> myVec1, myVec2;
    Query a(2, 7, 7, 0); Query b(5, 1, 2, 1);
    // Query a(5, 1, 2, 1); Query b(6, 2, 6, 1);
    // Query a(5, 1, 2, 1); Query b(7, 1, 2, 1);
    // Query a(8, 2, 1, 1); Query b(1, 7, 6, 0);
    return cout << Solve3(a, b), 0;
    while (q--) {
        Query a, b;
        cin >> a.s >> a.e >> a.t >> b.s >> b.e >> b.t;
        int p = lca(a.s, a.e);
        myVec1.clear(); myVec2.clear();
        if (a.s != p)
            myVec1.pb({a.s, p, a.t, 1});
        if (a.e != p) 
            myVec1.pb({p, a.e, a.t + dis[a.s] - dis[p], 0});
        p = lca(b.s, b.e);
        if (b.s != p)
            myVec2.pb({b.s, p, b.t, 1});
        if (b.e != p)
            myVec2.pb({p, b.e, b.t + dis[b.s] - dis[p], 0});
        bool res = 0;
        for (auto a : myVec1)
            for (auto b : myVec2) {
                if (a.dire && b.dire)
                    res |= Solve1(a, b);
                else if (a.dire && b.dire)
                    res |= Solve2(a, b);
                else
                    res |= Solve3(a, b);
                // if (res) clog << db(a.s) << db(a.e) << db(a.t) << db(b.s) << db(b.e) << db(b.t) << '\n';
            }
        cout << (res ? 'Y' : 'N');
    }
}
