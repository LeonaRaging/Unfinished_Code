#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 5e5 + 4;
const ll INF = 1e9;

ll tot, h[maxn], far[maxn];
int n, k, a[maxn];
vector<pair<int,int>> adj[maxn];
pair<ll,int> dis[maxn], mx[maxn][2];

int Find(int u, int p) {
    bool flag = 0;
    for (auto it : adj[u]) {
        if (it.fi == p) continue;
        if (Find(it.fi, u)) {
            tot += it.se;
            a[u] = flag = 1;
        }
    }
    if (a[u]) flag =  1;
    return flag;
}

ll dfs(int u, int p) {
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == p || !a[v]) continue;
        ll d = dfs(v, u) + w;
        mx[u][1] = max(mx[u][1], make_pair(d, v));
        if (mx[u][1] > mx[u][0]) swap(mx[u][0], mx[u][1]);
    }  
    return mx[u][0].fi;
}

void Calc(int u, int p, ll cur) {
    far[u] = max(cur, mx[u][0].fi);
    for (auto it : adj[u]) {
        int v, w; tie(v, w) = it;
        if (v == p || !a[v]) continue;
        if (v != mx[u][0].se) Calc(v, u, w + max(cur, mx[u][0].fi));
        else Calc(v, u, w + max(cur, mx[u][1].fi));
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    int u;
    for (int i = 1; i <= n; i++)
        dis[i] = {INF, INF};
    for (int i = 1; i <= k; i++) {
        cin >> u, a[u] = 1;
    }
    Find(u, 0);
    queue<pair<pair<ll,int>,int>> q;
    for (int i = 1; i <= n; i++) 
        if (a[i]) {
            bool flag = 0;
            for (auto it : adj[i])
                if (!a[it.fi]) flag = 1;
            dis[i] = {0, i};
            if (flag) q.push({dis[i], i});
        }
    while (!q.empty()) {
        auto d = q.front().fi; int u = q.front().se; q.pop();
        if (dis[u] != d) continue;
        for (auto it : adj[u]) {
            int v, w; tie(v, w) = it;
            if (dis[u].fi + w < dis[v].fi) {
                dis[v].fi = dis[u].fi + w;
                dis[v].se = dis[u].se;
                q.push({dis[v], v});
            }
        }
    }
    dfs(u, 0);    
    Calc(u, 0, 0);
    for (int i = 1; i <= n; i++)
        cout << dis[i].fi + 2 * tot - far[dis[i].se] << '\n';
}
