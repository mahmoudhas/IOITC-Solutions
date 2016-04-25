#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
const int mod = 1000000007;

int modpow(int x, int y)
{
    if (y == 0) return 1;
    if (y == 1) return x;
    int a = modpow(x, y/2);
    int ret;
    if (y % 2 == 0)
        ret = 1LL * a * a % mod;
    else ret = 1LL * a * a * x % mod;
    return ret;
}

int n, m, q;
vector<int> adj[MAXN];
int group[MAXN];

int invalid, oneway;

int color[MAXN];
int ncolors[2][MAXN][2];
int p[MAXN], size[MAXN];
int ncomponents;
int find(int i) { return p[i] == i ? i : p[i] = find(p[i]); }

int countcolors(int u)
{
    u = find(u);
    int ret = 0;
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
        ret += ncolors[i][u][j];
    return ret;
}
bool isInvalid(int u)
{
    u = find(u);
    for (int i = 0; i < 2; i++)
        if ((ncolors[i][u][0] && ncolors[i][u][1]) || (ncolors[0][u][i] && ncolors[1][u][i]))
            return true;
    return false;
}
void dfs(int u, int cur)
{
    if (group[u] == cur) return;
    group[u] = cur;
    if (color[u] != -1)
    {
        int pu = find(u);
        ncolors[color[u]][pu][cur]++;
    }
    for (int i = 0; i < adj[u].size(); i++)
        dfs(adj[u][i], !cur);
}
void merge(int u, int v)
{
    int pu = find(u), pv = find(v);
    if (pu == pv) return;
    if (size[pu] > size[pv])
    {
        swap(u, v);
        pu = find(u);
        pv = find(v);
    }
    invalid -= isInvalid(pu);
    invalid -= isInvalid(pv);
    oneway -= countcolors(pu) > 0;
    oneway -= countcolors(pv) > 0;
    if (group[u] != !group[v])
    {
        for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
            ncolors[i][pu][j] = 0;
        dfs(u, !group[v]);
    }
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
        ncolors[i][pv][j] += ncolors[i][pu][j];
    p[pu] = pv;
    size[pv] += size[pu];
    ncomponents--;
    invalid += isInvalid(pv);
    oneway += countcolors(pv) > 0;
}

void quncolor(int u)
{
    if (color[u] == -1) return;
    int pu = find(u);
    int g = group[u];
    oneway -= countcolors(pu) > 0;
    invalid -= isInvalid(pu);
    ncolors[color[u]][pu][g]--;
    invalid += isInvalid(pu);
    oneway += countcolors(pu) > 0;
    color[u] = -1;
}

void qcolor(int u, int cl)
{
    if (color[u] == cl) return;
    quncolor(u);
    int pu = find(u);
    int g = group[u];
    oneway -= countcolors(pu) > 0;
    invalid -= isInvalid(pu);
    ncolors[cl][pu][g]++;
    invalid += isInvalid(pu);
    oneway += countcolors(pu) > 0;
    color[u] = cl;
}

char s[2];
int k1, k2;

int main()
{
    memset(color, -1, sizeof color);
    scanf("%d%d%d%d%d", &n, &m, &q, &k1, &k2);
    assert(n % 2 == 0);
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        size[i] = 1;
    }
    ncomponents = n;
    for (int i = 0; i < k1; i++)
    {
        int x;
        scanf("%d", &x);
        qcolor(x, 0);
    }
    for (int i = 0; i < k2; i++)
    {
        int x;
        scanf("%d", &x);
        qcolor(x, 1);
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        merge(u, v);
    }

    while (q--)
    {
        int t;
        scanf("%d", &t);
        if (t == 0)
        {
            int u; char cl;
            scanf("%d%s", &u, s);
            cl = s[0];
            if (cl == 'U')
                quncolor(u);
            else qcolor(u, cl == 'B');
        }
        else if (t == 1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
            merge(u, v);
        }
        else if (t == 2)
        {
            if (invalid)
                puts("0");
            else printf("%d\n", modpow(2, ncomponents - oneway));
        }
    }
}
