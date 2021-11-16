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
    int prevNode;
    node(int _val=0, long long _dist=INT_MAX) : val(_val), dist(_dist), head(nullptr) {
        isVisited = false;
        prevNode = -1;
    }
    bool operator>(const node& n) const {
        return dist > n.dist;
    }

};

void insert(node * vertexArray, int s, int t, long long w){
    vertexArray[s].head = new edge(t, w, vertexArray[s].head);
}
int main(){
    int n,m;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    node * vertexArray = new node[n + 1];
    int tempSource, tempTarget;
    long long tempWeight;
    for (int i = 0; i < n; ++i) {
        vertexArray[i + 1].val = i + 1;
        vertexArray[i + 1].prevNode = 0;
        vertexArray[i + 1].dist = 0;
        insert(vertexArray, 0, i + 1, 0);
    }
    for (int i = 0; i < m; ++i) {
        cin >> tempSource >> tempTarget >> tempWeight;
        insert(vertexArray, tempSource, tempTarget, tempWeight);
    }
    vertexArray[0].dist = 0;
    edge * p;
    node * cyclableNode;
    bool isModified;
    for (int loop = 0; loop < n + 1; ++loop) {
        isModified = false;

        for (int ver = 1; ver < n + 1; ++ver) {
            node& currentNode = vertexArray[ver];
            p = currentNode.head;
            while (p) {
                if (currentNode.dist + p->weight < vertexArray[p->end].dist) {
                    isModified = true;
                    vertexArray[p->end].prevNode = currentNode.val;
                    vertexArray[p->end].dist = currentNode.dist + p->weight ;
                    if (loop == n){
                        cyclableNode = &vertexArray[p->end];
                        
                    }
                }
                p = p->next;
            }
        }
    }


    if (!isModified) {
        cout << "No" << endl;
    } else {
        
        int * outputCycle = new int[n + 5];
        node * cur = cyclableNode;
        int cycleIndex = n + 4;
        outputCycle[cycleIndex] = cur->val;
        cur->isVisited == true;
        cur = &vertexArray[cur->prevNode];
  
        while (cur->prevNode != 0 && cur->isVisited == false) {
            cur->isVisited = true;
            outputCycle[--cycleIndex] = cur->val;
            cur = &vertexArray[cur->prevNode];
        }
        outputCycle[--cycleIndex] = cur->val;
        int startVal = cur->val;
        int startIndex = cycleIndex;

        int cycleNum = 1;
        for (int i = startIndex + 1; outputCycle[i] != startVal; ++i) {
            cycleNum++;
        }


        cout << "Yes" << endl;
        cout << cycleNum << endl;
        for (int i = 0; i < cycleNum; ++i) {
            cout << outputCycle[startIndex + i] << (i == cycleNum - 1 ? "\n" : " ");
        }
        delete [] outputCycle;
    }

    for (int i = 0; i < n + 1; ++i) {

        while ((p = vertexArray[i].head))
        {
            vertexArray[i].head = p->next;
            delete p;
        }
    }
    delete [] vertexArray;
    return 0;
}