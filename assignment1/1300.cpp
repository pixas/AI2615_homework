#include <bits/stdc++.h>
using namespace std;


const int N = 4e7 + 1;
int n, k;
int a[N];
int ans, k_th;
void read_input_data() {
    int m;
    cin >> n >> k >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    k_th = k;
    unsigned int z = a[m - 1];
    for (int i = m; i < n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
        // cout << a[i] << endl;
    }
}
/** \brief 三路快排 对于含有重复值的数组有很好的效果
 * \tparam T 这种类型必须重载了<运算符
 * \param nums 待排序的数组
 * \param len 数组的大小
 */
template <typename T>
void quickSort(T* nums, const int len)
{
    if (len <= 1) {
        ans = nums[0];
        return;
    }
    const T pivot = nums[rand() % len];
    // i 当前操作的元素
    // j 第一个等于pivot的元素
    // k 第一个大于pivot的元素
    int i = 0, j = 0, k = len;
    // 完成一趟三路快排，将序列分为：小于pivot的元素 ｜ 等于pivot的元素 ｜
    // 大于pivot的元素    
    while (i < k)
    {
        if (nums[i] < pivot){
            swap(nums[i++], nums[j++]);
        } else if (nums[i] > pivot) {
            swap(nums[i], nums[--k]);
        } else {
            ++i;
        }
    }
    if (k_th <= j) {
        quickSort(nums, j);
    }
    else if (k_th <= k) {
        ans = pivot;
    }
    else {
        k_th -= k;
        quickSort(nums + k, len - k);
    }
    // j -- the length of former array
    // len - k -- the length of latter array
    // quickSort(nums, j);
    // quickSort(nums + k, len - k);
}
// int kth_element(int a[], int start, int end, int k);
int main(){
    read_input_data();
    // for (int i = 0; i< n; ++i) {
    //     cout << a[i] << endl;
    // }
    quickSort(a, n);
    cout << ans << endl;

    return 0;
}

