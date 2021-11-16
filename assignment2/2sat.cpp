#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MAXN 2000005
int n, m;
struct edge{
    int end;
    edge* next;
    edge(int _end, edge* _next=nullptr) : end(_end), next(_next) {}
} ;

struct node {
    int val;
    edge * head;
    node(int _v=-1, edge * h = nullptr) : val(_v), head(h) {

    }
} nodes[MAXN];





int dfn[MAXN] = {0}, low[MAXN] = {0}, dfncnt = 0, s[MAXN] = {0}, in_stack[MAXN] = {0}, tp = 0;
int scc[MAXN] = {0}, sc = 0;
int sz[MAXN]= {0};


void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt;
    s[++tp] = u;
    in_stack[u] = 1;
    edge* p = nodes[u].head;
    while (p) {
        const int & v = p->end;
        if (!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
        p = p->next;
    }
    if (dfn[u] == low[u]) {
        // find a SCC
        ++sc;
        while (s[tp] != u) {
            scc[s[tp]] = sc;
            sz[sc]++;
            in_stack[s[tp]] = 0;
            --tp;
        }
        scc[s[tp]] = sc;
        sz[sc]++;
        in_stack[s[tp]] = 0;
        --tp;
    }
}

void solve(){
    for (int i = 1; i <= 2 * n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    bool can = true;
    for (int i = 1; i <= 2 * n; i += 2) {
        if (scc[i] == scc[i + 1]) {
            can = false;
            break;
        }
    }
    if (!can) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        for (int i = 1; i <= 2 * n; i += 2) {
            if (scc[i] < scc[i + 1]) {
                cout << 1 << (i == 2 * n ? ("\n") : (" "));
            } else {
                cout << 0 << (i == 2 * n ? ("\n") : (" "));
            }
        }
    }
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int i, a, j, b;
    for (int _ = 0; _ < m; ++_) {
        cin >> i >> a >> j >> b;
        
        nodes[i * 2 - 1 + a].head = new edge(2 * j - 1 + (b ^ 1), nodes[i * 2 - 1 + a].head);
        nodes[j * 2 - 1 + b].head = new edge(2 * i - 1 + (a ^ 1), nodes[j * 2 - 1 + b].head);
    }
    solve();
    return 0;
}