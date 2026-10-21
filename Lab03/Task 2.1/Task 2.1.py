import base64

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(e, phi):
    d_old, d_new = 0, 1
    r_old, r_new = phi, e
    while r_new != 0:
        quotient = r_old // r_new
        d_old, d_new = d_new, d_old - quotient * d_new
        r_old, r_new = r_new, r_old - quotient * r_new
    if d_old < 0:
        d_old = d_old + phi
    return d_old

# 1. Hàm tạo khóa từ p, q, e cho trước
def generate_keys_given(p, q, e):
    n = p * q
    phi = (p - 1) * (q - 1)
    d = mod_inverse(e, phi)
    return ((e, n), (d, n))

# 2. Hàm mã hóa/giải mã tối ưu bằng pow() cho số lớn
def rsa_process_int(message_int, key, n):
    return pow(message_int, key, n)

# 3. Hàm hỗ trợ giải mã tự động cho câu 4
def try_decrypt(cipher_str, format_type, keys):
    # Bước 1: Chuyển chuỗi về số nguyên dựa trên định dạng
    try:
        if format_type == 'base64':
            # Padding nếu thiếu dấu =
            cipher_str += "=" * ((4 - len(cipher_str) % 4) % 4)
            c_bytes = base64.b64decode(cipher_str)
            c_int = int.from_bytes(c_bytes, byteorder='big')
        elif format_type == 'hex':
            c_int = int(cipher_str, 16)
        elif format_type == 'binary':
            c_int = int(cipher_str, 2)
        else:
            return "Định dạng không hợp lệ"
    except Exception as e:
        return f"Lỗi chuyển đổi dữ liệu: {e}"

    # Bước 2: Thử giải mã với từng khóa
    for key_idx, priv_key in keys.items():
        d, n = priv_key
        try:
            m_int = rsa_process_int(c_int, d, n)
            # Tính số byte cần thiết
            length = (m_int.bit_length() + 7) // 8
            if length == 0:
                continue
            m_bytes = m_int.to_bytes(length, byteorder='big')
            
            # Thử decode UTF-8 để xem có ra chuỗi đọc được không
            text = m_bytes.decode('utf-8')
            if text.isprintable():
                return f"Thành công với {key_idx}! Bản rõ: '{text}'"
        except Exception:
            # Bỏ qua nếu decode lỗi (do sai khóa)
            continue
            
    return "Không giải mã được bằng bất kỳ khóa nào!"


# THỰC THI NHIỆM VỤ 2.1
if __name__ == '__main__':
    print("="*80)
    print(" GIẢI QUYẾT NHIỆM VỤ 2.1 - LAB 03 ")
    print("="*80)

    # --- Ý 1: XÁC ĐỊNH KHÓA PU VÀ PR ---
    print("\n--- 1. XÁC ĐỊNH KHÓA PU VÀ PR ---")
    p1, q1, e1 = 11, 17, 7
    pub1, priv1 = generate_keys_given(p1, q1, e1)
    print(f"Key 1 - PU (e, n): {pub1}")
    print(f"Key 1 - PR (d, n): {priv1}\n")

    p2 = 20079993872842322116151219
    q2 = 676717145751736242170789
    e2 = 17
    pub2, priv2 = generate_keys_given(p2, q2, e2)
    print(f"Key 2 - PU: {pub2}")
    print(f"Key 2 - PR: {priv2}\n")

    p3 = int("F7E75FDC469067FFDC4E847C51F452DF", 16)
    q3 = int("E85CED54AF57E53E092113E62F436F4F", 16)
    e3 = int("0D88C3", 16)
    pub3, priv3 = generate_keys_given(p3, q3, e3)
    print(f"Key 3 (HEX) - PU: (e={hex(pub3[0])}, n={hex(pub3[1])})")
    print(f"Key 3 (HEX) - PR: (d={hex(priv3[0])}, n={hex(priv3[1])})\n")

    # --- Ý 2: MÃ HÓA VÀ GIẢI MÃ BẢN RÕ M = 5 ---
    print("--- 2. MÃ HÓA VÀ GIẢI MÃ BẢN RÕ M = 5 ---")
    M = 5
    e1, n1 = pub1
    d1, _ = priv1

    C_conf = rsa_process_int(M, e1, n1)
    M_conf = rsa_process_int(C_conf, d1, n1)
    print(f"[Bảo mật] Bản mã C: {C_conf} \t\t-> Giải mã M: {M_conf}")

    C_auth = rsa_process_int(M, d1, n1)
    M_auth = rsa_process_int(C_auth, e1, n1)
    print(f"[Xác thực] Bản mã C: {C_auth} \t\t-> Giải mã M: {M_auth}\n")

    # --- Ý 3: MÃ HÓA THÔNG ĐIỆP THÀNH BASE64 ---
    print("--- 3. MÃ HÓA THÔNG ĐIỆP THÀNH BASE64 ---")
    message = "The University of Information Technology"
    print(f"Thông điệp gốc: '{message}'")
    m_int = int.from_bytes(message.encode('utf-8'), byteorder='big')
    e3, n3 = pub3
    c_int = rsa_process_int(m_int, e3, n3)
    c_bytes = c_int.to_bytes((c_int.bit_length() + 7) // 8, byteorder='big')
    c_base64 = base64.b64encode(c_bytes).decode('utf-8')
    print(f"Bản mã Base64 (Dùng Key 3):\n{c_base64}\n")

    # --- Ý 4: GIẢI MÃ CÁC CHUỖI ĐÃ CHO ---
    print("--- 4. GIẢI MÃ CÁC BẢN MÃ ĐÃ CHO ---")
    keys_dict = {"Key 1": priv1, "Key 2": priv2, "Key 3": priv3}

    cipher_1 = "raUcesUlOkx/8ZhgodMoo0Uul8sC20yXlQFevSu7W/FDxIy0YRHMyXcHdD9PBvIT2aUft5fCQEGomiVVPv4I"
    cipher_2 = "C87F570FC4F699CEC24020C6F54221ABAB2CE0C3"
    cipher_3 = "Z2BUSkJcg0w4XEpgm0JcMEXEQmBIVH6dYEpNTHpMHptMQ7NgTHlgQrNMQ2BKTQ=="
    cipher_4 = "001010000001010011111111101101110010111011001010111011000110011110111111001111110110100011001111001100001001010001010100111101010100110011101110111011110101101100000100"

    print("Chuỗi 1 (Base64):", try_decrypt(cipher_1, 'base64', keys_dict))
    print("Chuỗi 2 (Hex)   :", try_decrypt(cipher_2, 'hex', keys_dict))
    print("Chuỗi 3 (Base64):", try_decrypt(cipher_3, 'base64', keys_dict))
    print("Chuỗi 4 (Binary):", try_decrypt(cipher_4, 'binary', keys_dict))
    print("="*80)