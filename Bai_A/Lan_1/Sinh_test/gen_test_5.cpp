#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main() {
    ofstream fout("test5.in");

    int n = 100000;

    fout << n << '\n';

    mt19937 rng(123456789);

    for (int i = 0; i < n; i++) {

        unsigned int x = rng();

        x ^= (rng() << 8);
        x ^= (rng() << 16);

        int y = (int)x;

        if (i & 1)
            y = -y;

        fout << y << '\n';
    }

    fout.close();

    cout << "Da tao xong test5.in\n";

    return 0;
}