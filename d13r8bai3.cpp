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
const int N = 16;

int n, used[maxn], par[maxn], up[maxn][20], h[maxn];
vector<int> adj[maxn];
map<int,int> mp[maxn];
set<int> mySet;

struct Centroid_Decomposition {
    int sz[maxn];
    int dfs(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u])
            if (v != p && !used[v]) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        return sz[u];
    }
    int Centroid(int u, int p, int tot) {
        for (int v : adj[u])
            if (v != p && !used[v] && sz[v] > tot / 2)
                return Centroid(v, u, tot);
        return u;
    }
    void build(int u, int p) {
        int c = Centroid(u, p, dfs(u, p));
        par[c] = p;
        used[c] = 1;
        for (int v : adj[c])
            if (v != p && !used[v])
                build(v, c);
    }
} Cen;

void dfs(int u, int p) {
    up[u][0] = p;
    for (int j = 1; j <= N; j++)
        up[u][j] = up[up[u][j - 1]][j - 1];
    for (int v : adj[u])
        if (v != p) {
            h[v] = h[u] + 1;
            dfs(v, u);
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

int dis(int u, int v) {
    return h[u] + h[v] - 2 * h[lca(u, v)];
}

void add(int u) {
    int v = u;
    while (v) {
        int d = dis(u, v);
        mp[v][d]++;
        v = par[v];
    }
}

void rev(int u) {
    int v = u;
    while (v) {
        int d = dis(u, v);
        mp[v][d]--;
        if (mp[v][d] == 0)
            mp[v].erase(mp[v].find(d));
        v = par[v];
    }
}

void query(int u) {
    pair<int,int> ans = {INF, 0};
    int v = u;
    while (v) {
        auto it = mp[v].begin();
        if (it != mp[v].end()) {
            int d = dis(u, v);
            if (it->fi + d < ans.fi)
                ans = {it->fi + d, it->se};
            else if (it->fi + d == ans.fi)
                ans.se += it->se;
        }
        v = par[v];
    }
    cout << ans.fi << ' ' << ans.se << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    int m, q; cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, 0);
    Cen.build(1, 0);
    for (int i = 1; i <= m; i++) {
        int u; cin >> u;
        if (mySet.find(u) == mySet.end()) {
            mySet.insert(u);
            add(u);
        }
        else {
            mySet.erase(u);
            rev(u);
        }
    }
    for (int i = 1; i <= q; i++) {
        int type, u; cin >> type >> u;
        if (type == 1) {
            if (mySet.find(u) == mySet.end()) {
                mySet.insert(u);
                add(u);
            }
            else {
                mySet.erase(u);
                rev(u);
            }       
        }
        else query(u);
    }
}
