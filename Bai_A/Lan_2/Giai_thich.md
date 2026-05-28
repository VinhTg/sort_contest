### Là T đã làm xuống còn 46ms nên là m phải làm lại phần giải thích này.

### M có thể làm theo hướng

### dựa trên thuật toán của code này:

```
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
```

### sẽ ra được code này:

```
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
const int MAX_BUF = 15000005;

char in_buf[MAX_BUF];
char out_buf[MAX_BUF];

int out_ptr = 0;
int p = 0;

inline void flush_out() {
    fwrite(out_buf, 1, out_ptr, stdout);
    out_ptr = 0;
}

inline void write_int(int x) {
    if (x == 0) {
        out_buf[out_ptr++] = '0';
        out_buf[out_ptr++] = '\n';
        if (out_ptr > MAX_BUF - 200) flush_out();
        return;
    }
    
    if (x < 0) {
        out_buf[out_ptr++] = '-';
    }
    
    unsigned int ux = (x < 0) ? -(unsigned int)x : (unsigned int)x;
    char s[16];
    int len = 0;
    
    do {
        s[len++] = char('0' + ux % 10);
        ux /= 10;
    } while (ux);

    while (len--) {
        out_buf[out_ptr++] = s[len];
    }
    out_buf[out_ptr++] = '\n';

    if (out_ptr > MAX_BUF - 200) flush_out();
}

inline void read_int(int &x) {
    while (in_buf[p] && in_buf[p] <= ' ') ++p;
    if (!in_buf[p]) return;
    
    bool neg = false;
    if (in_buf[p] == '-') {
        neg = true;
        ++p;
    }
    
    x = 0;
    while (in_buf[p] >= '0' && in_buf[p] <= '9') {
        x = x * 10 + (in_buf[p++] - '0');
    }
    
    if (neg) x = -x;
}

void radix_sort(int* arr, int n) {
    unsigned int* a = (unsigned int*)arr;
    unsigned int* b = new unsigned int[n];

    for (int i = 0; i < n; ++i) {
        a[i] ^= 0x80000000;
    }

    for (int shift = 0; shift < 32; shift += 8) {
        int cnt[256] = {0};
        
        for (int i = 0; i < n; ++i) {
            cnt[(a[i] >> shift) & 0xFF]++;
        }
        
        for (int i = 1; i < 256; ++i) {
            cnt[i] += cnt[i - 1];
        }
        
        for (int i = n - 1; i >= 0; --i) {
            b[--cnt[(a[i] >> shift) & 0xFF]] = a[i];
        }
        
        memcpy(a, b, n * sizeof(unsigned int));
    }

    for (int i = 0; i < n; ++i) {
        a[i] ^= 0x80000000;
    }

    delete[] b;
}

int arr[MAXN];

int main() {
    size_t bytes = fread(in_buf, 1, MAX_BUF - 1, stdin);
    if (!bytes) return 0;
    in_buf[bytes] = '\0';

    int n;
    read_int(n);

    for (int i = 0; i < n; ++i) {
        read_int(arr[i]);
    }

    radix_sort(arr, n);

    write_int(n);
    for (int i = 0; i < n; ++i) {
        write_int(arr[i]);
    }

    if (out_ptr) flush_out();

    return 0;
}
```

### Sau đó tối ưu thêm việc nhập xuất sao cho nhanh thì ra được thuật toán tối ưu nhất này:
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