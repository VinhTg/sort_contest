#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_BUF = 30000005; 
const int MAX_N = 1000005;     
const int MAX_LEN = 10005;

char in_buf[MAX_BUF];
char out_buf[MAX_BUF];

const char* string_ptrs[MAX_N];
int string_lens[MAX_N];
const char* sorted_ptrs[MAX_N];

int len_cnt[MAX_LEN];
int len_offset[MAX_LEN];
int current_len_offset[MAX_LEN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    size_t total_bytes = fread(in_buf, 1, MAX_BUF - 1, stdin);
    if (total_bytes == 0) return 0;
    in_buf[total_bytes] = '\0';

    const char* p = in_buf;
    
    while (*p && *p <= ' ') p++;
    
    int n = 0;
    while (*p >= '0' && *p <= '9') {
        n = n * 10 + (*p - '0');
        p++;
    }

    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        while (*p && *p <= ' ') p++;
        if (!*p) { n = i; break; }
        
        string_ptrs[i] = p;
        while (*p > ' ') p++;
        
        int len = p - string_ptrs[i];
        string_lens[i] = len;
        if (len > max_len) max_len = len;
        len_cnt[len]++;
    }

    int current_offset = 0;
    for (int l = 0; l <= max_len; ++l) {
        len_offset[l] = current_offset;
        current_offset += len_cnt[l];
    }

    memcpy(current_len_offset, len_offset, (max_len + 1) * sizeof(int));

    for (int i = 0; i < n; ++i) {
        int l = string_lens[i];
        sorted_ptrs[current_len_offset[l]++] = string_ptrs[i];
    }

    for (int l = 0; l <= max_len; ++l) {
        int start_idx = len_offset[l];
        int end_idx = current_len_offset[l];
        
        if (start_idx >= end_idx) continue;

        sort(sorted_ptrs + start_idx, sorted_ptrs + end_idx, [l](const char* a, const char* b) {
            return memcmp(a, b, l) < 0;
        });
    }

    char* out_ptr = out_buf;
    out_ptr += sprintf(out_ptr, "%d\n", n);

    for (int l = 0; l <= max_len; ++l) {
        int start_idx = len_offset[l];
        int end_idx = current_len_offset[l];
        for (int i = start_idx; i < end_idx; ++i) {
            memcpy(out_ptr, sorted_ptrs[i], l);
            out_ptr += l;
            *out_ptr++ = '\n';
        }
    }

    fwrite(out_buf, 1, out_ptr - out_buf, stdout);

    return 0;
}