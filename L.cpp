#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e6 + 4;
const int INF = 1e9;

int m, n, tot, pre[maxn], cnt[maxn];
vector<int> vals, sum[maxn];
vector<pair<int,int>> queries;

void insert(int x) {
    if (cnt[x] == 0) tot++;
    cnt[x]++;
}

void erase(int x) {
    cnt[x]--;
    if (cnt[x] == 0) tot--;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        int num; cin >> num;
        for (int i = 1; i <= num; i++) {
            int x; cin >> x;
            pre[i] = pre[i - 1] + x;
        }
        for (int j = 0; j <= num; j++) {
            vals.pb(pre[j] + 1); vals.pb(m - (pre[num] - pre[j]) + 1);
            queries.pb({pre[j] + 1, i}); queries.pb({m - (pre[num] - pre[j]) + 1, -i});
        }
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (auto &it : queries) {
        it.fi = lower_bound(vals.begin(), vals.end(), it.fi) - vals.begin() + 1;
        sum[it.fi].pb(it.se);
    }
    int res = m;
    for (int i = 1; i < int(vals.size()); i++) {
        for (auto x : sum[i])
            if (x < 0) erase(-x);
            else insert(x);
        if (tot == n)
            res -= vals[i] - vals[i - 1];
    }   
    cout << res;
}
