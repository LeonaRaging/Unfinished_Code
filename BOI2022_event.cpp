#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 2e5 + 4;
const int INF = 1e9;
const int N = 18;

pair<int,int> a[maxn];

struct seg_tree {
    vector<int> t;
    seg_tree() {
        t.resize(4 * maxn);
    }
    int MIN(int i, int j) {
        return (a[i].fi < a[j].fi ? i : j);
    }
    void update(int pos, int val, int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r) {
            t[v] = MIN(t[v], val);
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) update(pos, val, 2 * v, l, m);
        else update(pos, val, 2 * v + 1, m + 1, r);
        t[v] = MIN(t[2 * v], t[2 * v + 1]);
    }
    int get(int l, int r, int v = 1, int tl = 1, int tr = maxn - 1) {
        if (tl > r || tr < l) return 0;
        if (tl >= l && tr <= r) return t[v];
        int m = (tl + tr) / 2;
        int L = get(l, r, 2 * v, tl, m);
        int R = get(l, r, 2 * v + 1, m + 1, tr);
        return MIN(L, R);
    }
} IT;

int n, q, pre[maxn][20];
vector<int> vals;
vector<pair<int,int>> R[maxn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int l, r; cin >> l >> r;
        a[i] = {l, r};
        vals.pb(l); vals.pb(r);        
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    a[0] = {INF, INF};
    for (int i = 1; i <= n; i++) {
        a[i].fi = lower_bound(vals.begin(), vals.end(), a[i].fi) - vals.begin() + 1;
        a[i].se = lower_bound(vals.begin(), vals.end(), a[i].se) - vals.begin() + 1;
        R[a[i].se].pb({a[i].fi, i});
    }
    int sz = vals.size();
    for (int i = 1; i <= sz; i++) {
        sort(R[i].begin(), R[i].end());
        for (auto it : R[i]) {
            pre[it.se][0] = IT.get(it.fi, i);
            IT.update(i, it.se);
        }
    }
    for (int j = 1; j <= N; j++)
        for (int i = n; i >= 1; i--)
            pre[i][j] = pre[pre[i][j - 1]][j - 1];
    a[0] = {-INF, -INF};
    while (q--) {
        int s, t; cin >> s >> t;
        if (s == t) {
            cout << "0\n";
            continue;
        }
        int ans = 0;
        for (int j = N; j >= 0; j--)
            if (a[pre[t][j]].fi > a[s].se && pre[t][j] != s) {
                ans += (1 << j);
                t = pre[t][j];
            }
        if (a[t].se < a[s].se) ans = -1;
        else if (a[t].fi > a[s].se) {
            if (!pre[t][0]) ans = -1;
            else ans++;
        }
        if (ans == -1) cout << "impossible";
        else cout << ans + 1;
        cout << '\n';
    }
}
