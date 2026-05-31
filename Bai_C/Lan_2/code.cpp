#include <iostream>
#include <string>

using namespace std;

const int MAX_BUF = 30000005; 
const int MAXN = 1000005;
const int MAXL = 10005;

char pool_buf[MAX_BUF]; 
char* str_ptrs[MAXN];   
int lengths[MAXN];

int head[MAXL];
int next_idx[MAXN];

int A[MAXN];

void mkqsort(int l, int r, int depth) {
    if (l >= r) return;

    int mid = l + (r - l) / 2;
    int temp_m = A[l]; A[l] = A[mid]; A[mid] = temp_m;

    int pivot = str_ptrs[A[l]][depth];
    int lt = l, i = l + 1, gt = r;

    while (i <= gt) {
        int c = str_ptrs[A[i]][depth];
        if (c < pivot) {
            int temp = A[lt]; A[lt] = A[i]; A[i] = temp;
            lt++; i++;
        } else if (c > pivot) {
            int temp = A[gt]; A[gt] = A[i]; A[i] = temp;
            gt--;
        } else {
            i++;
        }
    }

    mkqsort(l, lt - 1, depth);
    if (pivot != '\0') {
        mkqsort(lt, gt, depth + 1);
    }
    mkqsort(gt + 1, r, depth);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int pool_ptr = 0;
    int max_len = 0;
    string tmp;

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        str_ptrs[i] = pool_buf + pool_ptr; 
        
        int len = tmp.length();
        for (int j = 0; j <= len; ++j) {
            str_ptrs[i][j] = tmp[j];
        }
        
        lengths[i] = len;
        pool_ptr += len + 1; 
        
        if (len > max_len) {
            max_len = len;
        }
    }

    for (int i = 0; i <= max_len; ++i) {
        head[i] = -1;
    }

    for (int i = n - 1; i >= 0; --i) {
        int len = lengths[i];
        next_idx[i] = head[len];
        head[len] = i;
    }

    cout << n << "\n";

    for (int L = 1; L <= max_len; ++L) {
        if (head[L] == -1) continue;

        int sz = 0;
        for (int i = head[L]; i != -1; i = next_idx[i]) {
            A[sz++] = i;
        }

        if (sz > 1) {
            mkqsort(0, sz - 1, 0);
        }

        for (int i = 0; i < sz; ++i) {
            cout << str_ptrs[A[i]] << "\n";
        }
    }

    return 0;
}