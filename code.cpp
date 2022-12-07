#include <bits/stdc++.h>
using namespace std;

#define all(val) val.begin(), val.end()
#define db(val) "[" #val " = " << (val) << "] "

const int INF = 1e9;
const int K = 10;

struct Node {
	int nxt[K], go[K];
	int mask = 0, link = -1, p = -1;
	bool bad = 0;
	char pch;
	Node(int p = -1, char pch = '$'): p(p), pch(pch) {
		memset(nxt, -1, sizeof nxt);
		memset(go, -1, sizeof go);
	}
};

int n, m, node;
vector<vector<int>> dp, par;
vector<vector<pair<int,int>>> trace;
vector<Node> t(1);

void add_string(string s, int id, bool f) {
	int v = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		int c = s[i] - 'a';
		if (t[v].nxt[c] == -1) {
			t[v].nxt[c] = t.size();
			// clog << v << ' ' << t.size() << ' ' << char(c + 'a') << '\n';
			t.emplace_back(v, s[i]);
		}
		v = t[v].nxt[c];
	}
	if (f) t[v].bad = 1;
	else t[v].mask |= (1 << id);
}

int go(int v, char ch);

int get_link(int v) {
	if (t[v].link == -1) {
		if (!v || !t[v].p)
			t[v].link = 0;
		else
			t[v].link = go(get_link(t[v].p), t[v].pch);
		t[v].mask |= t[t[v].link].mask;
		t[v].bad |= t[t[v].link].bad;
	}
	return t[v].link;
}

int go(int v, char pch) {
	int c = pch - 'a';
	if (t[v].go[c] == -1) {
		if (t[v].nxt[c] != -1)
			t[v].go[c] = t[v].nxt[c];
		else 
			t[v].go[c] = (!v ? 0 : go(get_link(v), pch));
	}
	return t[v].go[c];
}

void push_link() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		get_link(v);
		for (int i = 0; i < K; i++)
			if (t[v].nxt[i] != -1)
				q.push(t[v].nxt[i]);
	}
}

void bfs() {
	queue<pair<int,int>> q;
	q.push({0, 0});
	dp[0][0] = 0;
	while (!q.empty()) {
		int v, mask; tie(v, mask) = q.front(); q.pop();
		// clog << v << ' ' << bitset<2>(mask) << endl;
		if (mask == (1 << n) - 1) {
			node = v;
			break;
		}
		for (int i = 0; i < K; i++) {
			int u = go(v, char(i + 'a'));
			if (!u || t[u].bad) continue;
			int nxt = mask | t[u].mask;
			if (dp[v][mask] + 1 < dp[u][nxt]) {
				dp[u][nxt] = dp[v][mask] + 1;
				trace[u][nxt] = {v, mask};
				par[u][nxt] = i;
				q.push({u, nxt});
			}
		}
	}
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    string s;
    for (int i = 0; i < n; i++) {
    	cin >> s;
    	add_string(s, i, 0);
    }
    for (int i = 0; i < m; i++) {
    	cin >> s;
    	add_string(s, i, 1);
    }
    push_link();
    dp.resize(t.size());
    trace.resize(t.size());
    par.resize(t.size());
    for (int i = 0; i < (int)t.size(); i++) {
    	dp[i].resize(1 << n);
    	trace[i].resize(1 << n);
    	par[i].resize(1 << n);
    	fill(all(dp[i]), INF);
    }
    node = -1;
    bfs();
    if (node == -1)
    	return cout << "-", 0;
    string res = "";
    int bst = (1 << n) - 1;
    while (node) {
    	// clog << node << ' ' << bst << ' ' << par[node][bst] << endl;
    	int v, mask; tie(v, mask) = trace[node][bst];
    	if (par[node][bst] != -1)
    		res += char(par[node][bst] + 'a');
    	node = v; bst = mask;
    }
    reverse(all(res));
    cout << res;
    // for (int i = 0; i < (int)t.size(); i++)
    	// clog << i << ' ' << t[i].link << endl;
}


