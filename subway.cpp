#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
const ll mod = 1e9 + 7;
const int maxn = 1e4 + 4;
const int INF = 1e9;
const int N = 16;

int m, n, sz, a[maxn][N], par[1 << N];
pair<int,int> K[maxn];
ll dp[N][1 << N], MX[1 << N];

void Solve() {
    cin >> m >> n;
    for (int mask = 0; mask < (1 << n); mask++)
        par[mask] = 0;
    for (int i = 0; i < m; i++) {
        int mx = 0;
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            mx = max(mx, a[i][j]);
        }
        K[i] = {mx, i};
    }
    sort(K, K + m);
    for (int mask = 0; mask < (1 << n); mask++) 
        if (!par[mask]) {
            sz++;
            for (int i = 0; i < n; i++) {
                int child = ((mask << i) | (mask >> (n - i))) & ((1 << n) - 1);
                par[child] = sz;
            }
        }
    for (int i = 0; i < min(n, m); i++) {
        for (int j = 0; j < n; j++)
            a[i][j] = a[K[m - i - 1].se][j];
    }
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < min(n, m); i++) {
        if (i) for (int mask = 0; mask < (1 << n); mask++)
            dp[i][mask] = dp[i - 1][mask];
        for (int mask = 0; mask < (1 << n); mask++) {
            for (int j = 0; j < n; j++)
                if (mask >> j & 1) {
                    dp[i][mask] = max(dp[i][mask], dp[i][mask ^ (1 << j)] + a[i][j]);
                }
        }
        memset(MX, 0, sizeof MX);
        for (int mask = 0; mask < (1 << n); mask++)
            MX[par[mask]] = max(MX[par[mask]], dp[i][mask]); 
        for (int mask = 0; mask < (1 << n); mask++)
            dp[i][mask] = MX[par[mask]];
    }
    cout << dp[min(m, n) - 1][(1 << n) - 1] << '\n';
    clog << dp[1][3];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    int t; cin >> t;
    while (t--) {
        Solve();
    }
}
