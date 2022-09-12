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

int n, sz[maxn], h[maxn];
set<int> adj[maxn];
ll a[maxn], res, L[2], cur[2];

void add(ll &a, ll b) {
    a += b; if (a > mod) a -= mod;
}

void dfs1(int u, int p) {
    h[u] = h[p] + 1;
    L[h[u]]++;
    sz[u] = 1;
    for (int v : adj[u])
        if (v != p) {
            dfs1(v, u);
            sz[u] += sz[v];
        }
}

void reset(int u, int p, int val) {
    L[h[u]] += val;
    for (int v : adj[u])
        if (v != p)
            reset(v, u, val);
}

void dfs2(int u, int p) {
    cur[L[u]]++;
    add(res, ((h[u] & 1 ? -1 : 1) * L[0] + mod) % mod * a[u] % mod * sz[u] % mod);
    add(res, ((h[u] & 1 ? 1 : -1) * L[1] + mod) % mod * a[u] % mod * sz[u] % mod);
    for (int v : adj[u])
        if (v != p)
            dfs2(v, u);
}

void Solve(int c) {
    L[0] = 1; L[1] = 0;
    dfs1(c, 0);
    for (int v : adj[c]) {
        cur[0] = cur[1] = 0;
        reset(v, c, -1);
        dfs2(v, c);
        reset(v, c, 1);
        add(res, L[0] * a[c] % mod * (sz[c] - sz[v]) % mod * sz[v] % mod);
        add(res, ((-L[1] + mod) % mod) * a[c] % mod * (sz[c] - sz[v]) % mod * sz[v] % mod);
    }
}

struct Centroid_Decomposition {
    int sz[maxn];
    int dfs(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u])
            if (v != p)
                sz[u] += dfs(v, u);
        return sz[u];
    }
    int Centroid(int u, int p, int tot) {
        for (int v : adj[u])
            if (v != p && sz[v] > tot / 2)
                return Centroid(v, u, tot);
        return u;
    }
    void build(int u) {
        int c = Centroid(u, 0, dfs(1, 0));
        Solve(c);
        vector<int> del(adj[c].begin(), adj[c].end());
        for (int v : del) {
            adj[c].erase(v);
            adj[v].erase(c);
            build(v);
        }
    }
} Cen;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = (a[i] + mod) % mod;
    }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    Cen.build(1);
    cout << res;
}
