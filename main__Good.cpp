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

int n, a[maxn];

void Solve() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> res;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> v1, v2;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1)
                v1.pb(a[i]);
            else v2.pb(a[i]);
        bool flag = 0;
        for (int i = 0; i < (int)v1.size(); i++)
            for (int j = i + 1; j < (int)v1.size(); j++) {
                if (__gcd(v1[i], v1[j]) > 1) flag = 1;
                // if (mask == 31 && flag) clog << v1[i] << ' ' << v1[j] << ' ' << __gcd(v1[i], v1[j]) << endl;
            }
        for (int i = 0; i < (int)v2.size(); i++)
            for (int j = i + 1; j < (int)v2.size(); j++)
                if (__gcd(v2[i], v2[j]) > 1) flag = 1;
        if (flag) continue;
        sort(all(v1)); sort(all(v2));
        if (v1.size() > res.size())
            res = v1;
        else if (v1.size() == res.size()) {
            bool flag = 0;
            for (int i = 0; i < (int)res.size(); i++) {
                if (v1[i] < res[i]) {
                    flag = 1;
                    break;
                }
                if (v1[i] > res[i]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) res = v1;
        }
    }
    if (res.size() == 0) cout << -1 << '\n';
    else {
        cout << res.size() << ' ';
        for (int x : res) cout << x << ' ';
        cout << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // coding();
    // fre();
    int t; cin >> t;
    while (t--)
        Solve();
}

