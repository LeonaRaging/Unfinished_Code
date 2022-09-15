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

int r, c;
int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0,-1, 1};
vector<vector<int>> a, dp[2], col;
queue<pair<int,int>> q;

bool ok(int i, int j) {
    return i >= 1 && i <= r && j >= 1 && j <= c;
}

void place(int i, int j, int k) {
    clog << i << ' ' << j << ' ' << k << '\n';
    for (int p = 0; p < 4; p++)
        if (p != k) {
            int x = i + dx[p], y = j + dy[p];
            if (!ok(x, y) || abs(col[x][y] == 1))
                cout << "NO", exit(0);
            q.push({x, y});
            col[x][y] = 2;
        }
    col[i][j] = 2;
}

void bfs() {
    while (!q.empty()) {
        int i, j; tie(i, j) = q.front(); q.pop();
        for (int p = 0; p < 4; p++) {
            int x = i + dx[p], y = j + dy[p];
            if (ok(x, y) && abs(col[x][y] == 1)) {
                if (x == 4 && y == 5) clog << "ok";
                place(x, y, p ^ 1);
                col[x][y] = 2;
            }
        }
    }
}

void dfs(int i, int j, int k) {
    col[i][j] = -1;
    dp[0][i][j] = dp[1][i][j] = -INF;
    for (int p = 0; p < 4; p++) if (k != p) {
        int x = i + 2 * dx[p], y = j + 2 * dy[p];
        if (!ok(x, y)) continue;
        if (col[x][y] == -1) {
            place(i, j, p), bfs();
            return;
        }
        else if (col[x][y] == 1)
            dfs(x, y, p ^ 1);
    }
    for (int p = 0; p < 4; p++) {
        int res = 0;
        for (int d = 0; d < 4; d++) if (d != k) {
            if (d == p) {
                
            }
        }
    }
}

int main()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> r >> c;
    a.resize(r + 4);
    for (int i = 0; i < r + 4; i++)
        a[i].resize(c + 4);
    dp[0] = dp[1] = col = a;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> a[i][j];
    int k; cin >> k;
    for (int i = 1; i <= k; i++) {
        int x, y; cin >> x >> y;
        x++, y++;
        col[x][y] = 1;
        q.push({x, y});
    }   
    for (int i = 1; i <= r; i++)
        q.push({i, 0}), q.push({i, c + 1});
    for (int j = 1; j <= c; j++) {
        q.push({0, j}), q.push({r + 1, j});
    }
    bfs();
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) if (col[i][j] == 1) {
            if (i > 1 && j > 1 && col[i - 1][j - 1] == 1)
                place(i, j, 0), bfs();
            if (i > 1 && j < c && col[i - 1][j + 1] == 1)
                place(i, j, 0), bfs();
        }
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) if (col[i][j] == 1) {
            dfs(i, j, -1);
        }
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cout << col[i][j] << (j == c ? '\n' : ' ');
}
