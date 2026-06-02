#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ofstream fout("test3.in");
    if (!fout.is_open()) return 1;

    int n = 100000;
    fout << n << '\n';

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> dist(0, 2147483647);

    for (int i = 0; i < n; i++) {
        long long temp = dist(rng);

        if (i % 2 != 0) {
            temp = -temp;
        }

        // Bản chất phép toán này sẽ tự động ép phẳng vào dải 'int' khi ghi ra file
        int y = temp + (i * 16777619LL);

        fout << y << '\n';
    }

    fout.close();
    cout << "Da tao xong test3.in\n";

    return 0;
}