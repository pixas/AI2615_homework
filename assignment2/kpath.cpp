#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
long long n, m, s, t, k, x, y, ww, cnt, fa[maxn];
struct Edge
{
    int cur, h[maxn * 2], nxt[maxn * 2], p[maxn * 2], w[maxn * 2];
    void add_edge(int x, int y, int z)
    {
        cur++;
        nxt[cur] = h[x];
        h[x] = cur;
        p[cur] = y;
        w[cur] = z;
    }
} e1, e2;

long long dist[maxn];
bool tf[maxn], vis[maxn], ontree[maxn];
struct node
{
    long long x, v;
    node *operator=(node a)
    {
        x = a.x;
        v = a.v;
        return this;
    }
    bool operator<(node a) const { return v > a.v; }
} a;
priority_queue<node> Q;
void dfs(long long x)
{
    vis[x] = true;
    for (long long j = e2.h[x]; j; j = e2.nxt[j])
        if (!vis[e2.p[j]])
            if (dist[e2.p[j]] == dist[x] + e2.w[j])
                fa[e2.p[j]] = x, ontree[j] = true, dfs(e2.p[j]);
}
struct LeftistTree
{
    long long cnt, rt[maxn];
    // node v[maxn * 20];
    unordered_map<long long, long long> lc;
    unordered_map<long long, long long> rc;
    unordered_map<long long, long long> dist;
    unordered_map<int, node> v;
    LeftistTree() { dist[0] = -1; }
    long long newnode(node w)
    {
        cnt++;
        v[cnt] = w;
        return cnt;
    }
    long long merge(long long x, long long y)
    {
        if (!x || !y)
            return x + y;
        if (v[x] < v[y])
            swap(x, y);
        long long p = ++cnt;
        lc[p] = lc[x];
        v[p] = v[x];
        rc[p] = merge(rc[x], y);
        if (dist[lc[p]] < dist[rc[p]])
            swap(lc[p], rc[p]);
        dist[p] = dist[rc[p]] + 1;
        return p;
    }
} st;
void dfs2(int x)
{
    vis[x] = true;
    if (fa[x])
        st.rt[x] = st.merge(st.rt[x], st.rt[fa[x]]);
    for (int j = e2.h[x]; j; j = e2.nxt[j])
        if (fa[e2.p[j]] == x && !vis[e2.p[j]])
            dfs2(e2.p[j]);
}
int main()
{
    cnt = 0;
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &x, &y, &ww), e1.add_edge(x, y, ww), e2.add_edge(y, x, ww);


    Q.push({t, 0});
    while (!Q.empty())
    {
        a = Q.top();
        Q.pop();
        if (tf[a.x])
            continue;
        tf[a.x] = true;
        dist[a.x] = a.v;
        for (int j = e2.h[a.x]; j; j = e2.nxt[j])
            Q.push({e2.p[j], a.v + e2.w[j]});
    }
    long long last_path = -1;

    if (tf[s])
        printf("%ld ", dist[s]);
    cnt++;
    last_path = dist[s];

    dfs(t);
    for (int i = 1; i <= n; i++)
        if (tf[i])
            for (int j = e1.h[i]; j; j = e1.nxt[j])
                if (!ontree[j])
                    if (tf[e1.p[j]])
                        st.rt[i] = st.merge(
                            st.rt[i],
                            st.newnode({e1.p[j], dist[e1.p[j]] + e1.w[j] - dist[i]}));
    for (int i = 1; i <= n; i++)
        vis[i] = false;
    dfs2(t);
    if (st.rt[s])
        Q.push({st.rt[s], dist[s] + st.v[st.rt[s]].v});
    
    while (!Q.empty())
    {
        a = Q.top();
        Q.pop();
        if (cnt == k) break;
        if (cnt <= k - 1 && a.v > last_path)
        {
            printf("%ld%s", a.v, (cnt == k - 1 ? ("\n") : (" ")));
            last_path = a.v;
        }
        else if (cnt <= k - 1 && a.v == last_path)
        {
            cnt--;
        }

        cnt++;
        // if (cnt == k - 1)
        // {
        //     printf("%d\n", a.v);
        //     return 0;
        // }
        if (st.lc[a.x])
            Q.push({st.lc[a.x], a.v - st.v[a.x].v + st.v[st.lc[a.x]].v});
        if (st.rc[a.x])
            Q.push({st.rc[a.x], a.v - st.v[a.x].v + st.v[st.rc[a.x]].v});
        x = st.rt[st.v[a.x].x];
        if (x)
            Q.push({x, a.v + st.v[x].v});
    }
    if (cnt <= k - 1) {
        for (int i = cnt; i < k; ++i) {
            printf("%d%s", -1, (i == k - 1 ? ("\n") : (" ")));
        }
    }

    // printf("%d\n", cnt);
    return 0;
}