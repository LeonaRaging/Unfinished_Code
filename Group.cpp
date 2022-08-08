#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const int maxn = 1e5 + 4;
const ll INF = 1e16;
const ll mod = 998244353;
const int N = 40;

int n, k, dp[maxn][N];
ll a[maxn], t[4 * maxn];

void build(int v, int l, int r) {
    if (l == r) t[v] = (1LL << (a[l] - 1));
    else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = (t[2 * v] | t[2 * v + 1]);
    }
}

int get(int v, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return 0;
    if (tl >= l && tr <= r) return t[v];
    int m = (tl + tr) / 2;
    int L = get(2 * v, tl, m, l, r);
    int R = get(2 * v  + 1, m + 1, tr, l, r);
    return (L | R);
}

void Solve(int k, int L, int R, int optL, int optR) {
    if (L > R) return;
    int m = (L + R) / 2, best;
    for (int i = optL; i <= min(m - 1, optR); i++) {
        int num = __builtin_popcountll(get(1, 1, n, i + 1, m));
        if (dp[i][k - 1] + num > dp[m][k]) {
            dp[m][k] = dp[i][k - 1] + num;
            best = i;
        }
    }
    Solve(k, L, m - 1, optL, best);
    Solve(k, m + 1, R, best, optR);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    ll mask = 0;
    for (int i = 1; i <= n; i++) {
        mask |= (1LL << (a[i] - 1));
        dp[i][1] = __builtin_popcountll(mask);
    }
    for (int i = 2; i <= k; i++)
        Solve(i, 1, n, 0, n);
    cout << dp[n][k] << '\n';
}
