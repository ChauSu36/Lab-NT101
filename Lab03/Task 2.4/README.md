# Nhiệm vụ 2.4: Xác minh thủ công X.509 Certificate

## 1. Mục tiêu
- Tải chuỗi chứng chỉ X.509 từ máy chủ thực tế (`sha256.badssl.com`).
- Trích xuất khóa công khai của CA (n, e), khối chữ ký số của máy chủ và phần thân chứng chỉ TBS Certificate.
- Viết chương trình Python tính toán $EM' = S^e \pmod n$, gỡ bỏ lớp đệm PKCS#1 v1.5 và đối chiếu mã hash SHA-256.

## 2. Kết quả thực nghiệm
- Mã hash SHA-256 tính từ phần thân chứng chỉ (`c0_body.bin`): `20ffc90af25ed0cd0f2d0bb0e80f21770ffed5e2bb0526f935326152410ab302`
- Mã hash SHA-256 giải mã từ chữ ký số RSA bằng Public Key của CA: `20ffc90af25ed0cd0f2d0bb0e80f21770ffed5e2bb0526f935326152410ab302`
- Kết luận: Hai mã hash hoàn toàn trùng khớp, chứng chỉ máy chủ được xác minh thành công và đảm bảo tính toàn vẹn.

## 3. Hướng dẫn chạy
```bash
python3 verify.py
