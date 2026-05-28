# Giai_thich.md

# So sánh tối ưu giữa lần 1 và lần 2

## Lần 1

Lần 1 sử dụng QuickSort tối ưu gồm:

* Hoare Partition
* Median-of-Three
* Insertion Sort cho đoạn nhỏ
* Tail Recursion Elimination

QuickSort hoạt động dựa trên:

* chia mảng
* chọn pivot
* so sánh phần tử
* swap dữ liệu

Độ phức tạp trung bình:

O(n log n)

Tuy nhiên vẫn còn nhiều hạn chế khi xử lý dữ liệu cực lớn.
# Lần 2

Lần 2 chuyển sang sử dụng LSD Radix Sort base 256 kết hợp Fast IO và xử lý trực tiếp trên bit.

Thuật toán không còn dùng phép so sánh giữa các phần tử mà xử lý theo từng byte của số nguyên 32-bit.
# Các hướng tối ưu so với lần 1

## 1. Chuyển từ Comparison Sort sang Non-Comparison Sort

QuickSort:

* phải so sánh liên tục
* phụ thuộc pivot
* có branch prediction miss

Radix Sort:

* không dùng so sánh
* chỉ đếm tần suất và phân phối dữ liệu

Giúp CPU xử lý ổn định và nhanh hơn.
## 2. Độ phức tạp tuyến tính
QuickSort:
O(n log n)
Radix Sort:
O(4n)
vì int có 4 byte nên chỉ cần 4 pass.
Điều này giúp tốc độ nhanh hơn đáng kể trên dữ liệu lớn.
## 3. Không có đệ quy
QuickSort vẫn sử dụng recursive call nên:
* tốn stack
* có function call overhead
* có nguy cơ stack overflow

Radix Sort chạy hoàn toàn iterative nên giảm đáng kể overhead.
## 4. Tối ưu Input/Output

Lần 1 sử dụng:

```cpp id="tzw9p2"
cin / cout
```

Dù đã tắt sync nhưng vẫn chậm hơn fread/fwrite.

Lần 2 sử dụng:

```cpp id="7wgfgs"
fread
fwrite
```

kết hợp buffer lớn:

```cpp id="m5c7c0"
1 << 16
```

Giúp giảm số lần gọi hệ thống I/O.

Đây là tối ưu rất lớn khi dữ liệu có hàng triệu số.

---

## 5. Xử lý trực tiếp trên bit

Lần 2 sử dụng:

```cpp id="59p45m"
uint32_t
```

và thao tác bit:

```cpp id="w5mjlwm"
(key >> shift) & 255
```

CPU xử lý bit operation cực nhanh vì:

* không cần phép chia
* không cần modulo
* chỉ dùng shift và mask
## 6. Tách trước toàn bộ histogram
Trong lúc đọc input:
```cpp id="vnhmwx"
++cnt[0][...]
++cnt[1][...]
++cnt[2][...]
++cnt[3][...]
```
đã đồng thời tạo histogram cho cả 4 pass.
Điều này giúp:
* giảm số lần duyệt mảng
* giảm cache miss
* giảm memory access
Trong khi radix cơ bản thường phải đếm lại ở mỗi pass.
## 7. Giảm số lần copy dữ liệu
Code sử dụng:

```cpp id="vjlwm5"
src
dst
```

và hoán đổi con trỏ:

```cpp id="goi3ah"
tmp = src;
src = dst;
dst = tmp;
```

thay vì copy cả mảng.

Giúp giảm rất lớn chi phí memory bandwidth.

---

## 8. Tối ưu cache CPU

Radix Sort truy cập bộ nhớ tuần tự:

```cpp id="kdy4d2"
for i = 0 -> n
```

Giúp:

* cache locality tốt
* prefetch hiệu quả
* giảm cache miss

QuickSort truy cập dữ liệu phân tán hơn nên cache kém hơn.

---

## 9. Xử lý số âm không cần branch

Sử dụng:

```cpp id="66qjlg"
key ^ 0x80000000u
```

Giúp:

* biến signed int thành unsigned sortable
* số âm tự động nằm trước số dương
* không cần if riêng cho số âm

Giảm branch prediction fail.

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

# Bộ nhớ

## QuickSort

O(log n)

## Radix Sort

O(n)

do dùng thêm buffer phụ.

---

# Kết luận

Phiên bản lần 2 tối ưu mạnh hơn lần 1 ở các điểm:

* không dùng comparison
* không recursion
* tối ưu bit operation
* Fast IO bằng fread/fwrite
* cache locality tốt hơn
* giảm branch misprediction
* giảm số lần duyệt dữ liệus
* giảm số lần copy mảng

Kết quả là tốc độ thực tế nhanh hơn đáng kể trên dữ liệu lớn, đặc biệt với các bài sort contest số nguyên.
