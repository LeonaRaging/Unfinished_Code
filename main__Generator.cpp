#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define int long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "
using namespace std;
const ll mod = 20;
const int maxn = 20;
const int INF = 100;

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
    return l + mt() % (r - l + 1);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    int t = 5;
    cout << t << '\n';
    while (t--) {
        int n = get(5, 10);
        cout << n << '\n';
        for (int i = 1; i <= n; i++)
            cout << get(1, INF) << ' ';
        cout << '\n';
    }
}
