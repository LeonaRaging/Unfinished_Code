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

int n, c;
vector<pair<int,int>> a;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        int v, b; cin >> v >> b;
        a.pb({v, b});
    }
    sort(a.begin(), a.end());
    int ans = 0;
    while (true) {
        int sum = c;
        for (int i = n - 1; i >= 0; i--) {
            while (a[i].se > 0 && sum - a[i].fi >= 0) {
                a[i].se--;
                sum -= a[i].fi;
            }
        }
        for (int i = 0; i <= n - 1; i++)
            if (a[i].se > 0 && sum > 0) {
                a[i].se--;
                sum -= a[i].fi;
                break;
            }
        if (sum > 0) break;
        ans++;
    }
    cout << ans;
}
