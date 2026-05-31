**TEST 1**

### 1. Cấu trúc dữ liệu đầu vào

Tổng số lượng chuỗi $N = 9999$. Định dạng của một chuỗi bao gồm 2 phần chính:

* **Tiền tố (2 ký tự):** Sinh tự động, sắp xếp theo thứ tự giảm dần từ điển (từ `zz` xuống `aa`).
* **Thân chuỗi (100 ký tự):** Cố định toàn bộ là chữ `a`.
Dữ liệu tạo thành chu kỳ lặp lại với mỗi khối gồm 676 chuỗi nghịch thế, tổng cộng khoảng 14.8 khối ghép nối.

### 2. Phân tích cơ chế tấn công

* **Vô hiệu hóa tiêu chí độ dài:** Ép mọi thuật toán phải bỏ qua việc so sánh độ dài và tiến thẳng vào so sánh từ điển từng ký tự.
* **Cấu trúc mảng nghịch thế:** Việc lặp lại các chu kỳ giảm dần liên tục (nghịch thế) tạo ra độ lệch phân phối nghiêm trọng đối với các thuật toán dựa vào chia để trị.

### 3. Các thuật toán bị nhắm mục tiêu

* **Quick Sort cơ bản:** Các cài đặt sử dụng phân hoạch Hoare hoặc Lomuto mà không tối ưu hóa điểm chốt (pivot). Cây đệ quy bị lệch hoàn toàn khiến độ phức tạp suy thoái từ $O(N \log N)$ xuống $O(N^2)$.
* **Thuật toán $O(N^2)$ nguyên thủy:** Bubble Sort, Selection Sort, hoặc Insertion Sort sẽ bị Time Limit Exceeded (TLE) do phải gánh khối lượng phép toán hoán vị khổng lồ với $N = 9999$.

---

**TEST 2**

### 1. Cấu trúc dữ liệu đầu vào

Tổng số lượng chuỗi $N = 9999$. Mỗi chuỗi có độ dài chính xác **100 ký tự** (Hợp lệ tuyệt đối). Định dạng chuỗi gồm 3 phần:

* **Tiền tố (2 ký tự):** `c1`, `c2` chứa logic tạo nghịch thế.
* **Thân chuỗi tĩnh (97 ký tự):** Cố định toàn chữ `b`.
* **Hậu tố (1 ký tự):** Biến `suffix`.

### 2. Phân tích cơ chế tấn công

* **Tái cấu trúc khối dữ liệu tĩnh - động:** Đảo ngược vị trí vùng dữ liệu, ép CPU của thuật toán phải đọc qua toàn bộ 97 ký tự tĩnh giống hệt nhau trước khi chạm đến điểm phân định khác biệt (nghịch thế). Điều này đẩy cao chi phí thời gian của mỗi chu kỳ quét.

### 3. Các thuật toán bị nhắm mục tiêu

* **Các thuật toán so sánh chuỗi tuyến tính:** Bị vắt kiệt hiệu năng CPU do phải liên tục xử lý các mảng ký tự trùng lặp dài trước khi tìm thấy sự khác biệt, đặc biệt chí mạng với các giải thuật có số lần so sánh tiệm cận $O(N^2)$.

---

**TEST 3**

### 1. Cấu trúc dữ liệu đầu vào

Tổng số lượng chuỗi $N = 9999$, độ dài chính xác **100 ký tự**. Dữ liệu được chia thành các khối, mỗi khối chứa chính xác **25 chuỗi giống hệt nhau**. Định dạng chuỗi gồm 2 phần:

* **Tiền tố khối (3 ký tự):** `c1`, `c2`, `c3`. Trong đó `c2` giảm dần tạo chuỗi nghịch thế cục bộ và thỉnh thoảng có bước nhảy vọt (reset từ `a` về `z`).
* **Thân chuỗi (97 ký tự):** Cố định toàn chữ `c`.

### 2. Phân tích cơ chế tấn công

