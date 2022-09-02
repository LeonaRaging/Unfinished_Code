#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 4;
const int INF = 1e9;
const int N = 1005;

struct Node {
    int cnt, v, h, ms;
    Node (int _cnt = 0, int _v = 0, int _h = 0, int _ms = 0): cnt(_cnt), v(_v), h(_h), ms(_ms){}
};

int r, c, a[N][N], s[N][N];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> a[i][j];
    int ans = 0;
    for (int i = 1; i <= r; i++) {
        stack<Node> st;
        st.push(Node(0, -1, 0, 0));
        for (int j = 1; j <= c; j++) {
            s[i][j] = 1;
            if (a[i][j] == a[i - 1][j])
                s[i][j] += s[i - 1][j];
            int sum = 1;
            while (st.top().v == a[i][j] && st.top().h >= s[i][j]) {
                sum += st.top().cnt;
                st.pop();
            }
            int cur = sum * s[i][j];
            if (st.top().v == a[i][j])
                cur += st.top().ms;
            ans += cur;
            st.push(Node(sum, a[i][j], s[i][j], cur));
        }
    }
    cout << ans;
}
