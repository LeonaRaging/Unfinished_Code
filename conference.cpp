#include<bits/stdc++.h>
using namespace std;

#define pb push_back

const int maxn = 1e6 + 4;

void coding() {
    freopen("inputf.in", "r", stdin);
    freopen("outputf.out", "w", stdout);
    freopen("log.out", "w", stderr);
}

void fre() {
    freopen("conference.IN", "r", stdin);
    freopen("conference.OUT", "w", stdout);
}

int n, m, k, res[maxn], id[maxn], pos[maxn], used[maxn], has[maxn];
vector<pair<int,int>> edges;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    coding();
//    fre();
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        edges.pb({u, v});
    }
    memset(res, -1, sizeof res);
    memset(id, -1, sizeof id);
    memset(pos, 63, sizeof pos);
    for (int i = m - 1; i >= 0; i--) {
        int u, v; tie(u, v) = edges[i];
        if (u > v) swap(u, v);
        if (u <= k && v > k) {
            if (res[u] == -1) {
                res[u] = i + 1;
                id[u] = v;
            }
            has[u] = v;
        }
        if (u <= k && v <= k) {
            if (res[u] == -1 && res[v] != -1)
                res[u] = i + 1, id[u] = has[v];
            if (res[u] != -1 && res[v] == -1)
                res[v] = i + 1, id[v] = has[u];
            int x = has[u], y = has[v];
            has[u] = has[v] = (pos[x] < pos[y] ? x : y);
        }
    }
    memset(has, 0, sizeof has);
    for (int i = 0; i < m; i++) {
        int u, v; tie(u, v) = edges[i];
        if (u > v) swap(u, v);
        if (res[u] == i + 1) has[u] = 1;
        if (res[v] == i + 1) has[v] = 1;
        if (u <= k && v > k) {
            if (has[u]) used[v] = 1;
            if (used[v]) has[u] = 1;
        }
        if (u <= k && v <= k)
            has[u] = has[v] = max(has[u], has[v]);
        if (u > k && v > k)
            used[u] = used[v] = max(used[u], used[v]);
    }
    for (int i = 1; i <= k; i++)
        cout << res[i] << ' ';
    cout << '\n';
    vector<int> ans;
    for (int i = k + 1; i <= n; i++)
        if (used[i]) ans.pb(i);
    cout << ans.size() << ' ';
    for (int x : ans) cout << x << ' ';
    cout << '\n';
    for (int i = 1; i <= k; i++)
        cout << id[i] << ' ';
}
