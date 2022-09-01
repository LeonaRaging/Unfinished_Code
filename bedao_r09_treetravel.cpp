#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 4;
const int INF = 1e9;

int add(int a, int b) {
    a += b; if (a > mod) a -= mod;
    return a;
}

struct seg_tree {
    vector<int> t;
    seg_tree() {
        t.resize(4 * maxn);
    }
    void update(int pos, int val, int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r) {
            t[v] += val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) update(pos, val, 2 * v, l, m);
        else update(pos, val, 2 * v + 1, m + 1, r);
        t[v] = add(t[2 * v], t[2 * v + 1]);
    }
    int get(int l, int r, int v = 1, int tl = 1, int tr = maxn - 1) {
        if (tl > r || tr < l) return 0;
        if (tl >= l && tr <= r) return t[v];
        int m = (tl + tr) / 2;
        int L = get(l, r, 2 * v, tl, m);
        int R = get(l, r, 2 * v + 1, m + 1, tr);
        return add(L, R);
    }
} IT;

int n, root, par[maxn], tin[maxn], tout[maxn], res[maxn], a[maxn];
vector<int> adj[maxn];

void dfs(int u) {
    tin[u] = ++tin[0];
    for (int v : adj[u])
        dfs(v);
    tout[u] = tin[0];
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> par[i];
        if (par[i] == 0) root = i;
        else adj[par[i]].pb(i);
        a[i] = 1;
    }
    dfs(root);
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        a[u] = add(a[u], IT.get(tin[u], tout[u]));
        if (par[u])
            IT.update(tin[par[u]], a[u]);
        res[u] = a[u];
    }
    for (int i = 1; i <= n; i++)
        cout << res[i] << ' ';
}
