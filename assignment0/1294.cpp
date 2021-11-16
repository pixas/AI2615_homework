#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    int a, b;
    for (int i = 0; i < T; ++i) {
        cin >> a >> b;
        cout << a + b << "\n";

    }
    return 0;
}
