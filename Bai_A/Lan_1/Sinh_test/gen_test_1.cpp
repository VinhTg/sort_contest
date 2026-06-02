#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void test1() {
    ofstream fout("test1.in");

    int n = 100000;
    fout << n << '\n';

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; i++) {
        int y = (int)rng();

        if (i & 1) {
            y = -abs(y);
        } else {
            y = abs(y);
        }

        fout << y << '\n';
    }

    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test1();

    cout << "Da tao xong test1.in\n";

    return 0;
}
