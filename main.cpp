#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define all(val) val.begin(), val.end()
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 4;
const int INF = 1e9;
const int MAX = 3e6;
const int N = 3e6 + 4;

void coding() {
    if (fopen("inputf.in", "r")) {
        freopen("inputf.in", "r", stdin);
        freopen("outputf.out", "w", stdout);
        freopen("log.out", "w", stderr);
    }
}

void fre() {
    freopen(".INP", "r", stdin);
    freopen(".OUT", "w", stdout);
}

int n, prime[N], col[maxn], a[maxn];
vector<int> primes, myVec[2], res, adj[maxn], pos[N];
map<ll,bool> mp;
bool flag;

void init(int n) {
    mp.clear();
    res.clear();
    for (int i = 1; i <= n; i++)
        adj[i].clear();
    for (int i = 1; i <= MAX; i++)
        pos[i].clear();
}

int get(int i, int j) {
    return (i - 1) * n + j;
}

bool cmp(int i, int j) {
    return a[i] < a[j];
}

void bfs(int u) {
    myVec[0].clear();
    myVec[1].clear();
    queue<int> q;
    col[u] = 0; q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        myVec[col[u]].pb(u);
        for (int v : adj[u]) {
            if (col[v] == col[u])
                return flag = 0, void();
            else if (col[v] == -1) {
                col[v] = col[u] ^ 1;
                q.push(v);
            }
        }
    }
    if (myVec[0].size() < myVec[1].size())
        swap(myVec[0], myVec[1]);
    if (myVec[0].size() == myVec[1].size()) {
        sort(all(myVec[0]), cmp); sort(all(myVec[1]), cmp);
        bool flag = 0;
        for (int i = 0; i < (int)myVec[0].size(); i++)
            if (a[myVec[0][i]] > a[myVec[1][i]]) {
                flag = 1;
                break;
            }
            else if (a[myVec[0][i]] < a[myVec[1][i]])
                break;
        if (flag) swap(myVec[0], myVec[1]);
    }
    for (int x : myVec[0])
        res.pb(x);
}

void Solve() {
    cin >> n;
    init(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].pb(i);
        col[i] = -1;
    }
    for (int i : primes) {
        int tot = 0, u = 0, v = 0;
        for (int j = i; j <= MAX; j += i) if (!pos[j].empty()) {
            tot += pos[j].size();
            if (!u) {
                u = pos[j][0];
                if (pos[j].size() > 1)
                    v = pos[j][1];
            }
            else v = pos[j][0];
        }
        if (tot > 2)
            return cout << -1 << '\n', void();
        if (!v) continue;
        ll idx = get(u, v);
        if (mp.find(idx) != mp.end())
            continue;
        adj[u].pb(v);
        adj[v].pb(u);
        mp[idx] = 1;
    }
    flag = 1;
    for (int i = 1; i <= n; i++) {
        if (col[i] == -1)
            bfs(i);
        if (!flag)
            return cout << -1 << '\n', void();
    }
    sort(all(res), cmp);
    cout << res.size() << ' ';
    for (int x : res) cout << a[x] << ' ';
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // coding();
    // fre();
    for (int i = 2; i * i <= MAX; i++)
        if (!prime[i])
            for (int j = i * i; j <= MAX; j += i)
                prime[j] = 1;
    for (int i = 2; i <= MAX; i++)
        if (!prime[i])
            primes.pb(i);
    int t; cin >> t;
    while (t--)
        Solve();
}

