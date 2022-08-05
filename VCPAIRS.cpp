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

ll res;
int n, m, par[maxn], Rank[maxn];
map<int,int> color[maxn];

int find(int x) {
    if (x != par[x]) par[x] = find(par[x]);
    return par[x];
}

bool join(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return 0;
    if (Rank[u] < Rank[v]) swap(u, v);
    Rank[u] += Rank[v];
    for (auto x : color[v]) {
        res -= 1LL * color[u][x.fi] * (color[u][x.fi] - 1) / 2;
        res -= 1LL * color[v][x.fi] * (color[v][x.fi] - 1) / 2;
        color[u][x.fi] += x.se;
        res += 1LL * color[u][x.fi] * (color[u][x.fi] - 1) / 2;
    }
    color[v].clear();
    par[v] = u;
    return 1;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("VCPAIRS.INP", "r", stdin);
    freopen("VCPAIRS.OUT", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        color[i][x] = 1;
        Rank[i] = 1, par[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        join(u, v);
        cout << res << '\n';
    }
}
