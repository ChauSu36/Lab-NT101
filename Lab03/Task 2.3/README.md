# Nhiệm vụ 2.3: Tạo va chạm MD5 (MD5 Collision)

## 1. Mục tiêu
Sử dụng công cụ `md5collgen` để tạo ra hai tệp nhị phân khác nhau nhưng có cùng giá trị băm MD5 từ tiền tố cho trước.

## 2. Kết quả thực nghiệm
- **Trường hợp tiền tố không chia hết cho 64 byte (`prefix_short.txt` - 10 byte):**
  - Công cụ tự động chèn thêm 54 byte `0x00` (padding) để đủ kích thước khối 64 byte trước khi nối khối dữ liệu va chạm.
- **Trường hợp tiền tố đúng 64 byte (`prefix_64.txt` - 64 byte):**
  - Không có byte padding nào được chèn thêm; khối xung đột được gắn trực tiếp ngay sau 64 byte gốc.
  - Lệnh `diff` xác nhận 2 file nhị phân khác nhau, nhưng `md5sum` trả về cùng giá trị băm `96e5e3b559946aba4828a78a72f34319`.

## 3. Lệnh kiểm tra
```bash
md5sum out1.bin out2.bin
diff out1.bin out2.bin
```
