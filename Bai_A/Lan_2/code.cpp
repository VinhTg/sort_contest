#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
const int MAX_BUF = 2000005;

char in_buf[MAX_BUF];
char out_buf[MAX_BUF];

int out_ptr = 0;
int p = 0;

inline void write_int(int x) {
    unsigned int ux;
    if (x < 0) {
        out_buf[out_ptr++] = '-';
        ux = -(unsigned int)x;
    } else {
        ux = x;
    }
    
    char s[12];
    int len = 0;
    
    do {
        s[len++] = ux % 10 + '0';
        ux /= 10;
    } while (ux);

    while (len) {
        out_buf[out_ptr++] = s[--len];
    }
    out_buf[out_ptr++] = '\n';
}

inline void read_int(int &x) {
    while (in_buf[p] < '-') ++p;
    
    bool neg = (in_buf[p] == '-');
    if (neg) ++p;
    
    x = 0;
    while (in_buf[p] >= '0') {
        x = x * 10 + (in_buf[p++] - '0');
    }
    
    if (neg) x = -x;
}

unsigned int arr_a[MAXN];
unsigned int arr_b[MAXN];

void radix_sort(int n) {
    int cnt[4][256] = {{0}};
    
    for (int i = 0; i < n; ++i) {
        arr_a[i] ^= 0x80000000;
        unsigned int v = arr_a[i];
        cnt[0][v & 0xFF]++;
        cnt[1][(v >> 8) & 0xFF]++;
        cnt[2][(v >> 16) & 0xFF]++;
        cnt[3][v >> 24]++;
    }

    int pos[4][256];
    for (int j = 0; j < 4; ++j) {
        pos[j][0] = 0;
        for (int i = 1; i < 256; ++i) {
            pos[j][i] = pos[j][i - 1] + cnt[j][i - 1];
        }
    }

    for (int i = 0; i < n; ++i) {
        arr_b[pos[0][arr_a[i] & 0xFF]++] = arr_a[i];
    }
    
    for (int i = 0; i < n; ++i) {
        arr_a[pos[1][(arr_b[i] >> 8) & 0xFF]++] = arr_b[i];
    }
    
    for (int i = 0; i < n; ++i) {
        arr_b[pos[2][(arr_a[i] >> 16) & 0xFF]++] = arr_a[i];
    }
    
    for (int i = 0; i < n; ++i) {
        arr_a[pos[3][arr_b[i] >> 24]++] = arr_b[i];
    }

    for (int i = 0; i < n; ++i) {
        arr_a[i] ^= 0x80000000;
    }
}

int main() {
    size_t bytes = fread(in_buf, 1, MAX_BUF - 1, stdin);
    if (!bytes) return 0;
    in_buf[bytes] = '\0';

    int n;
    read_int(n);

    for (int i = 0; i < n; ++i) {
        read_int((int&)arr_a[i]);
    }

    radix_sort(n);

    write_int(n);
    for (int i = 0; i < n; ++i) {
        write_int((int)arr_a[i]);
    }

    fwrite(out_buf, 1, out_ptr, stdout);

    return 0;
}