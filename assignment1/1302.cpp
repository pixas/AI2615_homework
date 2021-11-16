#include <iostream>
using namespace std;

int query(int x, int y);
void optimal_sort(int n);

int __qcnt = 0;
int __hidden_array[1025];
int query (int x, int y) {
    __qcnt ++;
    int d = __hidden_array[x] - __hidden_array[y];
    return d > 0 ? 1 : (d == 0 ? 0 : -1);
}
int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> __hidden_array[i];
    optimal_sort(n);
    std::cout << "number of queries : " << __qcnt << std::endl;
}

int ans[1025];
int ans_temp[1025];
void solve(int ll, int rr, int* temp){
    if (rr - ll <= 1) {
        // ans[ll] = ll;
        return;
    } 
    int mid = ll + (rr - ll >> 1);
    solve(ll, mid, temp);
    solve(mid, rr, temp);
    int p = ll, q = mid, k = ll; // p the pointer of left
    // q the pointer of right
    // k the pointer of temp
    while (k < rr) {
        if (p >= mid || q < rr && query(ans[p], ans[q]) == 1) {
            // int t = ans[q];
            // ans[q] = ans[k];
            // ans[k] = t;
            ans_temp[k++] = ans[q++];
            // temp[k++] = __hidden_array[q++];
            // q++;
        }
        else {
            // int t = ans[p];
            // ans[p] = ans[k];
            // ans[k] = t;
            ans_temp[k++] = ans[p++];
            // temp[k++] = __hidden_array[p++];
            // p++;
        }
    }
    for (int i = ll; i < rr; ++i) {
        ans[i] = ans_temp[i];
        // __hidden_array[i] = temp[i];
    }
}
void optimal_sort(int n) {
    for (int i = 1; i <= n; ++i) {
        ans[i] = i;
        ans_temp[i] = i;
    }
    if (n <= 1) {
        cout << ans[n] << '\n';
        return;
    }
    int * temp = new int[n + 1];
    solve(1, n + 1, temp);
    delete [] temp;
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << (i == n ? '\n' : ' ');
    }
    
}