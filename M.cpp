#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 3e5 + 4;
const int INF = 1e9;

struct Edge {
    int u, v;
    int get(int x) {
        return u ^ v ^ x;
    }
};

int n, m, num, par[maxn], h[maxn], nxt[maxn], res[maxn];
bool good[maxn];
vector<Edge> edges;
vector<int> adj[maxn], myVec;


int find(int x) {
    if (x != nxt[x]) nxt[x] = find(nxt[x]);
    return nxt[x];
}

void dfs(int u, int p) {
    nxt[u] = u;
    for (int i : adj[u]) {
        int v = edges[i].get(u);
        if (v != p) {
            par[v] = i;
            h[v] = h[u] + 1;
            dfs(v, u);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> m;
    edges.pb({0, 0});
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        edges.pb({u, v});
    }
    for (int i = 1; i < n; i++) {
        int idx; cin >> idx;
        good[idx] = 1;
        int u = edges[idx].u, v = edges[idx].v;
        adj[u].pb(idx);
        adj[v].pb(idx);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int u = edges[i].u, v = edges[i].v;
        u = find(u); v = find(v);
        myVec.clear();
        while (u != v) {
            if (h[u] < h[v])
                swap(u, v);
            myVec.pb(par[u]);
            nxt[u] = edges[par[u]].get(u);
            u = find(u);
        }
        sort(myVec.begin(), myVec.end());
        for (auto idx : myVec) {
            res[idx] = ++num;
        }
        if (!good[i])
            res[i] = ++num;
    }
    for (int i = 1; i <= m; i++)
        cout << res[i] << ' ';
}
