
## 1. Phân tích các thuật toán được sử dụng

Đoạn code của bạn kết hợp hai thuật toán sắp xếp khác nhau để giải quyết bài toán sắp xếp chuỗi:

### A. Bucket Sort (Sắp xếp theo phân lô / theo độ dài)

* **Cách hoạt động:** Trong hàm `main`, bạn khởi tạo `vector<string> a[101]` và đẩy các chuỗi vào mảng dựa trên độ dài của chúng (`a[s.size()].push_back(s)`).
* **Mục đích:** Việc này chia bài toán lớn thành các bài toán nhỏ hơn. Thay vì sắp xếp toàn bộ danh sách, bạn chỉ cần sắp xếp các chuỗi có **cùng độ dài** với nhau. Điều này rất thông minh vì nó loại bỏ được trường hợp phải xử lý các chuỗi có độ dài ngắn dài khác nhau trong hàm Radix Sort, giúp code Radix Sort đơn giản hơn.
* **Độ phức tạp:** $O(N)$ với $N$ là tổng số chuỗi.

### B. MSD Radix Sort (Sắp xếp cơ số từ trái sang phải)

* **Cách hoạt động:** Hàm `RadixSort` của bạn chính là thuật toán **Most Significant Digit (MSD) Radix Sort**. Nó sắp xếp các chuỗi dựa trên ký tự đầu tiên (`pos = 0`), sau đó nhóm các chuỗi có cùng ký tự đầu tiên lại, và tiếp tục gọi đệ quy để sắp xếp dựa trên ký tự thứ hai (`pos = 1`), v.v.
* **Cơ chế lõi (Counting Sort):** Tại mỗi vị trí `pos`, bạn sử dụng **Counting Sort** (sắp xếp đếm) với mảng `cnt[27]` để đếm tần suất của 26 chữ cái tiếng Anh in thường. Sau đó tính mảng cộng dồn (prefix sum) để xác định vị trí đặt của từng chuỗi vào mảng `temp`.
* **Độ phức tạp:** Thời gian trung bình là $O(W)$, với $W$ là tổng độ dài của tất cả các chuỗi.

---

## 2. Các vấn đề logic trong code hiện tại

Trước khi tối ưu, có một vài điểm trong code của bạn mang rủi ro tiềm ẩn hoặc có thể là lỗi logic cần khắc phục:

* **Vòng lặp in kết quả bắt đầu từ 10:** Trong hàm `main`, bạn dùng `for (int i=10; i<=100; i++)`. Điều này có nghĩa là mọi chuỗi có độ dài từ 1 đến 9 sẽ **bị bỏ qua hoàn toàn**. Trừ khi đề bài của bạn có điều kiện bắt buộc chuỗi phải dài từ 10 ký tự trở lên, nếu không đây là một lỗi sai. Vòng lặp nên bắt đầu từ `1`.
* **Giới hạn độ dài chuỗi:** Bạn khai báo `a[101]`, tức là code sẽ bị lỗi bộ nhớ (Segmentation Fault) nếu đầu vào có một chuỗi dài 101 ký tự trở lên.
* **Ràng buộc ký tự:** Code của bạn giả định 100% các ký tự đều là chữ cái in thường từ `'a'` đến `'z'`. Nếu đầu vào có chữ in hoa (như `'A'`), số, hoặc khoảng trắng, `int c = ch - 'a';` sẽ sinh ra số âm, dẫn đến lỗi tràn viền mảng `cnt`.

---

## 3. Các cách tối ưu (Optimization)

MSD Radix Sort rất nhanh, nhưng nó có một nhược điểm chí mạng: **chi phí gọi đệ quy và khởi tạo mảng quá lớn đối với các tập dữ liệu nhỏ**. Dưới đây là các bước tối ưu:

### Tối ưu 1: Áp dụng Cut-off (Ngưỡng cắt) với Insertion Sort / std::sort

Khi chia nhỏ các nhóm chữ cái, bạn sẽ nhanh chóng tạo ra các mảng con chỉ có 2, 3 hoặc 10 phần tử. Việc khởi tạo mảng `cnt[27]` và vòng lặp đệ quy cho 5 chuỗi sẽ chậm hơn rất nhiều so với việc gọi trực tiếp hàm sắp xếp cơ bản.

* **Giải pháp:** Nếu `r - l < 15` (ngưỡng thường dùng), hãy dừng đệ quy và dùng `std::sort` cho đoạn đó.

### Tối ưu 2: Tối ưu mảng trung gian `temp`

Việc gán ngược lại từ `temp` vào `a` bằng vòng lặp `swap` là ổn, nhưng trong C++, bạn có thể sao chép nhanh vùng nhớ bằng `std::copy` hoặc dùng cấu trúc trả về con trỏ để tránh thao tác copy này. Tuy nhiên, cách đơn giản nhất là dùng `std::move`.

### Tối ưu 3: Tối ưu bộ nhớ cho Bucket

Thay vì dùng mảng tĩnh `vector<string> a[101]`, bạn có thể duyệt tìm độ dài lớn nhất của chuỗi trong quá trình đọc input, từ đó chỉ duyệt đến giới hạn thực tế, tiết kiệm thời gian khởi tạo và duyệt mảng trống.