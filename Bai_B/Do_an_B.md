# Câu 1: Thuật toán tốt nhất lần 1

## Thuật toán

**3-Way String Quicksort**

Thuật toán phân hoạch theo ký tự tại vị trí `d`, chia dữ liệu thành ba vùng:

* Nhỏ hơn pivot.
* Bằng pivot.
* Lớn hơn pivot.

Các phần tử thuộc nhóm bằng pivot tiếp tục được xử lý ở độ sâu `d + 1`.

```cpp
void quicksort3way(int lo, int hi, int d) {
    if (hi <= lo) return;

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);

        if (t < v)
            swap(a[lt++], a[i++]);
        else if (t > v)
            swap(a[i], a[gt--]);
        else
            i++;
    }

    quicksort3way(lo, lt - 1, d);

    if (v >= 0)
        quicksort3way(lt, gt, d + 1);

    quicksort3way(gt + 1, hi, d);
}
```

## Các tối ưu hóa

### 1. So sánh từng ký tự

Thuật toán chỉ đọc ký tự tại vị trí `d`.

Khi phát hiện khác biệt, quá trình xử lý dừng ngay mà không cần đọc thêm các ký tự phía sau.

Nhờ đó các ký tự thuộc tiền tố chung không bị đọc lại nhiều lần.

### 2. Phân hoạch ba chiều

Các chuỗi có cùng ký tự pivot được gom vào cùng một vùng.

Sau đó chỉ cần một lần đệ quy xuống mức `d + 1` để xử lý tiếp.

Điều này giúp giảm số phép so sánh và giảm số lần đệ quy không cần thiết so với Quicksort hai chiều.

### 3. Hàm `charAt()`

```cpp
inline int charAt(const string& s, int d) {
    return d < s.length()
           ? (unsigned char)s[d]
           : -1;
}
```

Khi vượt quá độ dài chuỗi, hàm trả về `-1`.

Nhờ đó các chuỗi có độ dài khác nhau được xử lý trực tiếp theo đúng thứ tự từ điển.

Ví dụ:

```text
ab
abc
```

sẽ luôn có:

```text
ab < abc
```

mà không cần điều kiện kiểm tra bổ sung.

### 4. Tối ưu nhập xuất

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

Giúp giảm chi phí nhập xuất trên các bộ dữ liệu lớn.

## Lý do lựa chọn

| Thuật toán             | Độ phức tạp       | Hạn chế                                |
| ---------------------- | ----------------- | -------------------------------------- |
| Quicksort truyền thống | O(n·L·log n)      | So sánh chuỗi nhiều lần                |
| Merge Sort             | O(n·L·log n)      | Cần O(n) bộ nhớ phụ                    |
| 3-Way String Quicksort | O(n·L) trung bình | Hiệu quả trên dữ liệu có tiền tố chung |

Điểm quan trọng nhất là tham số `d`.

Các ký tự thuộc phần tiền tố chung chỉ được xử lý đúng một lần và không bị đọc lại ở các mức đệ quy sau.

Nhờ đó thuật toán tận dụng tốt cấu trúc dữ liệu chuỗi và đạt hiệu năng cao nhất trong các phương án cài đặt ở lần thứ nhất.

---

# Câu 2: Sinh test case và thuật toán mục tiêu

## Cấu trúc dữ liệu sinh ra

Mỗi chuỗi được sinh theo dạng:

```text
[a × prefA] + [mã nhóm] + [a × prefB] + [đuôi 4 ký tự]
```

Các chuỗi trong cùng một nhóm chỉ khác nhau ở phần đuôi và có tiền tố chung rất dài.

## Thuật toán mục tiêu

Bộ test được thiết kế chủ yếu để làm tăng thời gian chạy của các biến thể **MSD Radix Sort**.

Đây là nhóm thuật toán thường đạt hiệu năng cao nhất đối với bài toán sắp xếp chuỗi, nhưng tồn tại một số điểm yếu đặc trưng:

* Phải khởi tạo bảng đếm ở mỗi mức đệ quy.
* Chỉ phân tách được dữ liệu khi xuất hiện khác biệt tại vị trí đang xét.
* Tiền tố chung càng dài thì số mức đệ quy càng lớn.
* Insertion Sort cho bucket nhỏ vẫn có thể phải đọc lại nhiều ký tự giống nhau.

So với MSD Radix Sort, 3-Way String Quicksort ít bị ảnh hưởng hơn vì không sử dụng bảng đếm và xử lý tốt các nhóm có cùng tiền tố thông qua phân hoạch ba chiều.

## Phân tích từng test

| Test  | Tham số                                | Chiến lược             | Tác động                                               |
| ----- | -------------------------------------- | ---------------------- | ------------------------------------------------------ |
| test1 | 3125 × 32, prefix ≈ 90                 | Chiều rộng             | 3125 bucket, mỗi bucket đệ quy khoảng 90 mức           |
| test2 | 6250 × 16, prefix ≈ 90                 | Ngưỡng Insertion Sort  | Bucket kích thước 16 liên tục kích hoạt Insertion Sort |
| test3 | 2500 × 32, prefix ≈ 95                 | Chiều sâu              | Đệ quy khoảng 95 mức trước khi phân tách               |
| test4 | 2000 × 50, prefix ≈ 96, không xáo trộn | Chiều sâu + bucket lớn | Bucket lớn được giữ nguyên và tiếp tục đệ quy rất sâu  |
| test5 | Bucket 16/32 xen kẽ, prefix ≈ 70       | Kết hợp                | Tác động đồng thời lên đệ quy và Insertion Sort        |

