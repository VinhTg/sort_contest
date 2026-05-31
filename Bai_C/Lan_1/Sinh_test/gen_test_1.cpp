#include <bits/stdc++.h>
#define taskname "C_"

using namespace std;
using ll = long long;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void gen()
{
    int n = 9999; 
    cout << n << '\n';

    for (int i = 0; i < n; ++i) {
        int current_pair_idx = i % 676;

        char c1 = 'z' - (current_pair_idx / 26);
        char c2 = 'z' - (current_pair_idx % 26);

        cout << c1 << c2;

        int m = 100; 
        for (int j = 1; j <= m; ++j) {
            cout << 'a';
        }
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(taskname".inp", "w", stdout);

    gen();

    return 0;
}