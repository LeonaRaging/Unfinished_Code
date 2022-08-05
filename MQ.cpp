#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const int maxn = 1e5 + 4;
const int INF = INT_MAX;
const ll mod = 1e9 + 7;
const int N = 205;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) {
        return w < other.w;
    }
};

struct Dsu {
    vector<int> par, Rank;
    void init(int n) {
        par.resize(n + 1);
        Rank.resize(n + 1);
        for (int i = 1; i <= n; i++)
            par[i] = i, Rank[i] = 1;
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
} Ds;

int n, m, q;
vector<Edge> edges, tree_edges;
set<pair<int,int>> zero_edges;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("MQ.INP", "r", stdin);
    freopen("MQ.OUT", "w", stdout);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.pb({u, v, w});
    }
    sort(edges.begin(), edges.end());
    Ds.init(n);
    for (auto it : edges) {
        int u = it.u, v = it.v, w = it.w;
        if (Ds.join(u, v))
            tree_edges.pb(it);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v; cin >> u >> v;
            zero_edges.insert({u, v});
        }
        else if (type == 2) {
            int u, v; cin >> u >> v;
            zero_edges.erase({u, v});
        }
        else {
            ll res = 0;
            Ds.init(n);
            for (auto it : zero_edges)
                Ds.join(it.fi, it.se);
            for (auto it : tree_edges) {
                int u = it.u, v = it.v; ll w = it.w;
                if (Ds.join(u, v)) res += w;
            }
            cout << res << '\n';
        }
    }
}
