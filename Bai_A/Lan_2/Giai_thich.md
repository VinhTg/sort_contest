So sánh tối ưu giữa lần 1 và lần 2
Lần 1

Sử dụng QuickSort tối ưu với:

Hoare Partition
Median-of-Three
Insertion Sort
Tail Recursion

Độ phức tạp trung bình:

O(nlogn)
Lần 2

Sử dụng LSD Radix Sort base 256 kết hợp Fast IO (fread/fwrite) và xử lý bit trực tiếp.

Độ phức tạp:

O(n)

(với số nguyên 32-bit chỉ cần 4 pass).

Các điểm tối ưu chính
1. Chuyển từ Comparison Sort sang Radix Sort
QuickSort cần nhiều phép so sánh và phụ thuộc pivot.
Radix Sort xử lý trực tiếp theo byte nên nhanh hơn trên dữ liệu lớn.
2. Không dùng đệ quy
QuickSort có overhead từ recursive call.
Radix Sort chạy hoàn toàn lặp nên tiết kiệm thời gian hơn.
3. Fast IO
Lần 1 dùng cin/cout.
Lần 2 dùng fread/fwrite và buffer lớn, giảm chi phí I/O.
4. Xử lý bit trực tiếp

Sử dụng:

(v >> shift) & 0xFF

nhanh hơn các phép chia hoặc modulo.

5. Tối ưu bộ nhớ và cache
Dùng mảng tĩnh thay cho cấp phát động.
Truy cập tuần tự giúp cache locality tốt hơn và giảm cache miss.
6. Xử lý số âm hiệu quả
arr[i] ^= 0x80000000;

không cần nhánh xử lý riêng cho số âm.

Kết luận

Phiên bản lần 2 nhanh hơn lần 1 nhờ:

Độ phức tạp từ O(n log n) xuống O(n).
Không dùng recursion.
Fast IO.
Xử lý bit trực tiếp.
Tối ưu cache và bộ nhớ.

Do đó Radix Sort phù hợp hơn cho bài sort contest với dữ liệu số nguyên kích thước lớn.