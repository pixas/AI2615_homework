#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)


const long long maxn = 100001;
const long long maxm = 200001;
const long long inf = LONG_LONG_MAX;
long long n, m, s, t, k, u, v, ww, H[maxn], cnt[maxn];
long long cur, h[maxn], nxt[maxm], p[maxm], w[maxm];
long long cur1, h1[maxn], nxt1[maxm], p1[maxm], w1[maxm];
bool tf[maxn];
void add_edge(int x, int y, long long z)
{
    if (p[x] == y && w[x] == z) {
        return;
    }
    cur++;
    nxt[cur] = h[x];
    h[x] = cur;
    p[cur] = y;
    w[cur] = z;
}
void add_edge1(int x, int y, long long z)
{
    if (p1[x] == y && w1[x] == z) return;
    cur1++;
    nxt1[cur1] = h1[x];
    h1[x] = cur1;
    p1[cur1] = y;
    w1[cur1] = z;
}
struct node
{
    long long x, v;
    bool operator<(node a) const { return v + H[x] > a.v + H[a.x]; }
};
priority_queue<node> q;
struct node2
{
    long long x, v;
    bool operator<(node2 a) const { return v > a.v; }
} y;
priority_queue<node2> Q;

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    while (m--)
    {
        scanf("%d%d%d", &u, &v, &ww);
        add_edge(u, v, ww);
        add_edge1(v, u, ww);
    }
    for (int i = 1; i <= n; i++)
        H[i] = inf;
    Q.push({t, 0});
    while (!Q.empty())
    {
        y = Q.top();
        Q.pop();
        if (tf[y.x])
            continue;
        tf[y.x] = true;
        H[y.x] = y.v;
        for (long long j = h1[y.x]; j; j = nxt1[j])
            Q.push({p1[j], y.v + w1[j]});
    }
    q.push({s, 0});
    long long last_path = LONG_LONG_MIN;
    int total_output = 0;
    int overall_output = k;
    while (!q.empty() && total_output < overall_output)
    {
        node x = q.top();
        // printf("%d %d\n", x.x, x.v);
        q.pop();
        
        
        if (x.x == t && x.v > last_path)
        {
            printf("%ld ", x.v);
            total_output++;
            last_path = x.v;
            
        }
        // if (x.x == t && x.v == last_path) {
        //     k++;
            
        // }
        cnt[x.x]++;
        if (cnt[x.x] > total_output + 1)
            continue;
        for (long long j = h[x.x]; j; j = nxt[j])
            q.push({p[j], x.v + w[j]});
    }
    // printf("%d\n", total_output);
    for (int i = total_output; i < overall_output; ++i) {
        printf("%d ", -1);
    }
    
    printf("\n");
    return 0;
}