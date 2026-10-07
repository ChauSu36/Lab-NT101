# Nhiệm vụ 2.5: So sánh DES, 3DES, AES và Phân tích Double-DES

## 1. So sánh độ mạnh và sự khác biệt giữa DES, 3DES và AES

| Tiêu chí | DES (Data Encryption Standard) | Triple-DES (3DES) | AES (Advanced Encryption Standard) |
| :--- | :--- | :--- | :--- |
| **Kích thước khối (Block size)** | 64 bits (8 bytes) | 64 bits (8 bytes) | 128 bits (16 bytes) |
| **Độ dài khóa (Key length)** | 56 bits (thực tế 64 bits kèm 8 bits kiểm tra chẵn lẻ) | 112 bits (2 khóa) hoặc 168 bits (3 khóa) | 128, 192 hoặc 256 bits |
| **Cấu trúc thuật toán** | Mạng Feistel (16 vòng) | Mạng Feistel (48 vòng, quy trình E-D-E) | Mạng thế - hoán vị (SPN, 10/12/14 vòng) |
| **Tốc độ xử lý** | Trung bình trên phần cứng cũ