* **Gom nhóm trùng lặp:** Gài bẫy bằng cách bơm một lượng lớn các phần tử có giá trị bằng nhau đứng liền kề.
* **Ngắt nhịp nghịch thế:** Việc thỉnh thoảng chèn các bước nhảy vọt (reset biến thiên) làm đứt gãy các chuỗi giảm dần (descending runs) liên tục.

### 3. Các thuật toán bị nhắm mục tiêu

* **Quick Sort không có Phân hoạch 3 chiều:** Sẽ hoán đổi dư thừa và chia mảng cực kỳ thiếu đồng đều khi gặp chuỗi trùng lặp, khiến độ phức tạp rớt thẳng xuống $O(N^2)$ và dính TLE.
* **TimSort / Hybrid Sorts:** Các thuật toán nhận diện mẫu mảng con bị đánh lừa bởi các bước nhảy vọt, tốn thêm chi phí gộp mảng (merge) thay vì thao tác đảo ngược mảng thông thường.

---

**TEST 4**

### 1. Cấu trúc dữ liệu đầu vào

Tổng số lượng chuỗi $N = 9999$. Dữ liệu chia thành các khối **25 phần tử**. Định dạng chuỗi được thiết lập để điểm khác biệt nằm ở tận cuối:

* **Tiền tố dùng chung (97 ký tự):** Định dạng `"qwert"` + `c6` + `"b"` + 90 ký tự `"d"`.
* **Ký tự phân định (1 ký tự):** Nằm ở vị trí thứ 98 (`suffix`).

### 2. Phân tích cơ chế tấn công

* **Tiền tố dùng chung dài (LCP):** Khi nội bộ khối 25 phần tử tiến hành so sánh, 97 ký tự đầu hoàn toàn trùng khớp. Cỗ máy so sánh bắt buộc phải quét đến phần tử thứ 98 mới tìm ra kết quả.
* **Tấn công răng cưa (Sawtooth):** Đẩy chi phí thời gian của một phép so sánh đơn lẻ từ $O(1)$ lên giới hạn $O(L)$ (với $L$ là chiều dài chuỗi).

### 3. Các thuật toán bị nhắm mục tiêu

* **Quick Sort tiêu chuẩn:** Nhạy cảm với dữ liệu có tính thứ tự đặc thù và bị bóp nghẹt bởi thao tác so sánh chuỗi bị kéo dài.
* **Natural Merge Sort / TimSort:** Không thể tìm được các đoạn (runs) tự nhiên đủ tốt, thao tác gộp bị bào mòn tài nguyên bởi chuỗi tiền tố LCP quá dài.

**TEST 5**
### 1. Phân tích cơ chế tấn công
* **Tối đa hóa chi phí so sánh (Chiến thuật LCP - Long Common Prefix):** Khi thuật toán so sánh hai chuỗi trong cùng một khối, **99 ký tự đầu tiên hoàn toàn giống nhau** (`c1` + `f` + `97 ký tự e`). Máy tính bắt buộc phải quét đến tận ký tự thứ 100 (`suffix`) mới biết chuỗi nào lớn hơn. Điều này đẩy chi phí so sánh lên mức cực đại $O(L)$ thay vì $O(1)$.

* **Đánh lừa logic sắp xếp:** Việc sắp xếp đan xen "khối tăng dần - nội bộ giảm dần" tạo ra sự phân mảnh liên tục. Dữ liệu liên tục bị gãy khúc cứ sau mỗi 24 phần tử.

### 2. Các thuật toán bị nhắm mục tiêu
* **Quick Sort:** Sẽ bị chậm đi hàng chục lần. Khi Quick Sort tiến hành phân hoạch (partition) trong nội bộ 24 phần tử của một khối, mảng đang bị ngược (giảm dần) kết hợp với chi phí so sánh 100 ký tự sẽ gây nghẽn CPU nghiêm trọng.

* **TimSort / Natural Merge Sort:** Các thuật toán gom mảng con thông minh sẽ bị vô hiệu hóa vì mảng liên tục bị đổi chiều (tăng xong lại giảm) ở chu kỳ quá ngắn (24 phần tử), ép thuật toán phải thực hiện vô số thao tác trộn (merge) rác.