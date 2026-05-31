#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void test1() {
    ofstream fout("test1.in");

    int n = 100000;
    fout << n << '\n';

    // Khởi tạo bộ sinh số ngẫu nhiên chuẩn 64-bit để tránh tràn bit khi dịch
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; i++) {
        // Lấy 1 lần giá trị ngẫu nhiên duy nhất
        unsigned long long random_val = rng();

        // Xáo trộn bit bằng các hằng số dịch bit nhanh (Bitwise shift)
        random_val ^= (random_val << 13);
        random_val ^= (random_val >> 7);
        random_val ^= (random_val << 17);

        int y = (int)(random_val & 0xFFFFFFFF); // Ép về kiểu int 32-bit

        // Đổi dấu luân phiên
        if (i & 1)
            y = -y;

        // XOR với hằng số FNV-1a để triệt tiêu tính tuần hoàn
        y ^= (i * 16777619);

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