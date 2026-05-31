## 1.giải thích code 1

Chương trình sinh một bộ dữ liệu gồm 100.000 số nguyên với giá trị được tạo ngẫu nhiên bằng bộ sinh số giả ngẫu nhiên mt19937. Các phép XOR và dịch bit được sử dụng để tăng độ phân tán của dữ liệu, đồng thời xen kẽ số dương và số âm nhằm tạo tập dữ liệu có phạm vi giá trị rất lớn và phân bố gần như ngẫu nhiên.

Thuật toán mục tiêu

Bộ test này chủ yếu hướng đến các thuật toán sắp xếp:

Quick Sort cài đặt cơ bản (chọn pivot cố định).
Merge Sort.
Heap Sort.
Các thuật toán O(n
2
) như Bubble Sort, Selection Sort, Insertion Sort.
Lý do lựa chọn

Dữ liệu ngẫu nhiên kích thước lớn (n=100000) buộc các thuật toán phải xử lý toàn bộ dữ liệu mà không thể tận dụng tính chất đặc biệt nào của mảng.

Tại sao test này làm tăng thời gian chạy
Với Bubble Sort, Selection Sort, Insertion Sort: thời gian chạy tăng rất mạnh do phải thực hiện khoảng O(n
2
) phép so sánh và hoán đổi.
Với Quick Sort cơ bản: dữ liệu ngẫu nhiên khiến thuật toán phải thực hiện đầy đủ các bước phân hoạch và đệ quy trên toàn bộ mảng.
Với Merge Sort và Heap Sort: dù vẫn đạt O(nlogn), kích thước dữ liệu lớn làm tăng số lần so sánh và thao tác bộ nhớ.

=> Đây là bộ test ngẫu nhiên quy mô lớn nhằm đánh giá hiệu năng thực tế của các thuật toán sắp xếp trên trường hợp tổng quát.

## 2. giải thích code 2
Chương trình sinh bộ dữ liệu gồm 100.000 số nguyên theo một quy luật xác định thay vì ngẫu nhiên hoàn toàn. Mỗi phần tử được tạo từ chỉ số i, sau đó nhân với 256, xen kẽ dấu âm dương và thực hiện thêm phép XOR với (i << 16) để tạo ra các giá trị có sự thay đổi mạnh ở các bit cao.

Thuật toán mục tiêu

Bộ test này hướng đến:

Radix Sort.
Counting Sort (khi cần xử lý giá trị âm).
Quick Sort.
Merge Sort.
Heap Sort.
Lý do lựa chọn

Dữ liệu được sinh theo quy luật đều đặn nhưng có sự biến đổi mạnh ở biểu diễn nhị phân. Điều này tạo ra nhiều giá trị có khoảng cách lớn và phân bố không liên tục trên miền số nguyên.

Tại sao test này làm tăng thời gian chạy
Với Radix Sort và Counting Sort: miền giá trị rất rộng khiến việc xử lý trở nên kém hiệu quả hơn so với dữ liệu có phạm vi nhỏ.
Với Quick Sort: dữ liệu có cấu trúc đặc biệt nên chất lượng phân hoạch phụ thuộc nhiều vào cách chọn pivot.
Với Merge Sort và Heap Sort: vẫn phải xử lý toàn bộ 100.000 phần tử và thực hiện đầy đủ các bước so sánh, sắp xếp.

=> Đây là bộ test dữ liệu có quy luật nhưng phân bố giá trị rộng, được dùng để kiểm tra khả năng xử lý của các thuật toán trên tập dữ liệu lớn không hoàn toàn ngẫu nhiên.
## 3 . giải thích code 3
Cách thức sinh test case

Chương trình sinh 100.000 số nguyên bằng bộ sinh số ngẫu nhiên mt19937. Mỗi giá trị được tạo thông qua nhiều phép XOR và dịch bit để tăng độ phân tán dữ liệu. Ngoài ra, dấu của số được xen kẽ giữa âm và dương, đồng thời tiếp tục kết hợp với chỉ số phần tử bằng phép XOR nhằm tạo ra tập dữ liệu gần như ngẫu nhiên hoàn toàn.

Thuật toán mục tiêu

Bộ test này hướng đến:

Quick Sort.
Merge Sort.
Heap Sort.
Radix Sort.
Các thuật toán O(n
2
) như Bubble Sort, Selection Sort, Insertion Sort.
Lý do lựa chọn

