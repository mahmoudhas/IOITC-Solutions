#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <cstring>
#include <cassert>
#include <bitset>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int MAXN = 200010;
const int MXLOG = 30;
const int mod = 1000000007;
const int inf = (1 << 30);
const ll infll = (1LL << 60);

int n, m;
int x, y;
vector<int> adj[MAXN];
map<ii, int> price;

int vis[MAXN];
vector<int> from[MAXN];

struct st
{
	int u, v, l;
	st() {}
	st(int a, int b, int c)
	{
		u = a, v = b, l = c;
	}
};

queue<st> q;
bool dag[MAXN];
int f[MAXN];
bool done[MAXN];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> x >> y;
	while (m--)
	{
		int u, v;
		char ch;
		cin >> u >> ch >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		price[{u, v}] = price[{v, u}] = ch;
	}

	q.emplace(x, x, 0);
	memset(vis, -1, sizeof vis);
	while (!q.empty())
	{
		int u = q.front().u, v = q.front().v, l = q.front().l;
		q.pop();
		if (vis[u] != -1)
		{
			if (l == vis[u] && u != v)
				from[u].push_back(v);
			continue;
		}
		vis[u] = l;
		if (u != v)
			from[u].push_back(v);
		for (auto nu : adj[u]) if (nu - v)
		{
			q.emplace(nu, u, l + 1);
		}
	}

	queue<int> temp;
	temp.push(y);
	dag[y] = true;
	while (!temp.empty())
	{
		int u = temp.front();
		temp.pop();
		for (auto nu : from[u]) if (!dag[nu])
		{
			temp.push(nu);
			dag[nu] = true;
		}
	}

	vector<int> cur;
	cur.push_back(x);
	memset(f, -1, sizeof f);
	while (!cur.empty())
	{
		int mn = inf;
		bool flag = false;
		for (auto u : cur)
		{
			if (u == y)
			{
				flag = true;
				break;
			}
			done[u] = true;
			for (auto v : adj[u]) if (dag[v] && !done[v])
				mn = min(mn, price[{u, v}]);
		}
		if (flag)
			break;
		vector<int> temp;
		for (auto u : cur)
		{
			for (auto v : adj[u]) if (dag[v] && !done[v] && price[{u, v}] == mn)
			{
				temp.push_back(v);
				f[v] = u;
				done[v] = true;
			}
		}
		cur = temp;
	}

	int u = y;
	string ans;
	while (u != x && u != -1)
	{
		ans += price[{f[u], u}];
		u = f[u];
	}
	reverse(ans.begin(), ans.end());
	cout << ans << '\n';
}
