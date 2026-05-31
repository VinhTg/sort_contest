BÀI A
GIẢI THÍCH CODE LẦN 1:
1. Ý tưởng chung

Chương trình sử dụng Quick Sort tối ưu hóa để sắp xếp mảng số nguyên. Đây là phiên bản cải tiến của Quick Sort truyền thống bằng cách kết hợp nhiều kỹ thuật tối ưu nhằm tăng tốc độ thực thi và giảm nguy cơ rơi vào trường hợp xấu nhất.

Quick Sort hoạt động theo nguyên tắc:

Chọn một phần tử làm pivot.
Chia mảng thành hai phần:
Các phần tử nhỏ hơn pivot.
Các phần tử lớn hơn pivot.
Đệ quy sắp xếp hai phần đó.

Độ phức tạp trung bình:

O(nlogn)
2. Các phương pháp tối ưu hóa được sử dụng
2.1. Median-of-Three Pivot Selection

Trong hàm partition():

int mid = left + (right - left) / 2;

if (arr[mid] < arr[left]) swap(arr[mid], arr[left]);
if (arr[right] < arr[left]) swap(arr[right], arr[left]);
if (arr[right] < arr[mid]) swap(arr[right], arr[mid]);

int pivot = arr[mid];

Thay vì chọn:

phần tử đầu,
phần tử cuối,
hoặc phần tử ngẫu nhiên,

chương trình lấy trung vị của:

phần tử đầu,
phần tử giữa,
phần tử cuối.

Ví dụ:

10   2   7

Sau khi sắp xếp:

2   7   10

Pivot được chọn là:

7
Lợi ích

Giảm khả năng xuất hiện trường hợp:

1 2 3 4 5 6 7 8

hoặc

8 7 6 5 4 3 2 1

làm Quick Sort bị suy biến thành:

O(n
2
)

Median-of-Three thường tạo ra pivot gần trung tâm hơn nên hai nửa sau khi chia cân bằng hơn.

2.2. Hoare Partition Scheme

Trong chương trình:

int i = left - 1;
int j = right + 1;

Hai con trỏ chạy từ hai đầu:

do { i++; } while (arr[i] < pivot);
do { j--; } while (arr[j] > pivot);

Sau đó đổi chỗ:

swap(arr[i], arr[j]);

đến khi:

i >= j
Lợi ích

So với Lomuto Partition:

for(...)

Hoare Partition:

ít phép swap hơn
ít phép gán hơn
nhanh hơn trong thực tế
xử lý dữ liệu có nhiều phần tử trùng nhau tốt hơn

Do đó hiệu năng thực tế cao hơn đáng kể.

2.3. Insertion Sort cho mảng nhỏ

Trong Quick Sort:

if (right - left < 15)
{
    insertionSort(arr, left, right);
    break;
}

Khi kích thước đoạn cần sắp xếp nhỏ hơn 15 phần tử, chương trình không tiếp tục đệ quy nữa mà dùng Insertion Sort.

Lý do

Mặc dù độ phức tạp của Insertion Sort là:

O(n
2
)

nhưng với n rất nhỏ:

5
10
15

thì:

không có chi phí đệ quy
không cần chọn pivot
không cần partition

nên thực tế nhanh hơn Quick Sort.

Đây là kỹ thuật được sử dụng trong nhiều thư viện chuẩn hiện nay.

2.4. Tail Recursion Optimization

Trong hàm:

if (p - left < right - p)
{
    quickSort(arr, left, p);
    left = p + 1;
}
else
{
    quickSort(arr, p + 1, right);
    right = p;
}

Chương trình luôn đệ quy vào nửa nhỏ hơn trước.

Lợi ích

Nếu đệ quy thông thường:

quickSort(left)
quickSort(right)

chiều sâu stack có thể lên đến:

O(n)

trong trường hợp xấu.

Kỹ thuật này đảm bảo:

O(logn)

mức sử dụng stack.

Ưu điểm:

giảm nguy cơ Stack Overflow
tiết kiệm bộ nhớ
ổn định hơn với dữ liệu lớn
3. Độ phức tạp
Thời gian
Trường hợp	Độ phức tạp
Tốt nhất	O(n log n)
Trung bình	O(n log n)
Xấu nhất	O(n²)

Tuy nhiên nhờ:

Median-of-Three
Hoare Partition

xác suất gặp trường hợp xấu nhất rất thấp.

Bộ nhớ

Do tối ưu đệ quy:

O(logn)
4. Tại sao đây là cách cài đặt tốt nhất ở lần chạy đầu tiên?

So sánh với các thuật toán khác:

Thuật toán	Thời gian TB	Bộ nhớ phụ
Bubble Sort	O(n²)	O(1)
Selection Sort	O(n²)	O(1)
Insertion Sort	O(n²)	O(1)
Merge Sort	O(n log n)	O(n)
Heap Sort	O(n log n)	O(1)
Quick Sort cơ bản	O(n log n)	O(log n)
Quick Sort tối ưu (chương trình)	O(n log n)	O(log n)
Lý do lựa chọn

Nhanh nhất trong thực tế

Mặc dù Heap Sort và Merge Sort cũng có độ phức tạp:

O(nlogn)

nhưng Quick Sort thường có hằng số thời gian nhỏ hơn nên chạy nhanh hơn trên dữ liệu thực tế.

Không cần bộ nhớ phụ lớn

Merge Sort cần:

O(n)

bộ nhớ phụ.

Chương trình này chỉ cần:

O(logn)

cho ngăn xếp đệ quy.

Giảm mạnh khả năng rơi vào O(n²)

Nhờ:

Median-of-Three
Hoare Partition

Tăng tốc với mảng nhỏ

Nhờ kết hợp:

Quick Sort
Insertion Sort

Tiết kiệm bộ nhớ stack

Nhờ Tail Recursion Optimization.

Kết luận

Thuật toán trong chương trình là một phiên bản Optimized Quick Sort kết hợp bốn kỹ thuật tối ưu:

Median-of-Three Pivot Selection
Hoare Partition Scheme
Insertion Sort cho mảng nhỏ
Tail Recursion Optimization

Nhờ các cải tiến này, thuật toán đạt hiệu năng thực tế rất cao, sử dụng ít bộ nhớ, giảm nguy cơ rơi vào trường hợp xấu nhất và phù hợp nhất để cài đặt ngay từ lần chạy đầu tiên đối với bài toán sắp xếp mảng số nguyên kích thước lớn.

GIẢI THÍCH SINH TEST LẦN 1:
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

GIẢI THÍCH CODE LẦN 2:
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

BÀI B:
GIẢI THÍCH CODE 1, GIẢI THÍCH SINH TEST LẦN 1, GIẢI THÍCH CODE LẦN 2
# Thuật toán tốt nhất lần 1

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

# Sinh test case và thuật toán mục tiêu

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

# Thuật toán tốt nhất lần 2

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

BÀI C
GIẢI THÍCH CODE 1:

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

GIẢI THÍCH SINH TEST 
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

GIẢI THÍCH CODE LẦN 2

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
