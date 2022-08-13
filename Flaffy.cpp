#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const ll mod = 1e9 + 7;
const int maxn = 2e5 + 4;
const int INF = 1e9;
const int N = 1e5;
const int N2 = 161051;
const int M = 45;

vector<int> mask[6];
int dis[maxn], trans[maxn][40], L[maxn][45], R[maxn][45], cur[maxn], mx[maxn], mn[maxn];
vector<pii> a[maxn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    for (int i = 0; i < 32; i++)
        mask[__builtin_popcount(i)].pb(i);
    for (int i = 0; i < N; i++) {
        dis[i] = dis[i / 10] + (i % 10 != 0);
        for (int j = 0; j < 32; j++) {
            int v = i, w = 0;
            for (int k = 0; k < 5; k++) {
                if (j >> k & 1) w = w * 11 + 10;
                else w = w * 11 + v % 10;
                v /= 10;
            }
            trans[i][j] = w;
        }
    }
    for (int c = 0; c <= M; c++) {
        for (int i = 0; i < N2; i++) a[i].clear();
        for (int i = 0; i < c && i < 5; i++) {
            int t = c - i + 1;
            for (int k = 0; k < N; k++)
                for (int m : trans[i]) a[trans[k][m]].pb({L[k][t], R[k][t]});
        }
        for (int k = 0; k < N2; k++) {
            sort(a[k].begin(), a[k].end(), [] (pii a, pii b) {
                return a.se > b.se; });
            cur[k] = 0;
            mn[k] = N + 1;
        }
        for (int k = N; k >= 0; k--) {
            L[k][c] = k - 1;
            for (int j = 0; j < 32; j++) {
                int v = trans[k][j];
                while (cur[v] < int(a[v].size()) && a[v][cur[v]].se >= k - 1) {
                    mn[v] = min(mn[v], a[v][cur[v]++].fi);
                }
                L[k][c] = min(L[k][c], mn[v]);
            }
        }
        for (int k = 0; k < N2; k++) {
            sort(a[k].begin(), a[k].end(), [] (pii a, pii b) {
                return a.fi < b.fi; });
            cur[k] = 0;
            mx[k] = -1;
        }
        for (int k = 0; k < N; k++) {
            R[k][c] = k + 1;
            for (int j = 0; j < 32; j++) {
                int v = trans[k][j];
                while (cur[v] < int(a[v].size()) && a[v][cur[v]].fi <= k + 1)
                    mx[v] = max(mx[v], a[v][cur[v]++].se);
                R[k][c] = max(R[k][c], mx[v]);
            }
        }
    }
    int t; cin >> t;
    while (t--) {
        int l, r, ans = 45; cin >> l >> r;
        for (int i = l; i <= r; i++) {
            int d1 = 0, d2 = 0;
            while (L[i][d1] > l && d1 <= M) d1++;
            while (R[i][d2] < r && d2 <= M) d2++;
            ans = min(ans, d1 + d2 + dis[i]);
        }
        cout << ans << '\n';
    }
}
