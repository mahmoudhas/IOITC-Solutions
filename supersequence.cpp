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

const int MAXN = 1010;
const int MXLOG = 30;
const int mod = 1000000007;
const int inf = (1 << 30);
const ll infll = (1LL << 60);

int n, m;
string s1, s2;

int dp[MAXN][MAXN];
int bt(int i, int j)
{
	int &ret = dp[i][j];
	if (ret != -1) return ret;
	if (i == n && j == m)
		return ret = 0;
	if (i == n)
		return ret = m - j;
	if (j == m)
		return ret = n - i;
	ret = 1 + min(bt(i + 1, j), bt(i, j + 1));
	if (s1[i] == s2[j])
		ret = min(ret, 1 + bt(i + 1, j + 1));
	return ret;
}

int main()
{
	cin >> n >> m >> s1 >> s2;
	memset(dp, -1, sizeof dp);
	string ans;
	int i = 0, j = 0;
	while (i < n || j < m)
	{
		if (i == n)
		{
			ans += s2.substr(j);
			j = m;
		}
		else if (j == m)
		{
			ans += s1.substr(i);
			i = n;
		}
		else if (s1[i] == s2[j])
			ans += s1[i++], j++;
		else if (bt(i + 1, j) < bt(i, j + 1))
			ans += s1[i++];
		else if (bt(i, j + 1) < bt(i + 1, j))
			ans += s2[j++];
		else if (s1[i] < s2[j])
			ans += s1[i++];
		else ans += s2[j++];
	}
	cout << ans << endl;
}
