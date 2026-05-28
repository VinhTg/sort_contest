#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

// Dùng Insertion Sort cho mảng con cực nhỏ để giảm chi phí đệ quy
inline void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Hoare Partition kết hợp Median-of-Three
int partition(int arr[], int left, int right) {
    int mid = left + (right - left) / 2;

    // Median-of-Three: Sắp xếp sơ bộ 3 phần tử để chọn Pivot tốt nhất
    if (arr[mid] < arr[left]) swap(arr[mid], arr[left]);
    if (arr[right] < arr[left]) swap(arr[right], arr[left]);
    if (arr[right] < arr[mid]) swap(arr[right], arr[mid]);

    int pivot = arr[mid];

    // Con trỏ Hoare
    int i = left - 1;
    int j = right + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);

        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

void quickSort(int arr[], int left, int right) {
    while (left < right) {
        // Ngưỡng tối ưu: Nếu mảng nhỏ hơn 15 phần tử, dùng Insertion Sort
        if (right - left < 15) {
            insertionSort(arr, left, right);
            break;
        }

        int p = partition(arr, left, right);

        // Tối ưu đệ quy đuôi: Luôn đệ quy vào phần nhỏ hơn để giữ Stack O(log n)
        if (p - left < right - p) {
            quickSort(arr, left, p);
            left = p + 1;
        } else {
            quickSort(arr, p + 1, right);
            right = p;
        }
    }
}

// Hàm Wrapper để dễ gọi
void optimizedQuickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}


int main() {
    ios::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    optimizedQuickSort(arr, n);

    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << '\n';
    }

    delete[] arr;
    return 0;
}
