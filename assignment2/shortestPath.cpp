#include <bits/stdc++.h>
using namespace std;



template <typename V, typename E>
class adjListGraph
{
    int vertices, edges;
    struct EdgeNode
    {
        int end;  // the index of endpoint
        E weight;  // the weight for the graph, it is set to 1 in all unweighted graphs
        EdgeNode* next;  // next pointer

        EdgeNode(int e = -1, E w = 0, EdgeNode* n = nullptr) : end(e), weight(w), next(n) {}
    };

    struct VertexNode //
    {
        V val;  // the node value
        EdgeNode* head;  // head pointer of corresponding list

        VertexNode(EdgeNode* h = nullptr) : head(h) {}

    };

    
    VertexNode* vertex_list;
    int* in_deg;
    int * out_deg;
    int find(const V& v) const {
        return v - 1;
    }
public:

    adjListGraph(int _size, const V d[]);
    adjListGraph(int _size);
    void insertMany(const int & edgeNum);
    void insert(V x, V y, E w);
    // bool exist(V x, V y) const;   // examine if an edge exists between the two nodes
    // std::vector<std::vector<V>> dfs() const;
    // std::vector<std::vector<V>> bfs() const;
    ~adjListGraph();

    E dijkstra(const V& x, const V& y) const;
    long long shortestPath(const int & source, const int & target) const;
};

template <typename V, typename E>
adjListGraph<V, E>::adjListGraph(int _size, const V d[]) : vertices(_size), edges(0)
{
    in_deg = new int[vertices] {0};
    out_deg = new int[vertices] {0};
    vertex_list = new VertexNode[vertices];
    for (int i = 0; i < vertices; ++i) {
        vertex_list[i].val = d[i];
    }
}
template <typename V, typename E>
adjListGraph<V, E>::adjListGraph(int _size) : vertices(_size), edges(0)
{
    in_deg = new int[vertices] {0};
    out_deg = new int[vertices] {0};
    vertex_list = new VertexNode[vertices];
    for (int i = 0; i < vertices; ++i) {
        vertex_list[i].val = i + 1;
    }
}

template <typename V, typename E>
adjListGraph<V, E>::~adjListGraph()
{
    int i;
    EdgeNode* p;
    for (i = 0; i < vertices; ++i) {

        while ((p = vertex_list[i].head))
        {
            vertex_list[i].head = p->next;
            delete p;
        }
    }
}
template <typename V, typename E>
void adjListGraph<V, E>::insert(V x, V y, E w) {
    int u = adjListGraph<V, E>::find(x), v = adjListGraph<V, E>::find(y);
    in_deg[v]++;
    ++out_deg[u];
    vertex_list[u].head = new EdgeNode(v, w, vertex_list[u].head); // 这句话保证了新插入的边对应的端点一定是最靠近顶点节点的
    ++edges;
}
template <typename V, typename E>
void adjListGraph<V, E>::insertMany(const int & edgeNum){

    int tempSource, tempTarget, tempWeight;
    
    for (int e = 0; e < edgeNum; ++e) {
        cin >> tempSource >> tempTarget >> tempWeight;

        insert(tempSource, tempTarget, tempWeight);
        insert(tempTarget, tempSource, tempWeight);
    }
}


template <typename V, typename E>
long long adjListGraph<V, E>::shortestPath(const int & source, const int & target) const {
    long long * sourceDistance = new long long[vertices];
    for (int i = 0; i < vertices; ++i) {
        sourceDistance[i] = LONG_LONG_MAX;
    }
    sourceDistance[source - 1] = 0;
    const VertexNode &sourceVertex = vertex_list[source - 1];
    EdgeNode* p = sourceVertex.head;
    while (p)
    {
        sourceDistance[p->end] = min(p->weight, sourceDistance[p->end]);
        p = p->next;
    }
    bool * isVisited = new bool[vertices]{false};
    isVisited[source - 1] = true;

    while (isVisited[target - 1] == false) {
        int minIndex;
        long long minDistance = LONG_LONG_MAX;
        for (int i = 0; i < vertices; ++i) {
            if (isVisited[i]) 
                continue;
            if (sourceDistance[i] < minDistance) {
                minDistance = sourceDistance[i];
                minIndex = i;
            }
        }
        isVisited[minIndex] = true;
        p = vertex_list[minIndex].head;
        while (p) {
            sourceDistance[p->end] = min(sourceDistance[p->end], p->weight + sourceDistance[minIndex]);
            p = p->next;
        }
    }
    return sourceDistance[target - 1];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int verticeNum, edgeNum, source, target;
    cin >> verticeNum >> edgeNum >> source >> target;
    adjListGraph<int, long long> graph(verticeNum);
    graph.insertMany(edgeNum);
    long long result = graph.shortestPath(source, target);
    cout << result << endl;
    return 0;
}