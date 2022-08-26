#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const int maxn = 3e5 + 4;
const int LOG = 2;
const int N = 1505;

int n, m, dem[maxn], cost[maxn];
ll sum[N][N], sumsqr[N][N], cnt[N][N];
vector<int> myVec[maxn];

pair<int,int> get(ll AplusB, ll A2plusB2) {
    ll AB = (AplusB * AplusB - A2plusB2) / 2;
    ll AminusB = sqrt(A2plusB2 - 2 * AB);
    ll A = (AplusB + AminusB) / 2;
    ll B = AplusB - A;
    return {A, B};
}

void Solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, u, y, v; cin >> x >> u >> y >> v;
        sum[x][y] += i; sumsqr[x][y] += i * i; cnt[x][y]++;
        sum[x][v + 1] -= i; sumsqr[x][v + 1] -= i * i; cnt[x][v + 1]--;
        sum[u + 1][y] -= i; sumsqr[u + 1][y] -= i * i; cnt[u  + 1][y]--;
        sum[u + 1][v + 1] += i; sumsqr[u + 1][v + 1] += i * i; cnt[u + 1][v + 1]++;
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + sum[i][j];
            sumsqr[i][j] = sumsqr[i - 1][j] + sumsqr[i][j - 1] - sumsqr[i - 1][j - 1] + sumsqr[i][j];
            cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1] + cnt[i][j];
        }
    int all = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) {
                if (cnt[i][j]) all++;
                if (cnt[i][j] == 1) cost[sum[i][j]]++;
                if (cnt[i][j] == 2) {
                int A, B; tie(A, B) = get(sum[i][j], sumsqr[i][j]);
                myVec[A].pb(B);
            }
        }
    int res = all;
    for (int i = 1; i <= n; i++) {
        for (int j : myVec[i]) {
            dem[j]++;
            res = min(res, all - cost[i] - cost[j] - dem[j]);
        }
        for (int j : myVec[i]) dem[j]--;
    }
    int mx[2] = {0, 0};
    for (int i = 1; i <= n; i++) {
        mx[1] = max(mx[1], cost[i]);
        sort(mx, mx + 2);
    }
    res = min(res, all - mx[0] - mx[1]);
    cout << res << '\n';
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++)
            sum[i][j] = sumsqr[i][j] = cnt[i][j] = 0;
    }
    for (int i = 1; i <= n; i++)
        myVec[i].clear(), dem[i] = cost[i] = 0;
}

signed main()
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
