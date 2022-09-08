#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 5e5 + 4;
const int INF = 1e9;

struct seg_tree {
    vector<int> t, lazy;
    seg_tree() {
        t.resize(4 * maxn);
        lazy.resize(4 * maxn);
    }
    void pushdown(int v) {
        int val = lazy[v];
        t[2 * v] += val;
        t[2 * v + 1] += val;
        lazy[2 * v] += val;
        lazy[2 * v + 1] += val;
        lazy[v] = 0;
    }
    void update(int l, int r, int val, int v = 1, int tl = 0, int tr = maxn - 1) {
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
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    int get(int l, int r, int v = 1, int tl = 0, int tr = maxn - 1) {
        if (tl > r || tr < l) return INF;
        if (tl >= l && tr <= r) return t[v];
        pushdown(v);
        int m = (tl + tr) / 2;
        int L = get(l, r, 2 * v, tl, m);
        int R = get(l, r, 2 * v + 1, m + 1, tr);
        return min(L, R);
    }
} IT[2];

int n, k, dp[maxn];
string s, t;

signed main() 
{
    ios::sync_with_stdio(0);
    cin.tie(    0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> k >> s >> t;
    s = ' ' + s, t = ' ' + t;
    for (int i = 1; i <= n; i++) {
        if (s[i] != t[i]) {
            if (t[i] == 'W' && t[i - 1] != 'W') {
                int j = i;
                while (t[i] == t[j]) j++;
                IT[1].update(0, j - 2, 1);
            }
            if (t[i] == 'B' && t[i - 1] != 'B') {
                int j = i;
                while (t[i] == t[j]) j++;
                IT[0].update(0, j - 2, 1);
            }
            int j = max(0LL, i - k);
            dp[i] = min(IT[0].get(j, i - 1), IT[1].get(j, i - 1)) + 1;
        } 
        else dp[i] = dp[i - 1];
        IT[0].update(i, i, dp[i]);
        IT[1].update(i, i, dp[i]);
    }
    cout << dp[n] << '\n';
}
