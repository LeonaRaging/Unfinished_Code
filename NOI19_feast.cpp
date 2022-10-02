#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 3e5 + 4;
const int INF = 1e9;

using T = pair<int,int>;

int n, k, a[maxn], par[maxn], Rank[maxn];

priority_queue<T, vector<T>, greater<T>> pq;
vector<int> myVec;
set<int> ms;

struct DisjointSet {
    DisjointSet(int n) {
        for (int i = 1; i <= n; i++) {
            par[i] = i, Rank[i] = myVec[i - 1];
            pq.push({abs(Rank[i]), i});
            ms.insert(i);
        }
    }
    int find(int x) {
        if (x != par[x]) par[x] = find(par[x]);
        return par[x];
    }
    bool join(int u, int v) {
        if (u == v) return 0;
        ms.erase(v);
        Rank[u] += Rank[v];
        par[v] = u;
        return 1;
    }
};

void init() {
    while (Rank[*ms.begin()] < 0)
        ms.erase(*ms.begin());  
    while (Rank[*ms.rbegin()] < 0)
        ms.erase(*ms.rbegin());
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int cur = 0, cnt = 0;
    int L = 1, R = n;
    while (a[L] <= 0) L++;
    while (a[R] <= 0) R--;
    int flag = (a[L] > 0 ? 1 : -1);
    for (int i = L; i <= R + 1; i++) {
        if (a[i] * flag < 0 || i == R + 1) {
            if (cur > 0)
                cnt++;
            myVec.pb(cur);
            cur = 0;
            flag = (a[i] > 0 ? 1 : -1);
        }
        cur += a[i];
    }
    n = myVec.size();
    DisjointSet Dsu(n);
    while (cnt > k) {
        int cur, x; tie(cur, x) = pq.top(); pq.pop();
        if (ms.find(x) == ms.end()) continue;
        auto lo = ms.lower_bound(x);
        auto hi = ms.upper_bound(x);
        int u = (lo == ms.begin() ? x : *(--lo));
        int v = (hi == ms.end() ? x : *hi);
        u = Dsu.find(u); v = Dsu.find(v);
        int pre = (Rank[u] > 0 && u != x) + (Rank[v] > 0 && v != x) + (Rank[x] > 0);
        Dsu.join(x, u);  
        Dsu.join(x, v);
        pq.push({abs(Rank[x]), x});
        int suf = Rank[u] > 0;
        cnt -= (pre - suf);
        init();
    }
    int res = 0;
    for (auto i : ms)
        if (Rank[i] > 0) res += Rank[i];
    cout << res;
}
