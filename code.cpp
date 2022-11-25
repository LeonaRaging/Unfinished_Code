#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define all(val) val.begin(), val.end()
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 3e5 + 4;
const int INF = 1e9;

struct DisjointSet {
   vector<int> par, Rank;
   DisjointSet(int n) {
      par.resize(n + 4);
      Rank.resize(n + 4);
      for (int i = 1; i <= n; i++)
         par[i] = i, Rank[i] = 0;
   }
   int find(int x) {
      if (x != par[x]) par[x] = find(par[x]);
      return par[x];
   }
   bool join(int u, int v) {
      u = find(u); v = find(v);
      if (u == v) return 0;
      par[v] = u;
      Rank[u] += Rank[v];
      return 1;
   }
};

struct Node {
   int type, i, x, y;
   Node(int type, int i, int x, int y):
      type(type), i(i), x(x), y(y) {}
   bool operator < (const Node &o) const {
      if (y != o.y) return y > o.y;
      if (type != o.type) return type == 1;
      return x < o.x;
   }
};

int n, m, res[maxn];
pii b[maxn];
vector<Node> myVec;

int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   //freopen(".INP", "r", stdin);
   //freopen(".OUT", "w", stdout);
   cin >> n;
   for (int i = 1, x, y; i <= n; i++) {
      cin >> x >> y;
      myVec.pb({0, i, x, y});
   }
   cin >> m;
   for (int i = 1; i <= m; i++) {
      cin >> b[i].fi >> b[i].se;
      myVec.pb({1, i, b[i].fi, b[i].se});
   }
   sort(all(myVec));
   set<pii> ms;
   set<Node> mySet;
   DisjointSet Dsu(n);
   for (auto it : myVec) {
      int t = it.type, x = it.x;
      if (!t) {
         auto lo = ms.lower_bound(pii(x, 0));
         Dsu.Rank[lo->se]++;
      }
      else {
         while (!ms.empty() && ms.begin()->fi < x)
            ms.erase(ms.begin());
         ms.insert({x, it.i});
         mySet.insert(it);
      }
   }
   for (auto it : ms)
      clog << it.fi << ' ' << it.se << '\n';
   for (int i = m; i >= 1; i--) {
      int u = Dsu.find(i);
      res[i] = Dsu.Rank[u];
      auto it = mySet.lower_bound(Node(1, i, b[i].fi, b[i].se));
      Dsu.join(u, it->i);
   }
   for (int i = 1; i <= m; i++)
      cout << res[i] << '\n';
}
