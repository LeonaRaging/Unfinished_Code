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
const int N = 1005;

int n, m, dis[N][N], R[N][N], L[N][N];

int Solve(int i, int j, int type) {
    bool res = 0;
    if (type == 0) {
        if (L[i][j] != -1) 
            return L[i][j];
        int pre = (j - 1 + n) % n;
        res = (Solve(i, pre, 0) && dis[pre][j]) || (Solve(pre, i, 1) && dis[i][j]);
        return L[i][j] = res;
    }
    else {
        if (R[i][j] != -1)
            return R[i][j];
        int nxt = j % n + 1;
        res = (Solve(i, nxt, 1) && dis[nxt][j]) || (Solve(nxt, i, 0) && dis[i][j]);
        return R[i][j] = res;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        dis[u][v] = dis[v][u] = 1;
    }
    for (int i = 1; i <= n; i++) {
        R[i][i] = L[i][i] = 1;
        for (int j = 1; j <= n; j++)
            if (i != j) R[i][j] = L[i][j] = -1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) 
            if (i != j)
                Solve(i, j, 0), Solve(i, j, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (R[i][j] && L[i + 1][j]) {
                deque<int> res;
                int x, y, type;
                x = i, y = j;
                type = 1;
                while (x != y) {
                    res.push_back(y);
                    int pre = (y - 1 + n) % n;
                    int nxt = y % n + 1;
                    if (type == 0) {
                        if (L[x][pre] && dis[pre][y]) y = pre;
                        else y = x, x = pre, type = 1;
                    }
                    else {
                        if (R[x][nxt] && dis[nxt][y]) y = nxt;
                        else y = x, x = nxt, type = 0;
                    }
                }
                res.push_back(y);
                x = i + 1, y = j;
                type = 0;
                while (x != y) {
                    int pre = (y - 1 + n) % n;
                    int nxt = y % n + 1;
                    if (type == 0) {
                        if (L[x][pre] && dis[pre][y]) y = pre;
                        else y = x, x = pre, type = 1;
                    }
                    else {
                        if (R[x][nxt] && dis[nxt][y]) y = nxt;
                        else y = x, x = nxt, type = 0;
                    }
                    res.push_front(y);
                }
                while (!res.empty()) cout << res.back() << '\n', res.pop_back();
                return 0;
            }
    cout << -1;
}
