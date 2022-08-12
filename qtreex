#include <bits/stdc++.h>
#define fi first
#define se second
// #define int long long
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const ll mod = 1e9 + 7;
const int maxn = 1e4 + 4;
const int INF = 1e9;
const int N = 18;

struct Node {
    int min, max, lazy, change;
} t[4 * maxn];

int n, par[maxn], sz[maxn], up[maxn][20], h[maxn], pos[maxn], head[maxn], chain[maxn], vals[maxn];
vector<pair<int,int>> adj[maxn];
tuple<int,int,int> edges[maxn];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int j = 1; j <= N; j++)
        up[u][j] = up[up[u][j - 1]][j - 1];
    par[u] = p;
    sz[u] = 1;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
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
    chain[u] = chain[0];
    pos[u] = ++pos[0];
    int mx = 0;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == par[u]) continue;
        if (sz[v] > sz[mx])
            mx = v;
    }
    if (mx != 0) hld(mx);
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == par[u] || v == mx) continue;
        chain[0]++;
        hld(v);
    }
}

void build(int v, int l, int r) {
    if (l == r) {
        t[v].min = t[v].max = vals[l];
        t[v].change = t[v].lazy = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m + 1, r);
    t[v].max = max(t[2 * v].max, t[2 * v + 1].max);
    t[v].min = min(t[2 * v].min, t[2 * v + 1].min);
}

void pushdown(int v) {
    if (t[v].lazy != 0) {
        t[2 * v].lazy = !(t[2 * v].lazy);
        t[2 * v + 1].lazy = !(t[2 * v + 1].lazy);
        swap(t[v].min, t[v].max);
        t[v].min *= -1; t[v].max *= -1;
        t[v].lazy = 0;
    }
}

void update_val(int v, int l, int r, int pos, int val) {
    if (l == r) {
        t[v].min = t[v].max = val;
        t[v].lazy = 0;
        return;
    }
    pushdown(v);
    int m = (l + r) / 2;
    if (pos <= m) update_val(2 * v, l, m, pos, val);
    else update_val(2 * v + 1, m + 1, r, pos, val);
    t[v].max = max(t[2 * v].max, t[2 * v + 1].max);
    t[v].min = min(t[2 * v].min, t[2 * v + 1].min);
}

void update_range(int v, int tl, int tr, int l, int r) {
    if (l != r) pushdown(v);
    if (tl > r || tr < l) return;
    // clog << db(v) << db(tl) << db(tr) << db(l) << db(r) << '\n';
    if (tl >= l && tr <= r) {
        t[v].lazy = 1;
        swap(t[v].min, t[v].max);
        t[v].min *= -1; t[v].max *= -1;
        t[2 * v].lazy = !(t[2 * v].lazy);
        t[2 * v + 1].lazy = !(t[2 * v + 1].lazy);
        return;
    }
    int m = (tl + tr) / 2;
    update_range(2 * v, tl, m, l, r);
    update_range(2 * v + 1, m + 1, tr, l, r);
    t[v].max = max(t[2 * v].max, t[2 * v + 1].max);
    t[v].min = min(t[2 * v].min, t[2 * v + 1].min);
}

int get(int v, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return -INF;
    if (l != r) pushdown(v);
    if (tl >= l && tr <= r) return t[v].max;
    int m = (tl + tr) / 2;
    int res1 = get(2 * v, tl, m, l, r);
    int res2 = get(2 * v + 1, m + 1, tr, l, r);
    return max(res1, res2);
}

void hld_update(int u, int p) {
    int uchain = chain[u], pchain = chain[p];
    while (1) {
        if (uchain == pchain) {
            update_range(1, 1, n, pos[p], pos[u]);
            break;
        }
        update_range(1, 1, n, pos[head[uchain]], pos[u]);
        u = par[head[uchain]];
        uchain = chain[u];
    }
}


int hld_query(int u, int p) {
    int res = -INF;
    int uchain = chain[u], pchain = chain[p];
    while (1) {
        if (uchain == pchain) {
            res = max(res, get(1, 1, n, pos[p], pos[u]));
            break;
        }
        res = max(res, get(1, 1, n, pos[head[uchain]], pos[u]));
        u = par[head[uchain]];
        uchain = chain[u];
    }
    return res;
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        adj[i].clear();
    }
    for (int i = 1; i <= 4 * n; i++)
        t[i].min = t[i].max = t[i].lazy = 0;
    chain[0] = pos[0] = 0;
}

void Solve() {
    cin >> n;
    init(n);
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        edges[i] = {u, v, w};
    }   
    dfs(1, 0);
    ++chain[0];
    hld(1);
    for (int i = 1; i < n; i++) {
        int u, v, w; tie(u, v, w) = edges[i];
        if (u == par[v]) swap(u, v);
        vals[pos[u]] = w;
    }
    build(1, 1, n);
    string s = "";
    while (s != "DONE") {
        cin >> s;
        if (s == "CHANGE") {
            int i, val; cin >> i >> val;
            int u, v, w; tie(u, v, w) = edges[i];
            if (u == par[v]) swap(u, v);
            update_val(1, 1, n, pos[u], val);
            edges[i] = {u, v, val};
        }
        if (s == "NEGATE") {
            int u, v; cin >> u >> v;
            int p = lca(u, v);
            if (u != p) hld_update(u, jump(u, h[u] - h[p] - 1));
            if (v != p) hld_update(v, jump(v, h[v] - h[p] - 1));
        }
        if (s == "QUERY") {
            int u, v; cin >> u >> v;
            if (u == v) {
                cout << 0 << '\n'; 
                continue;
            }
            int p = lca(u, v);
            int L = (u == p ? -INF : hld_query(u, jump(u, h[u] - h[p] - 1)));
            int R = (v == p ? -INF : hld_query(v, jump(v, h[v] - h[p] - 1)));
            cout << max(L, R) << '\n';
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    int t; cin >> t;
    while (t--) {
        Solve();
    }
}
