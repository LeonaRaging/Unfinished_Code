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
const int N = 18;

struct seg_tree {
    vector<int> t, lazy;
    seg_tree() {
        t.resize(4 * maxn);
    }
    void build(int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r) t[v] = 1;
        else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m + 1, r);
            t[v] = t[2 * v] + t[2 * v + 1];
        }
    }
    void update(int pos, int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r) {
            t[v] = 0;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) update(pos, 2 * v, l, m);
        else update(pos, 2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    int get(int num, int v = 1, int l = 1, int r = maxn - 1) {
        if (l == r) return l;
        int m = (l + r) / 2;
        if (t[2 * v] >= num)
            return get(num, 2 * v, l, m);
        num -= t[2 * v];
        return get(num, 2 * v + 1, m + 1, r);
    }
} IT;

int n, m, d, a[maxn], nxt[maxn], spt[maxn][20], sum[maxn], res[maxn];

int get(int l, int r) {
    int j = __lg(r - l + 1);
    return max(spt[l][j], spt[r - (1 << j) + 1][j]);
}

int find(int x) {
    if (x != nxt[x]) nxt[x] = find(nxt[x]);
    return nxt[x];
}

int main()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> m >> d;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        nxt[i] = i;
        spt[i][0] = a[i];
    }
    nxt[n] = n;
    for (int j = 1; j <= N; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            spt[i][j] = max(spt[i][j], spt[i + (1 << (j - 1))][j - 1]);
    IT.build();
    for (int i = 1; i <= m; i++) {
        int l, r; cin >> l >> r;
        l++, r++;
        l = (l != 1 ? IT.get(l - 1) + 1 : 1);
        r = IT.get(r);
        // clog << db(l) << db(r) << '\n';
        if (get(l, r - 1) < d) {
            sum[l]++, sum[r]--;
        }
        for (int cur = find(l); cur < r; cur = find(cur + 1)) {
            // clog << cur << '\n';
            IT.update(cur);
            nxt[cur] = nxt[cur + 1];
        }
    }
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i - 1] + sum[i];
        if (res[ans] < res[i])
            ans = i;
    }
    cout << ans - 1 << '\n';
    // clog << res[8];
}
