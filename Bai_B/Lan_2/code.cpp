#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
const int MAX_BUF = 15000000;
char in_buf[MAX_BUF];
char out_buf[MAX_BUF];
int out_ptr = 0;

char* strings[MAXN];
int str_len[MAXN];
int idx[MAXN], tidx[MAXN];
int bucket_map[256];

inline void fast_write(const char* s, int len) {
    memcpy(&out_buf[out_ptr], s, len);
    out_ptr += len;
    out_buf[out_ptr++] = '\n';
    if (out_ptr > MAX_BUF - 200) {
        fwrite(out_buf, 1, out_ptr, stdout);
        out_ptr = 0;
    }
}

void msdRadix(int* id, int* td, int n, int depth) {
    if (n <= 1) return;

    if (n <= 32) {
        for (int i = 1; i < n; ++i) {
            int key = id[i];
            int j = i - 1;
            while (j >= 0 && strcmp(strings[id[j]] + depth, strings[key] + depth) > 0) {
                id[j + 1] = id[j];
                --j;
            }
            id[j + 1] = key;
        }
        return;
    }

    int count[28] = {0};
    for (int i = 0; i < n; ++i) {
        count[bucket_map[(unsigned char)strings[id[i]][depth]]]++;
    }

    int start[28];
    start[0] = 0;
    for (int i = 1; i <= 27; ++i) start[i] = start[i - 1] + count[i - 1];

    int pos[28];
    memcpy(pos, start, sizeof(start));
    for (int i = 0; i < n; ++i) {
        int item = id[i];
        td[pos[bucket_map[(unsigned char)strings[item][depth]]]++] = item;
    }

    memcpy(id, td, n * sizeof(int));

    for (int b = 1; b <= 26; ++b) {
        if (count[b] > 1) {
            msdRadix(id + start[b], td + start[b], count[b], depth + 1);
        }
    }
}

int main() {
    size_t bytes = fread(in_buf, 1, MAX_BUF, stdin);
    if (bytes <= 0) return 0;
    in_buf[bytes] = '\0';

    bucket_map[0] = 0;
    for (int c = 'a'; c <= 'z'; ++c) {
        bucket_map[c] = c - 'a' + 1;
    }

    int p = 0;
    int n = 0;
    while (in_buf[p] < '0' || in_buf[p] > '9') p++;
    while (in_buf[p] >= '0' && in_buf[p] <= '9') n = n * 10 + (in_buf[p++] - '0');

    for (int i = 0; i < n; ++i) {
        while (in_buf[p] != '\0' && (in_buf[p] < 'a' || in_buf[p] > 'z')) p++;
        strings[i] = &in_buf[p];
        idx[i] = i;
        int start_p = p;
        while (in_buf[p] >= 'a' && in_buf[p] <= 'z') p++;
        str_len[i] = p - start_p;
        in_buf[p++] = '\0';
    }

    msdRadix(idx, tidx, n, 0);

    out_ptr = sprintf(out_buf, "%d\n", n);
    for (int i = 0; i < n; ++i) {
        int gid = idx[i];
        fast_write(strings[gid], str_len[gid]);
    }

    if (out_ptr > 0) {
        fwrite(out_buf, 1, out_ptr, stdout);
    }

    return 0;
}