# Ý tưởng chung

Chương trình sử dụng **Quick Sort tối ưu hóa** để sắp xếp mảng số nguyên. Đây là phiên bản cải tiến của Quick Sort truyền thống bằng cách kết hợp nhiều kỹ thuật tối ưu nhằm tăng tốc độ thực thi và giảm nguy cơ rơi vào trường hợp xấu nhất.

Quick Sort hoạt động theo nguyên tắc:

1. Chọn một phần tử làm pivot.
2. Chia mảng thành hai phần:
   - Các phần tử nhỏ hơn pivot.
   - Các phần tử lớn hơn pivot.
3. Đệ quy sắp xếp hai phần đó.

Độ phức tạp trung bình:

**O(n log n)**

---

# 2. Các phương pháp tối ưu hóa được sử dụng

## 2.1. Median-of-Three Pivot Selection

Trong hàm `partition()`:

```cpp
int mid = left + (right - left) / 2;

if (arr[mid] < arr[left]) swap(arr[mid], arr[left]);
if (arr[right] < arr[left]) swap(arr[right], arr[left]);
if (arr[right] < arr[mid]) swap(arr[right], arr[mid]);

int pivot = arr[mid];
```

Thay vì chọn:

- phần tử đầu,
- phần tử cuối,
- hoặc phần tử ngẫu nhiên,

chương trình lấy trung vị của:

- phần tử đầu,
- phần tử giữa,
- phần tử cuối.

Ví dụ:

```text
10 2 7
```

Sau khi sắp xếp:

```text
2 7 10
```

Pivot được chọn là:

```text
7
```

### Lợi ích

Giảm khả năng xuất hiện trường hợp:

```text
1 2 3 4 5 6 7 8
```

hoặc

```text
8 7 6 5 4 3 2 1
```

làm Quick Sort bị suy biến thành:

**O(n²)**

Median-of-Three thường tạo ra pivot gần trung tâm hơn nên hai nửa sau khi chia cân bằng hơn.

---

## 2.2. Hoare Partition Scheme

Trong chương trình:

```cpp
int i = left - 1;
int j = right + 1;
```

Hai con trỏ chạy từ hai đầu:

```cpp
do { i++; } while (arr[i] < pivot);
do { j--; } while (arr[j] > pivot);
```

Sau đó đổi chỗ:

```cpp
swap(arr[i], arr[j]);
```

đến khi:

```cpp
i >= j
```

### Lợi ích

So với Lomuto Partition:

```cpp
for(...)
```

Hoare Partition:

- ít phép swap hơn
- ít phép gán hơn
- nhanh hơn trong thực tế
- xử lý dữ liệu có nhiều phần tử trùng nhau tốt hơn

Do đó hiệu năng thực tế cao hơn đáng kể.

---

## 2.3. Insertion Sort cho mảng nhỏ

Trong Quick Sort:

```cpp
if (right - left < 15)
{
    insertionSort(arr, left, right);
    break;
}
```

Khi kích thước đoạn cần sắp xếp nhỏ hơn 15 phần tử, chương trình không tiếp tục đệ quy nữa mà dùng Insertion Sort.

### Lý do

Mặc dù độ phức tạp của Insertion Sort là:

**O(n²)**

nhưng với n rất nhỏ:

```text
5
10
15
```

thì:

- không có chi phí đệ quy
- không cần chọn pivot
- không cần partition

nên thực tế nhanh hơn Quick Sort.

Đây là kỹ thuật được sử dụng trong nhiều thư viện chuẩn hiện nay.

---

## 2.4. Tail Recursion Optimization

Trong hàm:

```cpp
if (p - left < right - p)
{
    quickSort(arr, left, p);
    left = p + 1;
}
else
{
    quickSort(arr, p + 1, right);
    right = p;
}
```

Chương trình luôn đệ quy vào nửa nhỏ hơn trước.

### Lợi ích

Nếu đệ quy thông thường:

```cpp
quickSort(left)
quickSort(right)
```

chiều sâu stack có thể lên đến:

**O(n)**

trong trường hợp xấu.

Kỹ thuật này đảm bảo:

**O(log n)**

mức sử dụng stack.

Ưu điểm:

- giảm nguy cơ Stack Overflow
- tiết kiệm bộ nhớ
- ổn định hơn với dữ liệu lớn

---

# 3. Độ phức tạp

## Thời gian

| Trường hợp | Độ phức tạp |
|------------|-------------|
| Tốt nhất | O(n log n) |
| Trung bình | O(n log n) |
| Xấu nhất | O(n²) |

Tuy nhiên nhờ:

- Median-of-Three
- Hoare Partition

xác suất gặp trường hợp xấu nhất rất thấp.

### Bộ nhớ

Do tối ưu đệ quy:

**O(log n)**

---

# 4. Tại sao đây là cách cài đặt tốt nhất ở lần chạy đầu tiên?

## So sánh với các thuật toán khác

| Thuật toán | Thời gian trung bình | Bộ nhớ phụ |
|------------|---------------------|------------|
| Bubble Sort | O(n²) | O(1) |
| Selection Sort | O(n²) | O(1) |
| Insertion Sort | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(1) |
| Quick Sort cơ bản | O(n log n) | O(log n) |
| Quick Sort tối ưu | O(n log n) | O(log n) |

### Lý do lựa chọn

#### 1. Nhanh nhất trong thực tế

Mặc dù Heap Sort và Merge Sort cũng có độ phức tạp:

**O(n log n)**

nhưng Quick Sort thường có hằng số thời gian nhỏ hơn nên chạy nhanh hơn trên dữ liệu thực tế.

#### 2. Không cần bộ nhớ phụ lớn

Merge Sort cần:

**O(n)**

bộ nhớ phụ.

Chương trình này chỉ cần:

**O(log n)**

cho ngăn xếp đệ quy.

#### 3. Giảm mạnh khả năng rơi vào O(n²)

Nhờ:

- Median-of-Three
- Hoare Partition

#### 4. Tăng tốc với mảng nhỏ

Nhờ kết hợp:

- Quick Sort
- Insertion Sort

#### 5. Tiết kiệm bộ nhớ stack

Nhờ Tail Recursion Optimization.

---

# Kết luận

Thuật toán trong chương trình là một phiên bản **Optimized Quick Sort** kết hợp bốn kỹ thuật tối ưu:

1. Median-of-Three Pivot Selection
2. Hoare Partition Scheme
3. Insertion Sort cho mảng nhỏ
4. Tail Recursion Optimization

Nhờ các cải tiến này, thuật toán đạt hiệu năng thực tế rất cao, sử dụng ít bộ nhớ, giảm nguy cơ rơi vào trường hợp xấu nhất và phù hợp để cài đặt ngay từ lần chạy đầu tiên đối với bài toán sắp xếp mảng số nguyên kích thước lớn.