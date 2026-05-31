#include <bits/stdc++.h>
#define taskname "C_"

using namespace std;

void gen() {
    int n = 9999; 
    cout << n << '\n';

    for (int i = 0; i < n; ++i) {
        int p_idx = i % 676;
        char c1 = 'z' - (p_idx / 26);
        char c2 = 'z' - (p_idx % 26);
        cout << c1 << c2;

        for (int j = 0; j < 97; ++j) {
            cout << 'b';
        }

        char suffix = 'z' - (i % 26);
        cout << suffix << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(taskname".inp", "w", stdout);

    gen();

    return 0;
}