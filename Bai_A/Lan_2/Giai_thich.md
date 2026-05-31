So sánh tối ưu giữa lần 1 và lần 2
Lần 1

Lần 1 sử dụng Optimized Quick Sort gồm:

Hoare Partition
Median-of-Three
Insertion Sort
Tail Recursion

Thuật toán hoạt động dựa trên:

so sánh phần tử
chọn pivot
phân hoạch mảng
đệ quy sắp xếp

Độ phức tạp trung bình:

O(nlogn)
Lần 2

Lần 2 chuyển sang sử dụng LSD Radix Sort Base 256 kết hợp:

Fast IO (fread, fwrite)
Buffer thủ công
Xử lý bit trực tiếp
Mảng tĩnh

Thuật toán không sử dụng phép so sánh mà sắp xếp trực tiếp theo từng byte của số nguyên 32-bit.

Độ phức tạp:

O(n)
Các hướng tối ưu so với lần 1
1. Chuyển từ Comparison Sort sang Non-Comparison Sort

Lần 1:

Quick Sort

phải thực hiện rất nhiều phép so sánh.

Lần 2:

Radix Sort

chỉ phân phối dữ liệu theo byte.

Giảm đáng kể số phép so sánh và branch của CPU.

2. Độ phức tạp tuyến tính

Quick Sort:

O(nlogn)

Radix Sort:

O(4n)

vì số nguyên 32-bit chỉ cần 4 lần xử lý.

3. Loại bỏ hoàn toàn đệ quy

Quick Sort vẫn có:

quickSort(...)

gây overhead stack.

Radix Sort sử dụng vòng lặp hoàn toàn nên không tốn chi phí đệ quy.

4. Fast IO

Lần 1 sử dụng:

cin / cout

Lần 2 sử dụng:

fread / fwrite

kết hợp buffer lớn:
f[];

Giảm đáng kể thời gian đọc ghi dữ liệu lớn.

5. Parse số nguyên thủ công

Sử dụng:

read_int()
write_int()

thay cho iostream.

Giúp giảm overhead của thư viện chuẩn C++.

6. Xử lý bit trực tiếp

Sử dụng:

(v >> shift) & 0xFF

để lấy từng byte.

CPU xử lý rất nhanh nhờ các phép dịch bit và mask.

7. Thống kê đồng thời 4 pass

Trong một lần duyệt dữ liệu:

cnt[0][...]
cnt[1][...]
cnt[2][...]
cnt[3][...]

đã thu thập thống kê cho cả 4 byte.

Giảm số lần quét mảng.

8. Dùng mảng tĩnh

Lần 1:

new int[n]

Lần 2:

unsigned int arr_a[MAXN];
unsigned int arr_b[MAXN];

Tránh cấp phát động và tăng cache locality.

9. Tối ưu cache CPU

Radix Sort truy cập dữ liệu tuần tự:

for (i = 0; i < n; i++)

Giúp:

giảm cache miss
tăng hiệu quả prefetch

Trong khi Quick Sort truy cập dữ liệu phân tán hơn.

10. Xử lý số âm bằng XOR

Sử dụng:

arr_a[i] ^= 0x80000000;

để chuyển thứ tự signed thành unsigned.

Không cần tách riêng số âm và số dương.

Kết luận

Phiên bản lần 2 tối ưu hơn lần 1 nhờ:

chuyển từ Quick Sort sang Radix Sort
giảm độ phức tạp từ O(nlogn) xuống O(n)
loại bỏ đệ quy
sử dụng Fast IO
xử lý bit trực tiếp
tối ưu cache CPU
giảm chi phí cấp phát bộ nhớ

Kết quả là tốc độ thực tế nhanh hơn đáng kể trên các bộ test lớn trong bài toán sắp xếp số nguyên.