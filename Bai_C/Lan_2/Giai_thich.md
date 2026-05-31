# BÁO CÁO: HÀNH TRÌNH TỐI ƯU HÓA THUẬT TOÁN SẮP XẾP CHUỖI

## PHẦN 1: NỀN TẢNG VÀ NHỮNG GIỚI HẠN BAN ĐẦU

### 1.1. Sắp xếp chuỗi với thuật toán cơ bản

Khi giải quyết bài toán sắp xếp một mảng số nguyên, các thuật toán như Quick Sort hay Merge Sort chuẩn hoạt động cực kỳ hiệu quả. Tuy nhiên, khi áp dụng trực tiếp cho chuỗi (String), chúng ta gặp phải một "nút thắt cổ chai" lớn về mặt kiến trúc.

Phép so sánh hai số nguyên $a < b$ chỉ mất độ phức tạp $O(1)$ ở cấp độ phần cứng. Ngược lại, để so sánh hai chuỗi `S1` và `S2`, CPU phải duyệt qua từng ký tự từ trái sang phải cho đến khi tìm thấy sự khác biệt.

### 1.2. Độ phức tạp thời gian thực tế

Nếu độ dài trung bình của các chuỗi là $L$, chi phí cho một lần so sánh là $O(L)$.
Một thuật toán Quick Sort kinh điển có độ phức tạp số lần so sánh là $O(N \log N)$. Khi áp dụng cho chuỗi, tổng thời gian thực thi bị đẩy lên thành $O(N \log N \times L)$. Nếu $N$ lên tới hàng triệu và $L$ cũng lớn, chi phí này trở nên không thể chấp nhận được. Hệ thống cần một phương pháp bóc tách ký tự để không phải so sánh lại những phần tiền tố (prefix) đã giống nhau.

---

## PHẦN 2: GOM NHÓM VÀ MSD RADIX SORT (Phân tích Code 1)

Đoạn Code lần 1 thể hiện nỗ lực bẻ gãy giới hạn $O(N \log N \times L)$ bằng cách ứng dụng **MSD (Most Significant Digit) Radix Sort**.

### 2.1. Chiến lược chia để trị theo độ dài

Thay vì ném tất cả vào một mảng duy nhất, hệ thống phân loại chuỗi ngay từ lúc đọc dữ liệu vào mảng `vector<string> a[101]`. Những chuỗi có độ dài bằng nhau sẽ vào chung một nhóm (bucket). Điều này triệt tiêu hoàn toàn các phép so sánh chênh lệch độ dài không cần thiết ở giai đoạn đầu.

### 2.2. Cơ chế hoạt động của MSD Radix Sort

Thuật toán thực hiện sắp xếp đếm (Counting Sort) trên từng vị trí ký tự (từ trái sang phải, tức là từ `pos = 0` đến `len`):

1. Đếm tần suất xuất hiện của từng ký tự tại vị trí `pos`.
2. Cộng dồn mảng đếm `cnt` để xác định vị trí bắt đầu của từng "khoang" ký tự trong mảng `temp`.
3. Đưa các chuỗi vào đúng khoang của nó trong mảng tạm `temp`, sau đó chép ngược lại mảng `a`.
4. Gọi đệ quy cho vị trí `pos + 1` trên từng khoang nhỏ vừa được chia.

### 2.3. Nhận diện các điểm yếu trong Code 1

Mặc dù thuật toán Radix Sort rất tốt về lý thuyết, nhưng cách cài đặt trong Code 1 bị giới hạn bởi cấu trúc dữ liệu:

* **Chi phí cấp phát động:** Sử dụng `std::string` và `std::vector` đồng nghĩa với việc liên tục gọi `new` và `delete` ngầm dưới background (Heap Allocation).
* **Rớt bộ nhớ đệm (Cache Miss):** Các đối tượng `std::string` thực chất chứa con trỏ trỏ đến vùng nhớ lưu ký tự nằm rải rác trên RAM. Khi CPU quét qua mảng `vector`, nó không thể nạp trước (prefetch) dữ liệu chuỗi vào Cache, gây nghẽn cổ chai bộ nhớ.
* **Chi phí không gian (Space Complexity):** Ở mỗi tầng đệ quy, thuật toán cần tạo ra một `vector<string> temp` mới. Mặc dù bộ nhớ được giải phóng sau đệ quy, nhưng đỉnh điểm mức sử dụng RAM vẫn rất lớn.

---

## PHẦN 3: QUẢN LÝ BỘ NHỚ TỐI ƯU (Phân tích Code 2)

Để xử lý giới hạn trên, Code lần 2 đã gạt bỏ hoàn toàn cấu trúc dữ liệu chuẩn (STL) và can thiệp sâu vào cách tổ chức RAM.

### 3.1. Từ bỏ Cấp phát động: Kỹ thuật Memory Pool

Thay vì để hệ điều hành cấp phát hàng triệu chuỗi nhỏ lẻ, hệ thống xin hẳn một mảng tĩnh khổng lồ: `char pool_buf[MAX_BUF]`.
Tất cả các chuỗi được nối tiếp nhau vào vùng nhớ này. Mảng `str_ptrs[i]` chỉ đơn giản là lưu **con trỏ** trỏ đến điểm bắt đầu của chuỗi thứ $i$ trong Pool.

