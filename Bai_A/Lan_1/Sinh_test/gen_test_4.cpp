#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout("test4.in");

    fout << 1 << '\n';
    fout << -2147483648 << '\n';

    fout.close();

    cout << "Da tao xong test4.in\n";

    return 0;
}