#include <iostream>
#include <fstream>

using namespace std;

void test2() {
    ofstream fout("test2.in");

    int n = 100000;
    fout << n << '\n';

    for (int i = 0; i < n; i++) {
        int x = i * 256;

        if (i & 1)
            x = -x;

        x ^= (i << 16);

        fout << x << '\n';
    }

    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test2();

    cout << "Da tao xong test2.in\n";

    return 0;
}