* **Hiệu ứng:** Dữ liệu hoàn toàn liên tục trên RAM. CPU có thể nạp một lúc một khối (cache line) chứa hàng tá ký tự, tăng tốc độ truy xuất lên nhiều lần (Cache-friendly).

### 3.2. Sắp xếp qua Chỉ số (Index Sorting)

Tương tự như tư duy khi cài đặt thuật toán trên danh sách liên kết, việc hoán vị địa chỉ quản lý (như đổi địa chỉ các Node) luôn tối ưu hơn rất nhiều so với việc sao chép hay hoán vị toàn bộ vùng dữ liệu vật lý khổng lồ bên trong.

Trong Code 2, thuật toán không bao giờ hoán vị các chuỗi trong `pool_buf`. Nó lưu các chỉ số từ $0$ đến $N-1$ vào một mảng `A`. Khi cần đổi chỗ, nó chỉ đổi chỗ hai số nguyên `A[i]` và `A[j]`. Phép hoán vị chuỗi nặng nề $O(L)$ giờ đây biến thành phép hoán vị số nguyên $O(1)$.

### 3.3. Gom nhóm $O(N)$ không dùng Vector

Để phân nhóm độ dài chuỗi mà không dùng `vector<string> a[101]`, hệ thống tạo ra một **Danh sách liên kết tự tạo (Ad-hoc Linked List)** bằng hai mảng `head` và `next_idx`.

* `head[len]` giữ chỉ số của chuỗi đầu tiên có độ dài `len`.
* `next_idx[i]` trỏ tới chuỗi tiếp theo có cùng độ dài.
Chỉ với 2 vòng `for` và mảng 1 chiều, dữ liệu được phân lô hoàn hảo với tốc độ tiệm cận mức phần cứng.

---

## PHẦN 4: 3-WAY MULTI-KEY QUICKSORT (Phân tích Code 2)

Cốt lõi của lần tối ưu thứ 2 là hàm `mkqsort`. MSD Radix Sort bị yếu điểm là mảng đếm `cnt` cố định kích thước 26 (chữ cái), rất tốn kém khi đệ quy xuống các khoảng nhỏ (ví dụ mảng chỉ còn 2-3 phần tử mà vẫn phải khởi tạo mảng `cnt[26]`).

### 4.1. Sự lai tạo hoàn hảo

Multi-Key Quicksort là sự kết hợp giữa Quick Sort và Radix Sort. Nó chỉ dựa vào **một ký tự duy nhất** (tại chỉ số `depth`) ở mỗi bước để chia mảng thành 3 phần, thay vì phân phối vào 26 khoang.

### 4.2. Cơ chế phân chia 3 ngôi (3-way Partitioning)

Thuật toán chọn ra một `pivot` là ký tự của chuỗi đầu tiên `str_ptrs[A[l]][depth]`. Quét qua mảng, nó chia dữ liệu thành:

1. **Phần `< pivot**` (Quản lý bởi con trỏ `lt`)
2. **Phần `== pivot**` (Nằm giữa `lt` và `i`)
3. **Phần `> pivot**` (Quản lý bởi con trỏ `gt`)

### 4.3. Giải phẫu hàm `mkqsort` với Ví dụ

Giả sử có mảng chuỗi tại `depth = 0`: `[ "cat", "bat", "car", "dog" ]`

* Chọn pivot: `c` (từ "cat").
* Quét mảng, đổi chỗ (hoán vị mảng `A`):
* `b < c`: Đẩy "bat" sang trái.
* `c == c`: Giữ "car" ở giữa.
* `d > c`: Đẩy "dog" sang phải.


* **Đệ quy thông minh:**
* Gọi `mkqsort` cho phần nhỏ hơn (`lt - 1`) với **`depth` không đổi**.
* Gọi `mkqsort` cho phần bằng (`lt` đến `gt`) với **`depth + 1`** (bởi vì ký tự tại `depth` đã giống nhau, ta xét ký tự tiếp theo).
* Gọi `mkqsort` cho phần lớn hơn (`gt + 1`) với **`depth` không đổi**.



Việc trượt `depth + 1` chỉ cho phần `==` chính là đặc tính chia để trị tiền tố của Radix Sort, nhưng được cài đặt bằng tốc độ và sự đơn giản của Quick Sort.

---

## PHẦN 5: TỔNG KẾT VÀ ĐÁNH GIÁ HIỆU NĂNG

### 5.1. Bảng so sánh tổng quan

| Tiêu chí | Code 1 (MSD Radix Sort + Vector) | Code 2 (Multi-key Quick Sort + Pool) |
| --- | --- | --- |
| **Quản lý bộ nhớ** | Rất phân mảnh, cấp phát động liên tục | Cực kỳ liền mạch (Memory Pool) |
| **Cache Friendly** | Kém (Dễ rớt bộ nhớ đệm) | Tuyệt vời (Dữ liệu liên tiếp) |
| **Bộ nhớ phụ** | Cao (Cần mảng `temp` bằng kích thước thực tế) | Thấp (Chỉ cần mảng chỉ số `A`) |
| **Hoán vị (Swap)** | Đổi vùng nhớ thật hoặc thao tác `std::swap` | Chỉ hoán vị số nguyên (Index $O(1)$) |
| **Xử lý đoạn ngắn** | Bị overhead do khởi tạo mảng `cnt` | Cực nhanh nhờ chia 3 ngôi trực tiếp |