## Chiến lược tổng thể

* Test 1 và Test 2 tấn công theo chiều rộng bằng cách tạo rất nhiều bucket.
* Test 3 và Test 4 tấn công theo chiều sâu bằng cách tạo tiền tố chung cực dài.
* Test 5 kết hợp cả hai hướng.

Mục tiêu chung là làm tăng số mức đệ quy, số lần khởi tạo bảng đếm và số phép so sánh phát sinh trong các bucket nhỏ của MSD Radix Sort.

---

# Câu 3: Thuật toán tốt nhất lần 2

## Thuật toán

**MSD Radix Sort kết hợp Hybrid Insertion Sort**

## Hạn chế của lần cài đặt thứ nhất

Phiên bản đầu tiên sử dụng 3-Way String Quicksort nhưng vẫn tồn tại một số hạn chế:

* Vẫn thuộc nhóm thuật toán dựa trên phép so sánh.
* Chưa tận dụng trực tiếp việc bảng chữ cái chỉ gồm 26 ký tự.
* Hoán đổi trực tiếp đối tượng `std::string` có chi phí tương đối lớn.
* `cin/cout` vẫn chậm hơn các phương pháp đọc ghi theo bộ đệm.
* Chưa có cơ chế xử lý riêng cho các bucket nhỏ.

Những hạn chế này là cơ sở để phát triển phiên bản thứ hai.

## Các tối ưu hóa

### 1. Chuyển sang MSD Radix Sort

Thay vì so sánh các chuỗi với nhau, thuật toán phân phối trực tiếp dữ liệu vào các bucket dựa trên ký tự đang xét.

Mỗi mức đệ quy chỉ cần một lần duyệt tuyến tính:

```text
O(n)
```

và không cần thực hiện các phép so sánh chuỗi.

### 2. Thu nhỏ bảng đếm

```cpp
int count[27];
```

thay cho:

```cpp
int count[256];
```

Bảng đếm nhỏ hơn khoảng 9,5 lần và dễ nằm trong cache CPU hơn.

### 3. Sắp xếp trên mảng chỉ số

```cpp
int idx1[MAXN];
int idx2[MAXN];
```

Thuật toán chỉ di chuyển các giá trị nguyên thay vì di chuyển toàn bộ chuỗi.

### 4. Hybrid Insertion Sort

Khi:

```cpp
n <= 32
```

thuật toán chuyển sang Insertion Sort.

Điều này giúp tránh chi phí khởi tạo bảng đếm và đệ quy đối với các bucket nhỏ.

### 5. So sánh từ đúng độ sâu hiện tại

```cpp
inline bool less_suffix(const char* a,
                        const char* b,
                        int depth)
```

Khi Insertion Sort được gọi ở độ sâu `depth`, các ký tự trước đó đã chắc chắn giống nhau.

Nếu sử dụng `strcmp()`, toàn bộ phần tiền tố sẽ bị đọc lại.

Với tiền tố dài khoảng 90 ký tự, mỗi phép so sánh sẽ lãng phí khoảng 90 lần đọc ký tự.

`less_suffix()` bắt đầu trực tiếp tại vị trí `depth`, loại bỏ hoàn toàn chi phí này.

### 6. Đọc dữ liệu bằng `fread`

```cpp
fread(in_buf, 1, MAX_BUF - 1, stdin);
```

Toàn bộ dữ liệu được đưa vào một bộ đệm duy nhất.

Các chuỗi chỉ được lưu dưới dạng con trỏ:

```cpp
strings[i] = &in_buf[p];
```

không phát sinh cấp phát động cho từng chuỗi.

### 7. Bộ đệm xuất riêng

Kết quả được ghi vào:

```cpp
char out_buf[MAX_BUF];
```

và xuất bằng `fwrite()`.

Nhờ đó số lần gọi hàm xuất dữ liệu của hệ điều hành được giảm đáng kể.

### 8. Lưu trước độ dài chuỗi

```cpp
str_len[i] = p - st;
```

Khi xuất dữ liệu, chương trình không cần gọi lại `strlen()` cho từng chuỗi.

## Kết quả cải thiện

So với phiên bản đầu tiên, phiên bản thứ hai:

* Loại bỏ phần lớn các phép so sánh chuỗi.
* Giảm chi phí di chuyển dữ liệu.
* Tận dụng đặc điểm bảng chữ cái gồm 26 ký tự.
* Tối ưu nhập xuất bằng bộ đệm lớn.
* Tối ưu bucket nhỏ bằng Hybrid Insertion Sort.

Nhờ đó chương trình đạt hiệu năng cao hơn đáng kể trên các bộ dữ liệu kiểm thử đã xây dựng.
