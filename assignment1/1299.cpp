#include <bits/stdc++.h>
using namespace std;

int n,m;

struct Point
{
    long long x, y;
    Point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
};

long long distance(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
long long closed_pt(Point * nums, int left, int right);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    Point* nums = new Point[n];
    // int a, b;
    for (int i = 0; i < n; ++i) {
        // cin >> a >> b;
        cin >> nums[i].x >> nums[i].y;
    }
    sort(nums, nums + n, [](const Point& a, const Point& b) -> bool {return a.x < b.x; });
    long long res = closed_pt(nums, 0, n - 1);
    cout << res << '\n';

    delete [] nums;
    return 0;
}


long long closed_pt(Point* nums, int left, int right) {
    // int n = right - left + 1;
    if (left == right) {
        return LONG_LONG_MAX;
    }
    // if (right - left == 1) {
    //     return distance(nums[left], nums[right]);
    // }
    // if (n == 3) {
    //     return min(distance(nums[0], nums[1]), min(distance(nums[0], nums[1]), distance(nums[1], nums[2])));
    // }
    
    int mid = left + (right - left) / 2;
    long long left_min = closed_pt(nums, left, mid);
    long long right_min = closed_pt(nums, mid + 1, right);
    long long cur_min = min(left_min, right_min);

    Point* res = new Point[right - left + 1];
    int i, k = 0;
    for (i = left; i <= right; ++i) {
        if ((nums[i].x - nums[mid].x) * (nums[i].x - nums[mid].x) < cur_min) {
            res[k++] = nums[i]; 
        }
    }
    sort(res, res + k, [](const Point& a, const Point& b) -> bool {return a.y < b.y;});
    int j;
    
    for (i = 0; i < k; ++i) {
        for (j = i + 1; j < k && (res[i].y - res[j].y) * (res[i].y - res[j].y) < cur_min; ++j) {
            long long temp = distance(res[i], res[j]);
            if (temp < cur_min) {
                cur_min = temp;
            } 
        }
    }



    delete [] res;

    return cur_min;
}