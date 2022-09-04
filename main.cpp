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

struct Query {
    char type;
    int u, v;
};

int n, k, leave[maxn], join[maxn], reach[maxn], res[maxn];
set<pair<int,int>> adj[maxn];
set<pair<int,int>> query1[maxn];
map<int,bool> L, cur;

void dfs(int u, int p, int pre, int f1, int f2) {
    auto i = query1[u].begin();
    while (i != query1[u].end()) {
        auto it = L.find(i->fi);
        if (it == L.end()) {
            i++;
            continue;
        }
        int v = it->fi;
        if (join[v] > leave[u] && reach[u] <= i->se)
            res[i->se] = -1;
        else res[i->se] = -2;
        i = query1[u].erase(i);
    }
    cur[u] = 1;
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == p) continue;
        if (w > pre && f1) {
            f2 = 0;
            join[v] = w; 
        }
        if (w < pre && f2) {
            f1 = 0;
            reach[v] = w, leave[v] = leave[u];
        }
        if (f1 == 0) join[v] = -1;
        if (f2 == 0) reach[v] = leave[v] = -1;
        dfs(v, u, w, f1, f2);
    }
}

void Solve(int u) {
    L.clear();
    for (auto it : adj[u]) {
        cur.clear();
        int v, w; tie(v, w) = it;   
        join[v] = reach[v] = leave[v] = w;
        dfs(v, u, w, 1, 1);
        for (auto it : cur)
            L[it.fi] = 1;
    }
}

struct Centroid_Decomposition {
    int sz[maxn];
    int dfs(int u, int p) {
        sz[u] = 1;
        for (auto it : adj[u])
            if (it.fi != p)
                sz[u] += dfs(it.fi, u);
        return sz[u];
    }
    int Centroid(int u, int p, int tot) {
        for (auto it : adj[u])
            if (it.fi != p && sz[it.fi] > tot / 2)
                return Centroid(it.fi, u, tot);
        return u;
    }
    void build(int u) {
        int tot = dfs(u, 0);
        int c = Centroid(u, 0, tot);
        Solve(c);
        clog << c << ' ' << tot << '\n';
        vector<pair<int,int>> del(adj[c].begin(), adj[c].end());
        for (auto it : del) {
            adj[c].erase(it);
            adj[it.fi].erase(adj[it.fi].find({c, it.se}));
            build(it.fi);
        }
    }
} Cen;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n + k - 1; i++) {
        char type; int u; cin >> type >> u;
        if (type == 'S') {
            int v; cin >> v;
            adj[u].insert({v, i});
            adj[v].insert({u, i});
        }
        else if (type == 'Q') {
            int v; cin >> v;
            query1[u].insert({v, i});
        }
    }
    Cen.build(1);
    cout << res[4];
}
