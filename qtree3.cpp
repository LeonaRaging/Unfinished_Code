#include<bits/stdc++.h>
#define ll long long
#define fi second
#define se first
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
#define mp make_pair
using namespace std;
const int maxn = 1e5 + 4;
const int INF = 1e9;
const ll mod = 1e9 + 7;
const int N = 1e4 + 3;

int n, q, pos[maxn], chain[maxn], head[maxn], node[maxn], t[4 * maxn], par[maxn], sz[maxn];
vector<int> adj[maxn];

void dfs(int u, int p) {
    sz[u] = 1;
    par[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void hld(int u) {
    if (head[chain[0]] == 0) head[chain[0]] = u;
    chain[u] = chain[0];
    pos[u] = ++pos[0];
    node[pos[0]] = u;
    int mx = 0;
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        if (sz[v] > sz[mx]) mx = v;
    }
    if (mx != 0) hld(mx);
    for (int v : adj[u])
        if (v != par[u] && v != mx) {
            chain[0]++;
            hld(v);
        }
}

void update(int v, int l, int r, int pos, int val) {
    if (l == r) {
        t[v] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m) update(2 * v, l, m, pos, val);
    else update(2 * v + 1, m + 1, r, pos, val);
    t[v] = min(t[2 * v], t[2 * v + 1]);
}

int get(int v, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return INF;
    if (tl >= l && tr <= r) return t[v];
    int m = (tl + tr) / 2;
    int L = get(2 * v, tl, m, l, r);
    int R = get(2 * v + 1, m + 1, tr, l, r);
    return min(L, R);
}

int hld_get(int u, int p) {
    int uchain = chain[u], pchain = chain[p];
    int res = INF;
    while (1) {
        if (uchain == pchain) {
            res = min(res, get(1, 1, n, pos[p], pos[u]));
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
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, 0);
    ++chain[0];
    hld(1);
    for (int i = 1; i <= 4 * n; i++)
        t[i] = INF;
    for (int i = 1; i <= q; i++) {
        int type, u; cin >> type >> u;
        int res = hld_get(u, 1);
        if (type == 0) {
            if (res == INF) update(1, 1, n, pos[u], pos[u]);
            else update(1, 1, n, pos[u], INF);
        }
        else cout << (res == INF ? -1 : node[res]) << '\n';
    }
}
