#include <bits/stdc++.h>
using namespace std;



int n,m;

void print(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << a[i] << (i == n - 1 ? "" : " ");
    }
    cout << '\n';
}
void print(int a[], int l, int r) {
    for (int i = l; i <= r; ++i) {
        cout << a[i] << (i == r ? "" : " ");
    }
    cout << '\n';
}
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int* bubble_sort(int a[], int n) {
    int * res = new int[n + 1] {0};
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                res[a[j]]++;
                res[a[j+1]]++;
            }
        } // after i-th inner iteration, a[n - i] is correct
        // print(a, n);
    }
    return res;
}

template <typename T>
void merge(T* nums, int ll, int rr, T* temp, int * inverse)
{
    if (rr - ll <= 1) return;
    int mid = ll + (rr - ll >> 1);
    merge(nums, ll, mid, temp, inverse);
    merge(nums, mid, rr, temp, inverse);
    int p = ll, q = mid, k = ll; // p the pointer of left
    // q the pointer of right
    // k the pointer of temp
    while (k < rr) {
        if (p >= mid || q < rr && nums[p] > nums[q]) {
            inverse[nums[q]] += mid - p;
            temp[k++] = nums[q++];
        }
        else {
            temp[k++] = nums[p++];
        }
    }
    for (int i = ll; i < rr; ++i) nums[i] = temp[i];
}
template <typename T>
void mergeSort(T* nums, int n, int * inverse)
{
    if (n <= 1) return;
    T* temp = new T[n];
    merge(nums, 0, n, temp, inverse);
    delete [] temp;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int * nums = new int[n + 1];
    int * mapping = new int [n + 1];
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        mapping[nums[i]] = i + 1;
    }
    int * inverse = new int [n + 1] {0};
    mergeSort(nums, n, inverse);
    int * ans = new int[n + 1];
    for (int i = 1; i <= n; ++i) {
        ans[i] = i - mapping[i] + 2 * inverse[i];
    }
    // int * res = bubble_sort(nums, n);
    print(ans, 1, n);
    // print(mapping, n + 1);
    // print(res, 1, n);
    delete [] nums;
    delete [] ans;
    delete [] inverse;
    delete [] mapping;
    return 0;
}