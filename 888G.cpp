#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const int maxn = 2e5 + 4;
const int LOG = 2;

struct Edge {
    int u, v, w;
};

int n, a[maxn];
vector<int> mySet[maxn];
vector<Edge> edges;

struct DisjointSet {
    vector<int> par, Rank;
    DisjointSet() {
        par.resize(maxn);
        Rank.resize(maxn);
        for (int i = 0; i < maxn; i++) {
            par[i] = i, Rank[i] = 1;
            mySet[i].pb(i);
        }
    }
    int find(int x) {
        if (x != par[x]) par[x] = find(par[x]);
        return par[x];
    }
    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return 0;
        if (Rank[u] < Rank[v]) swap(u, v);
        if (mySet[u].size() < mySet[v].size())
            swap(mySet[u], mySet[v]);
        for (auto it : mySet[v])
            mySet[u].pb(it);
        mySet[v].clear();
        return 1;
    }
} Dsu;

struct Trie {
  int sz, nxt[30 * maxn][2];
  bool leaf[30 * maxn];
  Trie () {
    sz = 0;
    for (int i = 0; i < 30 * maxn; i++)
        nxt[i][0] = nxt[i][1] = leaf[i] = 0;
  }
  void add_string(int x, int idx) {
    int v = 0;
    for (int i = LOG; i >= 0; i--) {
        int c = (x >> i & 1);
        if (!nxt[v][c])
            nxt[v][c] = ++sz;
        v = nxt[v][c];
    }
    leaf[v] = idx;
  }
  void del_string(int x) {
    int v = 0;
    for (int i = LOG; i >= 0; i--) {
        int c = (x >> i & 1);
        int u = nxt[v][c];
        nxt[v][c] = 0;
        v = u;
    }
    leaf[v] = 0;
  }
  int get(int x) {
    int v = 0;
    for (int i = LOG; i >= 0; i--) {
        clog << v << '\n';
        int c = (x >> i & 1);
        if (!nxt[v][c]) {
            if (!nxt[v][1 - c]) break;
            v = nxt[v][1 - c];
        }
        else v = nxt[v][c];
    }
    return leaf[v];
  }
} t;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    n = unique(a + 1, a + 1 + n) - (a + 1);
    ll res = 0;
    for (int i = 1; i <= n; i++)
        t.add_string(a[i], i);
    //cout << db(t.nxt[0][0]);
    return 0;
    for (int time = 0; time < LOG; time++) {
        edges.clear();
        for (int i = 1; i <= n; i++) if (mySet[i].size()) {
            for (auto it : mySet[i])
                t.del_string(a[it]);
            pair<int,int> bst = {(1 << 30), 0};
            for (auto it : mySet[i]) {
                auto idx = t.get(a[it]);
                if (a[it] ^ a[idx] < bst.fi)
                    bst = {a[it] ^ a[idx], idx};
            }
//            if (time == 0 && i == 1)
//                clog << db(t.get(a[1])) << '\n';
            for (auto it : mySet[i])
                t.add_string(a[it], it);
            edges.pb({i, bst.se, bst.fi});
        }
        for (auto it : edges) {
            if (Dsu.join(it.u, it.v))
                res += it.w;
        }
    }
    cout << res;
}
