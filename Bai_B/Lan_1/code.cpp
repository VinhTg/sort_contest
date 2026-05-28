#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int N = 1e5 + 7;
string a[N];
int n;

inline int charAt(const string &s, int d) {
    if (d < (int)s.length()) return (unsigned char)s[d];
    return -1;
}

void quicksort3way(int lo, int hi, int d) {
    if (hi <= lo) return;

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v) {
            swap(a[lt], a[i]);
            lt++;
            i++;
        } else if (t > v) {
            swap(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }

    quicksort3way(lo, lt - 1, d);

    if (v >= 0) quicksort3way(lt, gt, d + 1);

    quicksort3way(gt + 1, hi, d);
}

void Inp() {
    if (!(cin >> n)) return;
    for (int i = 0; i < n; i++) cin >> a[i];
}

void Solve() {
    if (n > 0) {
        quicksort3way(0, n - 1, 0);
    }
    cout << n << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Inp();
    Solve();

    return 0;
}
