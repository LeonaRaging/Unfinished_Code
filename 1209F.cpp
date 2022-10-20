#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define db(val) "[" #val " = " << (val) << "] "

const ll mod = 1e9 + 7;
const int maxn = 1e6 + 4;
const int INF = 1e9;

int n, m, sz, vis[maxn], dis[maxn];
vector<pair<int,int>> adj[maxn];
vector<int> candi[10];

void addedge(int u, int v, int w) {
   vector<int> myVec;
   while (w) {
      myVec.pb(w % 10);
      w /= 10;
   }
   reverse(myVec.begin(), myVec.end());
   int node = u;
   for (int i = 0; i < (int)myVec.size() - 1; i++) {
      adj[node].pb({++sz, myVec[i]});
      node = sz;
   }
   adj[node].pb({v, myVec.back()});
}

int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   //freopen(".INP", "r", stdin);
   //freopen(".OUT", "w", stdout);
   cin >> n >> m;
   sz = n;
   for (int i = 1; i <= m; i++) {
      int u, v; cin >> u >> v;
      addedge(u, v, i);
      addedge(v, u, i);
   }
   for (int i = 1; i <= n; i++)
      sort(adj[i].begin(), adj[i].end(), [](pii a, pii b) {
         return a.se < b.se;
      });
   queue<vector<int>> q;
   q.push(vector<int>(1, 1));
   memset(dis, 63, sizeof dis);
   dis[1] = 0;
   vector<tuple<int,int,int>> edges;
   while (!q.empty()) {
      for (int i = 0; i < 10; i++)
         candi[i].clear();
      edges.clear();
      auto myVec = q.front(); q.pop();
      for (int u : myVec) {
         for (auto it : adj[u]) {
            int v, w; tie(v, w) = it;
            if (dis[v] == dis[0])
               edges.pb({w, u, v});
         }
      }
      sort(edges.begin(), edges.end());
      for (auto it : edges) {
         int w, u, v; tie(w, u, v) = it;
         if (dis[v] == dis[0]) {
            dis[v] = (1LL * dis[u] * 10 + w) % mod;
            candi[w].pb(v);
         }
      }
      for (int i = 0; i < 10; i++) 
         if (!candi[i].empty())
            q.push(candi[i]);
   }
   for (int i = 2; i <= n; i++)
      cout << dis[i] << '\n';
}
