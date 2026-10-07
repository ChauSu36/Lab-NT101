from Crypto.Cipher import AES

key = b'1234567890123456'
plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_" # 32 bytes (2 blocks)

# 1. AES-ECB
cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)

# 2. AES-CBC
iv = b'0000000000000000' # Vector khởi tạo 16 bytes
cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
ct_cbc = cipher_cbc.encrypt(plaintext)

print(f"ECB (Hex): {ct_ecb.hex()}")
print(f"CBC (Hex): {ct_cbc.hex()}")