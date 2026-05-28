#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
const int MAX_BUF = 15000005;

char in_buf[MAX_BUF];
char out_buf[MAX_BUF];

int out_ptr = 0;

char* strings[MAXN];
int str_len[MAXN];

int idx1[MAXN];
int idx2[MAXN];

inline void flush_out() {
    fwrite(out_buf, 1, out_ptr, stdout);
    out_ptr = 0;
}

inline void fast_write(const char* s, int len) {
    memcpy(out_buf + out_ptr, s, len);
    out_ptr += len;
    out_buf[out_ptr++] = '\n';

    if (out_ptr > MAX_BUF - 200) {
        flush_out();
    }
}

inline int bucket(unsigned char c) {
    return c ? (c - 'a' + 1) : 0;
}

inline bool less_suffix(const char* a, const char* b, int depth) {
    a += depth;
    b += depth;

    while (*a == *b && *a) {
        ++a;
        ++b;
    }

    return *a < *b;
}

void insertion_sort(int* id, int n, int depth) {
    for (int i = 1; i < n; ++i) {
        int key = id[i];
        int j = i - 1;

        while (j >= 0 &&
               less_suffix(strings[key], strings[id[j]], depth)) {
            id[j + 1] = id[j];
            --j;
        }

        id[j + 1] = key;
    }
}

void msdRadix(int* src, int* dst, int n, int depth) {
    if (n <= 1) return;

    if (n <= 32) {
        insertion_sort(src, n, depth);
        return;
    }

    int count[27] = {};
    int start[27];
    int pos[27];

    for (int i = 0; i < n; ++i) {
        ++count[bucket((unsigned char)strings[src[i]][depth])];
    }

    start[0] = 0;
    for (int i = 1; i < 27; ++i) {
        start[i] = start[i - 1] + count[i - 1];
    }

    memcpy(pos, start, sizeof(start));

    for (int i = 0; i < n; ++i) {
        int v = src[i];
        dst[pos[bucket((unsigned char)strings[v][depth])]++] = v;
    }

    memcpy(src, dst, n * sizeof(int));

    for (int b = 1; b < 27; ++b) {
        int sz = count[b];

        if (sz > 1) {
            msdRadix(src + start[b],
                     dst + start[b],
                     sz,
                     depth + 1);
        }
    }
}

inline void write_int(int x) {
    char s[16];
    int len = 0;

    do {
        s[len++] = char('0' + x % 10);
        x /= 10;
    } while (x);

    while (len--) {
        out_buf[out_ptr++] = s[len];
    }

    out_buf[out_ptr++] = '\n';
}

int main() {
    size_t bytes = fread(in_buf, 1, MAX_BUF - 1, stdin);

    if (!bytes) return 0;

    in_buf[bytes] = '\0';

    int p = 0;
    int n = 0;

    while (in_buf[p] < '0' || in_buf[p] > '9') ++p;

    while (in_buf[p] >= '0' && in_buf[p] <= '9') {
        n = n * 10 + (in_buf[p++] - '0');
    }

    for (int i = 0; i < n; ++i) {
        while (in_buf[p] < 'a' || in_buf[p] > 'z') ++p;

        strings[i] = &in_buf[p];
        idx1[i] = i;

        int st = p;

        while (in_buf[p] >= 'a' && in_buf[p] <= 'z') ++p;

        str_len[i] = p - st;

        in_buf[p++] = '\0';
    }

    msdRadix(idx1, idx2, n, 0);

    write_int(n);

    for (int i = 0; i < n; ++i) {
        int id = idx1[i];
        fast_write(strings[id], str_len[id]);
    }

    if (out_ptr) flush_out();

    return 0;
}