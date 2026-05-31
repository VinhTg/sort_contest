#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void test1() {
    ofstream fout("test1.in");

    int n = 10000;
    fout << n << '\n';

    mt19937 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    for (int i = 0; i < n; i++) {
        int y = rng() % 1000000;

        if (i & 1)
            y = -y;

        fout << y << '\n';
    }

    fout.close();
}

int main() {
    test1();
    return 0;
}