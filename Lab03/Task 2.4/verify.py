def verify_certificate():
    # 1. Đọc khóa công khai modulus n của CA
    with open("ca_n.hex", "r") as f:
        n = int(f.read().strip(), 16)

    # Khóa công khai e thông thường là 65537
    e = 65537

    # 2. Đọc chữ ký số S
    with open("signature.hex", "r") as f:
        sig_hex = f.read().strip()
        S = int(sig_hex, 16)

    # 3. Tính toán xác minh RSA: EM' = S^e mod n
    em_int = pow(S, e, n)
    em_hex = hex(em_int)[2:]

    # Căn chỉnh kích thước đúng theo modulus (thường 512 ký tự hex cho RSA 2048-bit)
    modulus_len_hex = len(hex(n)[2:])
    em_hex = em_hex.zfill(modulus_len_hex)

    print("=" * 65)
    print("DỮ LIỆU SAU KHI GIẢI MÃ RSA TỪ CHỮ KÝ (EM'):")
    print(em_hex)
    print("=" * 65)

    # 4. Trích xuất mã băm SHA-256 (32 byte cuối = 64 ký tự hex)
    extracted_hash = em_hex[-64:]

    # 5. Đọc hash tính lại trực tiếp từ c0_body.bin
    with open("body_hash.txt", "r") as f:
        recomputed_hash = f.read().strip()

    print(f"Hash trích xuất từ chữ ký : {extracted_hash}")
    print(f"Hash tính lại từ c0_body.bin: {recomputed_hash}")
    print("=" * 65)

    # 6. Đối chiếu kết quả
    if extracted_hash.lower() == recomputed_hash.lower():
        print("[SUCCESS] XÁC MINH CHỨNG CHỈ THÀNH CÔNG! (Hashes match)")
    else:
        print("[FAILED] XÁC MINH THẤT BẠI! (Hashes do not match)")

if __name__ == "__main__":
    verify_certificate()
