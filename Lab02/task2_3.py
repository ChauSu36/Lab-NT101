from Crypto.Cipher import DES

def bytes_to_bin_str(data_bytes: bytes) -> str:
    return bin(int.from_bytes(data_bytes, 'big'))[2:].zfill(len(data_bytes) * 8)

def count_differing_bits(b1: bytes, b2: bytes) -> int:
    int1 = int.from_bytes(b1, 'big')
    int2 = int.from_bytes(b2, 'big')
    return bin(int1 ^ int2).count('1')

def avalanche_test(key_bytes: bytes, key_label: str):
    p1 = b'STAYHOME'
    p2 = b'STAYHOMA' 

    cipher = DES.new(key_bytes, DES.MODE_ECB)
    
    c1 = cipher.encrypt(p1)
    c2 = cipher.encrypt(p2)
    
    bin_c1 = bytes_to_bin_str(c1)
    bin_c2 = bytes_to_bin_str(c2)
    
    diff_bits = count_differing_bits(c1, c2)
    total_bits = len(c1) * 8
    percentage = (diff_bits / total_bits) * 100
    
    print("=" * 65)
    print(f"THỬ NGHIỆM KHÓA [{key_label}]: {key_bytes.decode('utf-8')}")
    print("=" * 65)
    print(f"Bản rõ P1 ({p1.decode()}): {bin_c1}")
    print(f"Bản rõ P2 ({p2.decode()}): {bin_c2}")
    print("-" * 65)
    print(f"-> Số bit khác nhau (Hamming Distance): {diff_bits} / {total_bits} bits[cite: 11]")
    print(f"-> Tỷ lệ phần trăm thay đổi bit        : {percentage:.2f}%\n[cite: 11]")

if __name__ == "__main__":
    avalanche_test(b'87654321', "Khóa mẫu")
    
    avalanche_test(b'24521485', "MSSV Thành viên 1")
    avalanche_test(b'24520227', "MSSV Thành viên 2")
    avalanche_test(b'24521541', "MSSV Thành viên 3")