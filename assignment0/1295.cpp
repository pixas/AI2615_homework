#include <bits/stdc++.h>
using namespace std;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    if (n < 2) {
        cout << 0 << '\n';
        return 0;
    }
    
    if (n > (1<<20)) {
        cout << 0 << '\n';
        return 0;
    }
    bool * notPrime = new bool[n + 1] {false};
    int * primeNum = new int[n + 1] {0};

    // for (size_t i = 0; i < n + 1; i++)
    // {
    //     /* code */
    //     cout << notPrime[i] << endl;
    // }
    
    long long total = 0;
    for (int i = 2; i <= n; ++i) {
        if (notPrime[i] == false) {
            primeNum[++primeNum[0]] = i;
            // this number is a prime number
            total++;
        }
        for (int j = 1; j <= primeNum[0] && i * primeNum[j] <= n; ++j) {
            notPrime[i * primeNum[j]] = true;
            if (i % primeNum[j] == 0) {
                break;
            }
        }
    }

    // cout << total << '\n';
    cout << 2. * total / n / n << '\n';
    delete [] primeNum;
    delete [] notPrime;
    return 0;
}