#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const ll mod = 1e9 + 7;
const int maxn = 5e3 + 4;
const int INF = 1e9;
const int N = 18;

struct Query {
    int u, v, val;
    bool operator < (const Query &other) {
        return val < other.val;
    }
};

struct Node {
    int min, lazy;
} t[4 * maxn];

int n, sz[maxn], h[maxn], up[maxn][20], par[maxn], pos[maxn], chain[maxn], head[maxn];
vector<int> adj[maxn];
vector<pair<int,int>> edges;
vector<Query> queries;

void dfs(int u, int p) {
    up[u][0] = p;
    for (int j = 1; j <= N; j++)
        up[u][j] = up[up[u][j - 1]][j - 1];
    par[u] = p;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        h[v] = h[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    int k = h[u] - h[v];
    for (int j = N; j >= 0; j--)
        if (k >> j & 1)
            u = up[u][j];
    if (u == v) return u;
    for (int j = N; j >= 0; j--)
        if (up[u][j] != up[v][j])
            u = up[u][j], v = up[v][j];
    return up[u][0];
}

int jump(int u, int k) {
    for (int j = N; j >= 0; j--)
        if (k >> j & 1)
            u = up[u][j];
    return u;
}

void hld(int u) {
    if (head[chain[0]] == 0) head[chain[0]] = u;
    pos[u] = ++pos[0];
    chain[u] = chain[0];
    int mx = 0;
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        if (sz[v] > sz[mx])
            mx = v;
    }
    if (mx != 0) hld(mx);
    for (int v : adj[u])
        if (v != par[u] && v != mx) {
            chain[0]++;
            hld(v);
        }
}

void pushdown(int v) {
    int val = t[v].lazy;
    t[2 * v].min = t[2 * v].lazy = val;
    t[2 * v + 1].min = t[2 * v + 1].lazy = val;
    t[v].lazy = 0;
}

void update(int v, int tl, int tr, int l, int r, int val) {
    if (tl > r || tr < l) return;
    if (tl >= l && tr <= r) {
        t[v].min = val;
        t[v].lazy = val;
        return;
    }
    if (t[v].lazy != 0) pushdown(v);
    int m = (tl + tr) / 2;
    update(2 * v, tl, m, l, r, val);
    update(2 * v + 1, m + 1, tr, l, r, val);
    t[v].min = min(t[2 * v].min, t[2 * v + 1].min);
}

void hld_update(int u, int p, int val) {
    int uchain = chain[u], pchain = chain[p];
    while (1) {
        if (uchain == pchain) {
            int k = h[u] - h[p];
            update(1, 1, n, pos[jump(u, k - 1)], pos[u], val);
            break;
        }
        update(1, 1, n, pos[head[uchain]], pos[u], val);
        u = par[head[uchain]];
        uchain = chain[u];
    }
}

int get(int v, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return INF;
    if (tl >= l && tr <= r) return t[v].min;
    if (t[v].lazy != 0) pushdown(v);
    int m = (tl + tr) / 2;
    int L = get(2 * v, tl, m, l, r);
    int R = get(2 * v + 1, m + 1, tr, l, r);
    return min(L, R);
}

int hld_get(int u, int p) {
    int res = INF;
    int uchain = chain[u], pchain = chain[p];
    while (1) {
        if (uchain == pchain) {
            int k = h[u] - h[p];
            res = min(res, get(1, 1, n, pos[jump(u, k - 1)], pos[u]));
            break;
        }
        res = min(res, get(1, 1, n, pos[head[uchain]], pos[u]));
        u = par[head[uchain]];
        uchain = chain[u];
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        edges.pb({u, v});
    }
    dfs(1, 0);
    chain[0] = 1;
    hld(1);
    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        int u, v, val; cin >> u >> v >> val;
        queries.pb({u, v, val});
    }
    sort(queries.begin(), queries.end());
    for (int i = 1; i <= 4 * n; i++)
        t[i].min = INF, t[i].lazy = 0;
    for (auto it : queries) {
        int u = it.u, v = it.v, val = it.val;
        int p = lca(u, v);
        hld_update(u, p, val);
        hld_update(v, p, val);
    }
    for (auto it : queries) {
        int u = it.u, v = it.v, val = it.val;
        int p = lca(u, v);
        int x = min(hld_get(u, p), hld_get(v, p));
        // clog << u << ' ' << v << ' ' << x << '\n';
        if (x != val) return cout << -1, 0;
    }
    for (auto it : edges) {
        int u, v; tie(u, v) = it;
        if (v != par[u]) swap(u, v);
        int res = hld_get(u, v);
        cout << (res == INF ? 1 : res) << ' ';   
    }
    // clog << db(pos[2]);
}
