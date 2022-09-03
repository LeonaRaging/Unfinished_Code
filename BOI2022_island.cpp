#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 2e5 + 4;
const int INF = 1e9;

int n, m, a[maxn], vis[maxn];
vector<int> adj[maxn], nodes[maxn], vals, myVec[maxn];

struct DisjointSet {
    vector<int> par, Rank;
    DisjointSet(int n) {
        par.resize(n + 4); Rank.resize(n + 4);
        for (int i = 1; i <= n; i++)
            par[i] = i, Rank[i] = vals[a[i]], myVec[i].pb(i);
    }
    int find(int x) {
        if (x != par[x]) par[x] = find(par[x]);
        return par[x];
    }
    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return u;
        if (Rank[u] < Rank[v])
            swap(u, v);
        Rank[u] += Rank[v];
        par[v] = u;
        if (myVec[u].size() < myVec[v].size())
            swap(myVec[u], myVec[v]);
        for (auto it : myVec[v]) {
            vis[it] = 1;
            myVec[u].pb(it);
        }
        myVec[v].clear();
        return 1;
    }
};

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vals.pb(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        nodes[a[i]].pb(i);
    }
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        if (a[u] == a[v]) {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        else {
            if (a[u] < a[v]) swap(u, v);
            adj[u].pb(v);
        }
    }
    bitset<maxn> res;
    res.set();
    DisjointSet Dsu(n);
    for (int i = 0; i < (vals.size()); i++) {
        for (int u : nodes[i]) {
            vis[u] = 1;
            for (int v : adj[u]) {
                if (vis[v]) {
                    v = Dsu.find(v);
                    if (Dsu.Rank[v] < vals[a[u]]) {
                        for (int node : myVec[v]) {
                            res[node] = 0;
                        }
                        myVec[v].clear();
                    }
                }
                Dsu.join(u, v);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << res[i];
}
