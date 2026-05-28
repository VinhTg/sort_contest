# BÁO CÁO ĐỒ ÁN SORT CONTEST

## 1. THÔNG TIN CHUNG
* **Tên môn học:** Cấu trúc dữ liệu và Giải thuật (Data Structures and Algorithms)
* **Thời gian học:** Học kỳ 2, Năm học 2025 - 2026
* **Họ và tên sinh viên:** Lê Trung Vinh, Huỳnh Trịnh Chí Tài, Nguyễn Trương Đức Tiến
* **Mã số sinh viên:** 25120470, 25120431,25120446
* **Affiliation:** Ho Chi Minh City University of Science (HCMUS)
* **Repository Link:** https://github.com/VinhTg/sort_contest

---

### 2. Mô tả:

1. Cần làm phần Giai_thich.md của lần 1 của mỗi bài.

2. Cần tối ưu code vào lần nộp 2 

3. Ghi giải thích các hướng tối ưu so với lần 1.

4. Làm phần test_gen của phần sinh test cũ.

### 3. Yêu cầu:

Sinh viên xây dựng một repository Github chứa file README.md là báo cáo đồ án, file test_gen.cpp chứa mã nguồn C++ dùng để sinh ra bộ test case mà sinh viên nộp trên Moodle. Repository này cần để ở chế độ công khai (public) và chủ của repo phải có institution/affiliation là HCMUS hoặc FIT-HCMUS.

Trợ giảng sẽ tiến hành compile file test_gen.cpp trên môi trường do Trợ giảng thiết lập, vì vậy sinh viên chỉ được phép dùng các thư viện có sẵn trong Standard Template Library chuẩn của C++ 23. File test_gen.cpp cần cung cấp command-line interface như sau:

Câu lệnh: test_gen.<ext> <int/strlexi/strlenlexi> <1/2/3/4/5>, ví dụ test_gen.exe int 3, hay test_gen.o strlexi 5.
test_gen.<ext> là file binary đã biên dịch, có thể là test_gen.exe (trên Windows) hoặc test_gen.o (trên Linux).
Trong đó, argument thứ hai là int hoặc strlexi hoặc strlenlexi cho biết bài toán benchmark mà output của file cần cung cấp.
Còn argument thứ ba là số nguyên từ 1 đến 5, đại diện cho việc file binary cần sinh test thứ mấy mà sinh viên đã nộp trên Moodle.
File README.md báo cáo cần cung cấp đầy đủ các thông tin dưới đây:

Tên môn và thời gian học, họ tên sinh viên, MSSV.
Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên và các phương thức tối ưu hóa liên quan, lý giải tại sao phương pháp này tốt nhất trong tất cả các cách cài đặt ở lần 1.
Cách thức sinh test case được cài đặt trong test_gen.cpp, các thuật toán mục tiêu mà bộ test này được sinh ra để tăng thời gian chạy, giải thích lý do chọn các thuật toán mục tiêu này cùng việc tại sao các test trên giúp tăng thời gian chạy của chúng.
Thuật toán cài đặt tốt nhất ở lần thứ hai cùng các phương thức tối ưu hóa liên quan, làm thế nào để tối ưu tiếp tục so với lần 1.
Giới hạn: tối đa 10.000 ký tự không tính khoảng trắng nhưng tính các ký hiệu đặc biệt trong markdown (ví dụ #, $, -, v.v.)