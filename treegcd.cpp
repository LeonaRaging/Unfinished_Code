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
const int N = 105;

int n, m;
ll dp[N][maxn], tot[N][maxn];
vector<int> adj[N], prime[maxn];

void add(ll &a, ll b) {
    a += b; if (a > mod) a -= mod;
}

void del(ll &a, ll b) {
    a -= b; if (a < 0) a += mod;
}

void dfs(int u, int p) {
    for (int v : adj[u]) 
        if (v != p) dfs(v, u);
    for (int i = 2; i <= m; i++) {
        dp[u][i] = 1;
        int k = prime[i].size();
        for (int v : adj[u]) {
            if (v == p) continue;
            ll sum = 0;
            for (int mask = 1; mask < (1 << k); mask++) {
                int cnt = 0, p = 1;
                for (int j = 0; j < k; j++)
                    if (mask >> j & 1) {
                        cnt++;
                        p *= prime[i][j];
                    }
                if (cnt & 1) add(sum, tot[v][p]);
                else del(sum, tot[v][p]);
            }
            if (sum)
                (dp[u][i] *= sum) %= mod;
        }
    }
    for (int i = 2; i <= m; i++)
        for (int j = i; j <= m; j += i)
            add(tot[u][i], dp[u][j]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("treegcd.in", "r", stdin);
    // freopen("treegcd.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i = 2; i <= m; i++)
        if (prime[i].empty()) {
            for (int j = i; j <= m; j += i)
                prime[j].pb(i);
        }
    dfs(1, 0);
    ll res = 0;
    for (int i = 2; i <= m; i++)
        add(res, dp[1][i]);
    cout << res;
}
