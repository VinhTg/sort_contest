#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ofstream fout("test3.in");

    int n = 100000;

    fout << n << '\n';

    mt19937 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    for (int i = 0; i < n; i++) {

        unsigned int x = rng();

        x ^= (rng() << 8);
        x ^= (rng() << 16);

        int y = (int)x;

        if (i & 1)
            y = -y;

        y ^= (i * 16777619);

        fout << y << '\n';
    }

    fout.close();

    cout << "Da tao xong test3.in\n";

    return 0;
}