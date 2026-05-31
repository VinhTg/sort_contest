#include <bits/stdc++.h>
#define taskname "C_"

using namespace std;

void gen() {
    int n = 9999; 
    cout << n << '\n';

    for (int i = 0; i < n; ++i) {
        int char1_idx = (i / 24) % 26;
        char c1 = 'a' + char1_idx;
        cout << c1;

        cout << 'f';

        for (int j = 0; j < 97; ++j) {
            cout << 'e';
        }
        char suffix = 'z' - (i % 24);
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