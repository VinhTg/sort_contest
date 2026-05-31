# So sánh tối ưu giữa lần 1 và lần 2

## Lần 1

Lần 1 sử dụng **Optimized Quick Sort** gồm các kỹ thuật:

* Hoare Partition
* Median-of-Three Pivot Selection
* Insertion Sort cho mảng nhỏ
* Tail Recursion Optimization

Thuật toán hoạt động dựa trên việc:

* So sánh các phần tử
* Chọn pivot
* Phân hoạch mảng
* Đệ quy sắp xếp các đoạn con

Độ phức tạp trung bình:

**O(n log n)**

---

## Lần 2

Lần 2 chuyển sang sử dụng **LSD Radix Sort Base 256** kết hợp với:

* Fast I/O (`fread`, `fwrite`)
* Buffer đọc ghi thủ công
* Xử lý bit trực tiếp
* Mảng tĩnh

Thuật toán không sử dụng phép so sánh mà sắp xếp trực tiếp theo từng byte của số nguyên 32-bit.

Độ phức tạp:

**O(n)**

---

# Các hướng tối ưu so với lần 1

## 1. Chuyển từ Comparison Sort sang Non-Comparison Sort

Phiên bản đầu sử dụng Quick Sort nên phải thực hiện số lượng lớn phép so sánh giữa các phần tử.

Phiên bản thứ hai sử dụng Radix Sort, chỉ phân phối dữ liệu theo từng byte nên không cần thực hiện phép so sánh.

Điều này giúp giảm đáng kể branch misprediction và tăng hiệu suất xử lý của CPU.

---

## 2. Giảm độ phức tạp thuật toán

Quick Sort:

**O(n log n)**

Radix Sort:

**O(4n) ≈ O(n)**

Do số nguyên 32-bit chỉ cần xử lý 4 byte nên số vòng lặp luôn cố định.

---

## 3. Loại bỏ hoàn toàn đệ quy

Quick Sort sử dụng đệ quy nên phát sinh chi phí quản lý stack.

Radix Sort hoạt động hoàn toàn bằng vòng lặp nên loại bỏ được overhead này.

---

## 4. Tối ưu đọc ghi dữ liệu

Phiên bản đầu sử dụng:

```cpp
cin / cout
```

Phiên bản thứ hai sử dụng:

```cpp
fread / fwrite
```

kết hợp buffer lớn giúp giảm số lần gọi hàm I/O và tăng tốc độ đọc ghi dữ liệu.

---

## 5. Parse số nguyên thủ công

Sử dụng:

```cpp
read_int()
write_int()
```

thay cho cơ chế của iostream.

Cách làm này giúp giảm đáng kể chi phí xử lý khi làm việc với lượng dữ liệu lớn.

---

## 6. Xử lý bit trực tiếp

Các byte của số nguyên được lấy bằng:

```cpp
(v >> shift) & 0xFF
```

CPU xử lý các phép dịch bit và mask rất nhanh, giúp tăng tốc độ thực thi.

---

## 7. Thống kê đồng thời 4 pass

Trong một lần duyệt dữ liệu, chương trình đồng thời thống kê cho cả 4 byte:

```cpp
cnt[0][...]
cnt[1][...]
cnt[2][...]
cnt[3][...]
```

Giúp giảm số lần quét mảng và tăng hiệu quả sử dụng bộ nhớ đệm.

---

## 8. Sử dụng mảng tĩnh

Phiên bản đầu:

```cpp
new int[n]
```

Phiên bản thứ hai:

```cpp
unsigned int arr_a[MAXN];
unsigned int arr_b[MAXN];
```

Giúp tránh chi phí cấp phát động và cải thiện cache locality.

---

## 9. Tối ưu cache CPU

Radix Sort truy cập dữ liệu tuần tự:

```cpp
for (int i = 0; i < n; i++)
```

Điều này giúp:

* Giảm cache miss
* Tăng hiệu quả prefetch
* Tận dụng tốt bộ nhớ đệm CPU

Trong khi Quick Sort thường truy cập dữ liệu phân tán hơn.

---

## 10. Xử lý số âm bằng XOR

Sử dụng:

```cpp
arr_a[i] ^= 0x80000000;
```

để chuyển thứ tự signed sang unsigned trước khi sắp xếp.

Nhờ đó không cần xử lý riêng số âm và số dương.

---

# Kết luận

Phiên bản lần 2 tối ưu hơn phiên bản lần 1 nhờ:

* Chuyển từ Quick Sort sang Radix Sort
* Giảm độ phức tạp từ **O(n log n)** xuống **O(n)**
* Loại bỏ hoàn toàn đệ quy
* Sử dụng Fast I/O
* Xử lý dữ liệu bằng bit
* Tối ưu cache CPU
* Giảm chi phí cấp phát bộ nhớ

Kết quả là thời gian thực thi thực tế nhanh hơn đáng kể trên các bộ dữ liệu lớn, đặc biệt trong các bài toán **Sort Contest** và **Competitive Programming**.