Dữ liệu ngẫu nhiên với phạm vi giá trị rất lớn giúp loại bỏ các trường hợp đặc biệt mà thuật toán có thể tận dụng để tăng tốc. Mọi thuật toán đều phải xử lý đầy đủ số lượng phần tử và thực hiện toàn bộ các bước sắp xếp.

Tại sao test này làm tăng thời gian chạy
Với các thuật toán O(n
2
), số phép so sánh và hoán đổi tăng cực lớn khi n=100000.
Với Quick Sort, dữ liệu ngẫu nhiên khiến quá trình phân hoạch diễn ra trên toàn bộ cây đệ quy.
Với Merge Sort và Heap Sort, số phép so sánh đạt gần mức tối đa của trường hợp trung bình.
Với Radix Sort, việc xuất hiện cả số âm lẫn số dương cùng miền giá trị rộng làm tăng khối lượng xử lý các chữ số.

=> Đây là bộ test ngẫu nhiên kích thước lớn nhằm đánh giá hiệu năng tổng quát của các thuật toán sắp xếp trên dữ liệu thực tế không có quy luật đặc biệt.
## 3. giải thích code 4
Cách thức sinh test case

Chương trình sinh một bộ dữ liệu chỉ gồm 1 phần tử, có giá trị:

-2147483648

Đây là giá trị nhỏ nhất của kiểu dữ liệu int 32-bit (INT_MIN).

Thuật toán mục tiêu

Bộ test này hướng đến:

Tất cả các thuật toán sắp xếp.
Các thuật toán Radix Sort hoặc Counting Sort có xử lý số âm.
Các chương trình có thực hiện phép lấy trị tuyệt đối hoặc đổi dấu phần tử.
Lý do lựa chọn

Đây là trường hợp biên (edge case) nhỏ nhất về kích thước dữ liệu và đồng thời chứa giá trị nguyên nhỏ nhất mà kiểu int có thể lưu trữ.

Tại sao test này làm tăng thời gian chạy hoặc gây lỗi
Kiểm tra khả năng xử lý khi n = 1, tránh lỗi truy cập ngoài mảng hoặc đệ quy không cần thiết.
Với một số cài đặt Radix Sort hoặc Counting Sort, việc xử lý INT_MIN có thể gây tràn số khi thực hiện:
abs(INT_MIN)

hoặc

-INT_MIN

vì giá trị đối của INT_MIN không biểu diễn được bằng kiểu int.

Giúp phát hiện các lỗi liên quan đến điều kiện biên và xử lý số nguyên cực trị.

=> Đây là bộ test biên nhằm kiểm tra tính đúng đắn và độ ổn định của thuật toán khi làm việc với kích thước dữ liệu nhỏ nhất và giá trị nguyên nhỏ nhất có thể xuất hiện.
## 5. giải thích test 5
Cách thức sinh test case

Chương trình sinh 100.000 số nguyên ngẫu nhiên bằng bộ sinh mt19937 với seed cố định 123456789. Các giá trị được biến đổi thêm bằng phép XOR và dịch bit để tăng độ phân tán. Dấu âm dương được xen kẽ giữa các phần tử nhằm tạo tập dữ liệu có miền giá trị rộng và ổn định qua mọi lần chạy.

Thuật toán mục tiêu

Bộ test này hướng đến:

Quick Sort.
Merge Sort.
Heap Sort.
Radix Sort.
Các thuật toán O(n
2
) như Bubble Sort, Selection Sort, Insertion Sort.
Lý do lựa chọn

Khác với test ngẫu nhiên hoàn toàn, việc sử dụng seed cố định giúp mọi lần sinh dữ liệu đều cho kết quả giống nhau. Điều này cho phép so sánh công bằng thời gian chạy giữa các thuật toán trên cùng một bộ dữ liệu.

Tại sao test này làm tăng thời gian chạy
Kích thước dữ liệu lớn (n=100000) buộc thuật toán phải xử lý số lượng phần tử rất lớn.
Dữ liệu phân bố ngẫu nhiên nên không tồn tại cấu trúc đặc biệt để thuật toán tận dụng nhằm tăng tốc.
Với các thuật toán O(n
2
), thời gian thực thi tăng rất mạnh do số phép so sánh và hoán đổi cực lớn.
Với các thuật toán O(nlogn), bộ test tạo điều kiện đánh giá hiệu năng thực tế trên dữ liệu ngẫu nhiên chuẩn.

=> Đây là bộ test ngẫu nhiên có tính tái lập cao, được sử dụng để đo đạc và so sánh hiệu năng của các thuật toán sắp xếp một cách khách quan và ổn định.