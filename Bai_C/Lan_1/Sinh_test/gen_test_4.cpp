#include <bits/stdc++.h>
#define taskname "C_"

using namespace std;

void gen() {
    int n = 9999; 
    cout << n << '\n';

    for (int i = 0; i < n; ++i) {
        cout << "qwert";

        int group = i / 25;
        char c6 = 'n' - (group % 14);
        if (c6 < 'a') c6 = 'z';
        cout << c6;

        cout << 'b';

        for (int j = 0; j < 90; ++j) {
            cout << 'd';
        }

        char suffix = 'a' + (i % 26);
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