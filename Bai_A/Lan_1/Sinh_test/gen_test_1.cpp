#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void test1() {
    ofstream fout("test1.in");

    int n = 100000;
    fout << n << '\n';

    // Dùng mt19937 (32-bit) là đủ cho kiểu int, không cần 64-bit
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // Nếu muốn giới hạn khoảng số (ví dụ từ -1 tỷ đến 1 tỷ) thì dùng uniform_int_distribution
    // Còn nếu muốn lấy toàn bộ dải của int thì để rng() tự sinh và ép kiểu
    for (int i = 0; i < n; i++) {
        int y = (int)rng(); // Tự động trải đều từ -2^31 đến 2^31 - 1

        // Nếu bạn THỰC SỰ muốn dòng sau phải luân phiên Dương - Âm - Dương - Âm:
        if (i & 1) {
            y = -abs(y); // Chắc chắn âm ở vị trí lẻ
        } else {
            y = abs(y);  // Chắc chắn dương ở vị trí chẵn
        }

        fout << y << '\n';
    }

    fout.close();
}

int main() {
    // Tối ưu tốc độ ghi file dữ liệu lớn
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test1();

    cout << "Da tao xong test1.in\n";

    return 0;
}
