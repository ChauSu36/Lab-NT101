# Nhiệm vụ 2.5: So sánh DES, 3DES, AES và Phân tích Double-DES

## 1. So sánh độ mạnh và sự khác biệt giữa DES, 3DES và AES

| Tiêu chí | DES (Data Encryption Standard) | Triple-DES (3DES) | AES (Advanced Encryption Standard) |
| :--- | :--- | :--- | :--- |
| **Kích thước khối (Block size)** | 64 bits (8 bytes) | 64 bits (8 bytes) | 128 bits (16 bytes) |
| **Độ dài khóa (Key length)** | 56 bits (thực tế 64 bits kèm 8 bits parity) | 112 bits (2 khóa) hoặc 168 bits (3 khóa) | 128, 192 hoặc 256 bits |
| **Cấu trúc thuật toán** | Mạng Feistel (16 vòng) | Mạng Feistel (48 vòng, quy trình E-D-E) | Mạng thế - hoán vị (SPN, 10/12/14 vòng) |
| **Tốc độ xử lý** | Trung bình trên phần cứng cũ | Rất chậm (mã hóa lặp lại 3 lần) | Rất nhanh (hỗ trợ tập lệnh AES-NI trên CPU) |
| **Mức độ an toàn hiện tại** | **Không an toàn** (bị bẻ khóa bằng vét cạn trong vài giờ) | **Lỗi thời / Kém an toàn** (dễ bị tấn công Sweet32 do khối 64-bit) | **Rất an toàn** (chuẩn mã hóa hiện đại toàn cầu) |

### Nhận xét:
- **DES:** Đã hoàn toàn mất an toàn vì không gian khóa $2^{56}$ quá nhỏ so với năng lực tính toán hiện nay.
- **3DES:** Khắc phục được độ dài khóa của DES nhưng hiệu năng rất chậm và kích thước khối 64-bit dễ bị tấn công va chạm khối (Sweet32).
- **AES:** Chuẩn mã hóa thay thế hoàn hảo với độ an toàn cao, kích thước khối 128-bit chuẩn mực và tối ưu tốc độ xử lý vượt trội.

---

## 2. Tại sao chúng ta không nên sử dụng mã hóa Double-DES (2DES)?

Double-DES áp dụng hai tầng mã hóa tuần tự với hai khóa độc lập $K_1$ và $K_2$ (mỗi khóa 56 bits):
$$C = E_{K_2}(E_{K_1}(P))$$

Về mặt lý thuyết, tổng độ dài của 2 khóa là $56 + 56 = 112$ bits, được kỳ vọng đạt độ phức tạp vét cạn là $2^{112}$. Tuy nhiên, trên thực tế **2DES hoàn toàn không được sử dụng vì bị vô hiệu hóa bởi cuộc tấn công "Gặp nhau ở giữa" (Meet-in-the-Middle Attack)** do Ralph Merkle và Martin Hellman công bố.

### Cơ chế tấn công Meet-in-the-Middle:
Biến đổi phương trình mã hóa tương đương:
$$E_{K_1}(P) = D_{K_2}(C) = X$$
*(với $X$ là khối dữ liệu trung gian 64-bit sau tầng mã hóa thứ nhất).*

Giả sử kẻ tấn công nắm được một cặp bản rõ – bản mã $(P, C)$ đã biết:
1. **Pha 1 (Mã hóa xuôi từ bản rõ $P$):**
   - Thử toàn bộ $2^{56}$ khả năng của $K_1$ để tính $X = E_{K_1}(P)$.
   - Lưu toàn bộ $2^{56}$ cặp $(X, K_1)$ vào một bảng băm (Hash Table) sắp xếp theo $X$.
2. **Pha 2 (Giải mã ngược từ bản mã $C$):**
   - Thử lần lượt từng khóa $K_2$ ($2^{56}$ khả năng) để tính $X' = D_{K_2}(C)$.
   - Với mỗi $X'$, tra cứu ngay vào bảng băm ở Pha 1 xem có $X = X'$ hay không.
3. **Pha 3 (Xác minh khóa):**
   - Nếu có sự trùng khớp ($X = X'$), thử lại bộ khóa $(K_1, K_2)$ tìm được với cặp $(P_2, C_2)$ thứ hai để loại bỏ trường hợp trùng ngẫu nhiên và xác định chính xác khóa bí mật.

### Kết luận:
- **Độ phức tạp tính toán thực tế:** Giảm từ $2^{112}$ xuống chỉ còn:
  $$2^{56} + 2^{56} = 2 \times 2^{56} = 2^{57} \text{ phép tính}$$
- **Độ an toàn hiệu dụng:** Chỉ đạt **57 bits** — tức là 2DES chỉ mạnh hơn DES đơn (56 bits) đúng **1 bit** bảo mật.
- **Chi phí vận hành:** Tiêu tốn gấp đôi tài nguyên xử lý và bộ nhớ so với DES đơn nhưng không đem lại giá trị an toàn thực tế. Vì vậy, Double-DES hoàn toàn bị loại bỏ.