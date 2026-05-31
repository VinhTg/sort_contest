#include <bits/stdc++.h>
#define taskname "C_"

using namespace std;

void gen() {
    int n = 9999; 
    cout << n << '\n';

    for (int i = 0; i < n; ++i) {
        int group = i / 25; 
        
        char c1 = 'z';
        
        char c2 = 'd' - (group % 26);
        if (c2 < 'a') c2 = 'z' - ('a' - c2 - 1); 
        char c3 = 'h';

        cout << c1 << c2 << c3;

        for (int j = 0; j < 97; ++j) {
            cout << 'c';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(taskname".inp", "w", stdout);

    gen();

    return 0;
}