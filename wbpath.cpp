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
const int N = 105;

int r, c, f[N][N][4 * N], trace[N][N][4 * N];
int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0,-1, 1};
char dire[] = {'U', 'D', 'L', 'R'};
string grid[N];

bool ok(int i, int j) {
    return i >= 1 && i <= r && j >= 1 && j <= c;
}

void Solve() {
    int x, y, s, t; cin >> x >> y >> s >> t;
    memset(f, 63, sizeof f);
    queue<tuple<int,int,int>> q;
    int d = r + c + (grid[x][y] == 'W' ? 1 : -1);
    f[x][y][d] = 0;
    q.push({x, y, d});
    while (!q.empty()) {
        int i, j, diff; tie(i, j, diff) = q.front(); q.pop();
        // cout << i << ' ' << j << ' ' << diff << '\n';
        for (int p = 0; p < 4; p++) {
            int x = i + dx[p], y = j + dy[p];
            if (!ok(x, y)) continue;
            int nxt = diff + (grid[x][y] == 'W' ? 1 : -1);
            // if (i == 1 && j == 1 && diff == 7) clog << x << ' ' << y << ' ' << nxt << '\n';
            if (nxt < 0 || nxt > 2 * (r + c)) continue;
            if (f[i][j][diff] + 1 < f[x][y][nxt]) {
                f[x][y][nxt] = f[i][j][diff] + 1;
                trace[x][y][nxt] = p;
                q.push({x, y, nxt});
            }
        }
    }
    if (f[s][t][r + c] == f[0][0][0])
        return cout << -1 << '\n', void();
    vector<char> res;
    int diff = r + c;
    while (s != x || t != y) {
        // clog << s << ' ' << t << '\n';
        int p = trace[s][t][diff];
        res.pb(dire[trace[s][t][diff]]);
        s += dx[p]; t += dy[p];
        diff -= (grid[s][t] == 'W' ? 1 : -1);
    }
    cout << f[s][t][r + c] << ' ';
    for (auto i : res) cout << i << ' ';
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        cin >> grid[i];
        grid[i] = ' ' + grid[i];
    }
    int t; cin >> t;
    while (t--)
        Solve();
}
