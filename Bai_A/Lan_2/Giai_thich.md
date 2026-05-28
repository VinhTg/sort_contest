
# So sánh tối ưu giữa lần 1 và lần 2

## Lần 1

Lần 1 sử dụng QuickSort tối ưu gồm:

* Hoare Partition
* Median-of-Three
* Insertion Sort
* Tail Recursion

Thuật toán hoạt động dựa trên:

* so sánh phần tử
* chọn pivot
* chia mảng
* swap dữ liệu

Độ phức tạp trung bình:

O(n log n)

---

# Lần 2

Lần 2 chuyển sang sử dụng LSD Radix Sort base 256 kết hợp Fast IO và buffer thủ công.

Thuật toán xử lý trực tiếp trên bit của số nguyên 32-bit thay vì dùng phép so sánh.

Độ phức tạp:

O(n)

---

# Các hướng tối ưu so với lần 1

## 1. Chuyển từ Comparison Sort sang Non-Comparison Sort

QuickSort cần:

* so sánh liên tục
* branch nhiều
* phụ thuộc pivot

Radix Sort:

* không dùng comparison
* chỉ phân phối dữ liệu theo byte

Giảm đáng kể branch misprediction của CPU.

---

## 2. Độ phức tạp tuyến tính

QuickSort:

O(n log n)

Radix Sort:

O(4n)

vì int có 4 byte nên chỉ cần 4 pass cố định.

Giúp tốc độ nhanh hơn rõ rệt trên dữ liệu lớn.

---

## 3. Không dùng recursion

QuickSort vẫn có:

* recursive call
* stack overhead

Radix Sort chạy iterative hoàn toàn nên giảm overhead.

---

## 4. Fast IO bằng fread/fwrite

Lần 1 sử dụng:

```cpp id="wdbjlwm"
cin / cout
```

Lần 2 sử dụng:

```cpp id="v2l2lo"
fread / fwrite
```

kèm buffer lớn:

```cpp id="hlr1o3"
char in_buf[MAX_BUF]
char out_buf[MAX_BUF]
```

Giảm số lần gọi hệ thống I/O nên nhanh hơn đáng kể.

---

## 5. Parse số nguyên thủ công

Sử dụng:

```cpp id="wl9ggg"
read_int()
write_int()
```

thay vì stream của C++.

Giúp:

* giảm overhead của iostream
* đọc ghi trực tiếp trên buffer
* tăng tốc đáng kể với dữ liệu lớn

---

## 6. Xử lý bit trực tiếp

Sử dụng:

```cpp id="zhfctw"
(v >> shift) & 0xFF
```

CPU xử lý:

* shift
* mask

nhanh hơn phép chia hoặc modulo.

---

## 7. Tạo histogram cho toàn bộ pass ngay từ đầu

Trong lúc duyệt dữ liệu:

```cpp id="yg3ydc"
cnt[0][...]
cnt[1][...]
cnt[2][...]
cnt[3][...]
```

đã đồng thời thống kê cho cả 4 pass.

Giúp:

* giảm số lần duyệt mảng
* giảm cache miss
* giảm memory access

---

## 8. Dùng static array thay cho vector động

Lần 2 sử dụng:

```cpp id="fagc5f"
unsigned int arr_a[MAXN]
unsigned int arr_b[MAXN]
```

Giúp:

* dữ liệu liên tục trong memory
* cache locality tốt hơn
* tránh overhead cấp phát động

---

## 9. Tối ưu cache CPU

Radix Sort truy cập bộ nhớ tuần tự:

```cpp id="e8z0vx"
for i = 0 -> n
```

Giúp:

* cache locality tốt
* prefetch hiệu quả
* giảm cache miss

QuickSort truy cập phân tán hơn nên cache kém hơn.

---

## 10. Xử lý số âm bằng XOR

Sử dụng:

```cpp id="0fjlwm"
arr_a[i] ^= 0x80000000
```

Giúp:

* chuyển signed int thành unsigned sortable
* số âm tự động nằm trước số dương
* không cần branch xử lý riêng

---

## 11. Giảm số lần cấp phát bộ nhớ

QuickSort dùng:

```cpp id="5rvl1l"
new int[n]
```

Lần 2 dùng static array cố định nên:

* tránh heap allocation
* giảm memory overhead
* truy cập nhanh hơn

---

# Độ phức tạp

## QuickSort

### Trung bình

O(n log n)

### Tệ nhất

O(n²)

---

## Radix Sort

### Mọi trường hợp

O(n)

với int 32-bit cố định.

---

# Kết luận

Phiên bản lần 2 tối ưu hơn lần 1 ở các điểm:

* không dùng comparison
* không recursion
* Fast IO mạnh hơn
* parse số nguyên thủ công
* xử lý bit trực tiếp
* cache locality tốt hơn
* giảm branch misprediction
* giảm memory overhead
* giảm số lần duyệt dữ liệu

Kết quả là tốc độ thực tế nhanh hơn đáng kể trên dữ liệu lớn trong các bài sort contest.
