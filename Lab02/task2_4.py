import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

# 1. Tạo dữ liệu 1000 byte ngẫu nhiên hoặc lặp lại
BLOCK_SIZE = 16
ORIGINAL_DATA = b"A" * 1000  # Dữ liệu kiểm thử 1000 bytes
KEY = os.urandom(16)        # Khóa AES-128
IV = os.urandom(16)         # Vector khởi tạo IV

# Đệm dữ liệu theo chuẩn PKCS7 để chia hết cho block 16 bytes
PLAINTEXT = pad(ORIGINAL_DATA, BLOCK_SIZE)
TOTAL_BLOCKS = len(PLAINTEXT) // BLOCK_SIZE

def flip_bit(byte_data: bytes, byte_pos: int, bit_pos: int = 0) -> bytes:
    """Đảo 1 bit tại vị trí byte_pos."""
    data_list = bytearray(byte_data)
    data_list[byte_pos] ^= (1 << bit_pos)  # Đảo bit chỉ định (mặc định bit 0)
    return bytes(data_list)

def count_different_bytes(b1: bytes, b2: bytes) -> int:
    """Đếm số byte khác biệt giữa hai khối."""
    return sum(1 for x, y in zip(b1, b2) if x != y)

def evaluate_mode(mode_name, cipher_encrypt, cipher_decrypt):
    # Bước 2: Mã hóa dữ liệu bằng AES-128
    ciphertext = cipher_encrypt.encrypt(PLAINTEXT)

    # Bước 3: Làm hỏng bản mã bằng cách đảo 1 bit tại byte thứ 26 (tính từ 0)
    corrupted_ciphertext = flip_bit(ciphertext, byte_pos=26, bit_pos=0)

    # Bước 4: Giải mã bản mã đã bị lỗi
    # (So sánh trực tiếp decrypted bytes trước khi unpad để tránh ValueError nếu khối đệm bị lỗi)
    decrypted = cipher_decrypt.decrypt(corrupted_ciphertext)

    print(f"\n{'='*25} CHẾ ĐỘ {mode_name} {'='*25}")
    corrupted_blocks = []

    for block_idx in range(TOTAL_BLOCKS):
        start = block_idx * BLOCK_SIZE
        end = start + BLOCK_SIZE
        orig_block = PLAINTEXT[start:end]
        dec_block = decrypted[start:end]

        diff_bytes = count_different_bytes(orig_block, dec_block)
        if diff_bytes > 0:
            corrupted_blocks.append((block_idx, diff_bytes))

    print(f"Tổng số khối: {TOTAL_BLOCKS} khối (khối 0 đến {TOTAL_BLOCKS - 1})")
    print(f"Số lượng khối bị hỏng: {len(corrupted_blocks)} khối")
    for b_idx, diff_count in corrupted_blocks:
        print(f" - Khối {b_idx} (bytes {b_idx*16} đến {(b_idx+1)*16 - 1}): bị sai {diff_count}/16 bytes")

def main():
    print(f"Byte bị đảo bit: 26 -> Nằm ở Khối thứ {26 // 16} (Block 1), vị trí {26 % 16} trong khối.")
    
    # 1. AES-ECB
    evaluate_mode("ECB", AES.new(KEY, AES.MODE_ECB), AES.new(KEY, AES.MODE_ECB))

    # 2. AES-CBC
    evaluate_mode("CBC", AES.new(KEY, AES.MODE_CBC, iv=IV), AES.new(KEY, AES.MODE_CBC, iv=IV))

    # 3. AES-CFB
    evaluate_mode("CFB", AES.new(KEY, AES.MODE_CFB, iv=IV, segment_size=128), AES.new(KEY, AES.MODE_CFB, iv=IV, segment_size=128))

    # 4. AES-OFB
    evaluate_mode("OFB", AES.new(KEY, AES.MODE_OFB, iv=IV), AES.new(KEY, AES.MODE_OFB, iv=IV))

if __name__ == "__main__":
    main()