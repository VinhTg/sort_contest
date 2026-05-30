#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 500000 + 5;
const int BUF_SIZE = 1 << 24;
const int INSERTION_SORT_THRESHOLD = 32;

char in_buf[BUF_SIZE];
char out_buf[BUF_SIZE];
int out_ptr = 0;

struct StringRef {
    char* s;
    int len;
};

StringRef arr[MAXN];
StringRef aux[MAXN];

inline int cmp_str(const StringRef& a, const StringRef& b, int d) {
    return strcmp(a.s + d, b.s + d);
}

inline void insertion_sort(StringRef* a, int n, int d) {
    for (int i = 1; i < n; i++) {
        StringRef tmp = a[i];
        int j = i - 1;

        while (j >= 0 && cmp_str(a[j], tmp, d) > 0) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = tmp;
    }
}

void msd_sort(StringRef* a, StringRef* aux, int l, int r, int d) {
    if (r - l <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(a + l, r - l, d);
        return;
    }

    int cnt[257] = {};

    // counting
    for (int i = l; i < r; i++) {
        cnt[(unsigned char)a[i].s[d] + 1]++;
    }

    // prefix sum
    for (int i = 1; i < 257; i++) {
        cnt[i] += cnt[i - 1];
    }

    int pos[257];
    memcpy(pos, cnt, sizeof(cnt));

    // distribute
    for (int i = l; i < r; i++) {
        unsigned char c = (unsigned char)a[i].s[d];
        aux[l + pos[c]++] = a[i];
    }

    // copy back
    memcpy(a + l, aux + l, (r - l) * sizeof(StringRef));

    // recurse
    for (int i = 0; i < 256; i++) {
        int L = l + cnt[i];
        int R = l + cnt[i + 1];

        if (R - L > 1) {
            msd_sort(a, aux, L, R, d + 1);
        }
    }
}

int main() {
    int bytes = fread(in_buf, 1, BUF_SIZE, stdin);
    if (bytes <= 0) return 0;

    int p = 0;
    int n = 0;

    // read n
    while (in_buf[p] < '0' || in_buf[p] > '9') p++;

    while (in_buf[p] >= '0' && in_buf[p] <= '9') {
        n = n * 10 + (in_buf[p++] - '0');
    }

    // read strings
    for (int i = 0; i < n; i++) {

        while (in_buf[p] <= 32) p++;

        arr[i].s = &in_buf[p];

        char* start = &in_buf[p];

        while (in_buf[p] > 32) p++;

        arr[i].len = &in_buf[p] - start;

        in_buf[p++] = '\0';
    }

    msd_sort(arr, aux, 0, n, 0);

    // output n
    char tmp[32];
    int len = sprintf(tmp, "%d\n", n);
    fwrite(tmp, 1, len, stdout);

    // output strings
    for (int i = 0; i < n; i++) {

        if (out_ptr + arr[i].len + 1 >= BUF_SIZE) {
            fwrite(out_buf, 1, out_ptr, stdout);
            out_ptr = 0;
        }

        memcpy(out_buf + out_ptr, arr[i].s, arr[i].len);

        out_ptr += arr[i].len;
        out_buf[out_ptr++] = '\n';
    }

    fwrite(out_buf, 1, out_ptr, stdout);

    return 0;
}