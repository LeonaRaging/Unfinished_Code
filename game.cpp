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

int n, q, a[maxn];
map<int,vector<int>> mp;

struct seg_tree {
    vector<int> t, lazy;
    seg_tree() {
        t.resize(4 * maxn);
        lazy.resize(4 * maxn);
    }
    void build(int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r ) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
    }
    void pushdown(int v) {
        int val = lazy[v];
        t[2 * v] += val;
        t[2 * v + 1] += val;
        lazy[2 * v] += val;
        lazy[2 * v + 1] += val;
        lazy[v] = 0;
    }
    void update(int l, int r, int val, int v = 1, int tl = 1, int tr = maxn - 1) {
        if (tl > r || tr < l) return;
        if (tl >= l && tr <= r) {
            t[v] += val;
            lazy[v] += val;
            return;
        }
        pushdown(v);
        int m = (tl + tr) / 2;
        update(l, r, val, 2 * v, tl, m);
        update(l, r, val, 2 * v + 1, m + 1, tr);
    }
    int get(int pos, int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r)
            return t[v];
        pushdown(v);
        int m = (l + r) / 2;
        if (pos <= m) return get(pos, 2 * v, l, m);
        return get(pos, 2 * v + 1, m + 1, r);
    }
} IT;

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

int rd(int l, int r) {
    return l + mt() % (r - l + 1);
}

int get(int x, int l, int r) {
    l = lower_bound(mp[x].begin(), mp[x].end(), l) - mp[x].begin();
    r = lower_bound(mp[x].begin(), mp[x].end(), r) - mp[x].begin();
    return r - l + 1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]].pb(i);
    }
    IT.build();
    while (q--) {
        int type, l, r; cin >> type >> l >> r;
        if (type == 1) {
            int x; cin >> x;
            IT.update(l, r, x);
        }
        else {
            int res = -1;
            for (int i = 0; i < 20; i++) {
                int x = rd(l, r);
                int num = IT.get(x);
                if (get(num, l, r) >= (r - l + 2) / 2) {
                    if (res == 0) res = num;
                    else res = -1;
                }
            }
            if (res > 0) cout << res;
            else cout << "IMPOSSIBLE";
            cout << '\n';
        }
    }
}
