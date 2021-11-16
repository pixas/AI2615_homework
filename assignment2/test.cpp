#include <bits/stdc++.h>
using namespace std;

int n,m;
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
int main(){
    unordered_map<int, int> MyMap;
    cout << MyMap[1] << endl;
    
    cout << MyMap.count(1) << endl;
    node nodes[100];
    cout << nodes[0].v << " " << nodes[0].x << endl;
    
    return 0;
}