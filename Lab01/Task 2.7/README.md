# Task 2.7: Mở rộng mật mã cổ điển - Affine Cipher (C++)

## 1. Giới thiệu
Chương trình minh họa mật mã Affine Cipher:
- Công thức mã hóa: `C = (a * p + b) mod 26`
- Công thức giải mã: `p = a^(-1) * (C - b) mod 26`
- Điều kiện an toàn: `gcd(a, 26) = 1`

## 2. Cách biên dịch và chạy
Sử dụng trình biên dịch `g++`:

```bash
# Biên dịch file cpp
g++ -std=c++11 affine_cipher.cpp -o affine_cipher

# Chạy chương trình
./affine_cipher