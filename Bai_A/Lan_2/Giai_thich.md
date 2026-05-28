# Giai_thich.md

# So sánh tối ưu giữa lần 1 và lần 2

## Lần 1

Lần 1 sử dụng QuickSort tối ưu gồm:

* Hoare Partition
* Median-of-Three
* Insertion Sort
* Tail Recursion

Thuật toán hoạt động dựa trên:

* chọn pivot
* chia mảng
* so sánh phần tử
* swap dữ liệu

Độ phức tạp trung bình:

O(n log n)

---

# Lần 2

Lần 2 sử dụng LSD Radix Sort base 256 kết hợp Fast IO và xử lý bit trực tiếp.

Thuật toán không dùng phép so sánh mà xử lý theo từng byte của số nguyên 32-bit.

Độ phức tạp:

O(n)

với số pass cố định là 4.

---

# Các hướng tối ưu so với lần 1

## 1. Không dùng comparison

QuickSort phải:

* so sánh liên tục
* branch nhiều
* phụ thuộc pivot

Radix Sort chỉ:

* đếm tần suất
* phân phối dữ liệu

Giảm đáng kể branch misprediction của CPU.

---

## 2. Độ phức tạp tuyến tính

QuickSort:

O(n log n)

Radix Sort:

O(4n)

Do int có 4 byte nên chỉ cần 4 pass.

Tốc độ nhanh hơn đáng kể trên dữ liệu lớn.

---

## 3. Không dùng recursion

QuickSort vẫn có:

* recursive call
* stack overhead

Radix Sort chạy iterative hoàn toàn nên giảm overhead.

---

## 4. Fast IO bằng fread/fwrite

Lần 1 dùng:

```cpp id="w9g9hg"
cin / cout
```

Lần 2 dùng:

```cpp id="dknh75"
fread / fwrite
```

kèm buffer lớn:

```cpp id="n85i7f"
1 << 16
```

Giảm số lần gọi hệ thống I/O nên nhanh hơn nhiều.

---

## 5. Xử lý trực tiếp trên bit

Sử dụng:

```cpp id="ifh70l"
(key >> shift) & 255
```

CPU xử lý:

* shift
* mask

nhanh hơn rất nhiều so với phép chia hoặc modulo.

---

## 6. Tạo histogram ngay lúc đọc input

Trong lúc đọc dữ liệu:

```cpp id="v2krv4"
++cnt[0][...]
++cnt[1][...]
++cnt[2][...]
++cnt[3][...]
```

đã đồng thời tạo toàn bộ histogram cho 4 pass.

Giúp:

* giảm số lần duyệt mảng
* giảm cache miss
* giảm memory access

---

## 7. Giảm copy dữ liệu

Sử dụng:

```cpp id="8gpx6v"
src
dst
```

và đổi con trỏ:

```cpp id="q2j40r"
tmp = src;
src = dst;
dst = tmp;
```

thay vì copy toàn bộ mảng sau mỗi pass.

Giảm đáng kể memory bandwidth.

---

## 8. Tối ưu cache CPU

Radix Sort truy cập bộ nhớ tuần tự.

Giúp:

* cache locality tốt
* prefetch hiệu quả
* giảm cache miss

QuickSort truy cập dữ liệu phân tán hơn nên cache kém hơn.

---

## 9. Xử lý số âm bằng XOR

Sử dụng:

```cpp id="o5q0gn"
key ^ 0x80000000u
```

Giúp:

* chuyển signed int thành unsigned sortable
* số âm tự nằm trước số dương
* không cần branch xử lý riêng

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
* tối ưu bit operation
* giảm branch misprediction
* cache locality tốt hơn
* giảm số lần duyệt dữ liệu
* giảm chi phí copy mảng

Kết quả là tốc độ thực tế nhanh hơn đáng kể trên dữ liệu lớn trong các bài sort contest.
