#include <bits/stdc++.h>
using namespace std;

struct edge{
    int end;
    long long weight;
    edge* next;
    edge(int _end, long long _weight, edge* _next=nullptr) : end(_end), weight(_weight), next(_next) {}
};

struct node{
    int val;
    long long dist;
    edge * head;
    bool isVisited;
    node(int _val=0, long long _dist=LONG_LONG_MAX) : val(_val), dist(_dist), head(nullptr) {
        isVisited = false;
    }
    bool operator>(const node& n) const {
        return dist > n.dist;
    }
};

int n,m;
int source, target;
void insert(node * vertexArray, int s, int t, long long w){
    vertexArray[s].head = new edge(t, w, vertexArray[s].head);
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> source >> target;
    source--;
    target--;
    node * vertexArray = new node[n];

    int tempSource, tempTarget;
    long long tempWeight;
    for (int i = 0; i < m; ++i) {
        cin >> tempSource >> tempTarget >> tempWeight;
        insert(vertexArray, tempSource - 1, tempTarget - 1, tempWeight);
        insert(vertexArray, tempTarget - 1, tempSource - 1, tempWeight);
    }

    priority_queue<node, vector<node>, greater<node>> q;
    // long long* sourceDistance = new long long[n];
    // for (int i = 0; i < n; ++i) {
    //     vertexArray[i].dist = LONG_LONG_MAX;
    // }
    vertexArray[source].dist = 0;
    
    q.push(vertexArray[source]);

    while (!q.empty()) {
        node currentNode = q.top();
        q.pop();
        if (currentNode.isVisited) continue;
        currentNode.isVisited = true;
        edge* p = currentNode.head;
        while (p) {
            if (p->weight + currentNode.dist < vertexArray[p->end].dist) {
                vertexArray[p->end].dist = p->weight + currentNode.dist;
                q.push(vertexArray[p->end]);
            }
            
            p = p->next;
        }

    }
    cout << vertexArray[target].dist << endl;
    return 0;
}